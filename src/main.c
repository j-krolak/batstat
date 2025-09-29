#include <stdio.h>
#include <time.h>
#include <string.h>
#include <getopt.h>

#include "battery.h"
#include "battery_history.h"
#include "time_utils.h"
#include "config.h"
#include "graph.h"

void run_service();
void run_cli(unsigned char flags);

int main(int argc, char *argv[]) {
    int opt;
    char *config_path = NULL;
    static struct option long_opts[] = {
        {"service", no_argument, 0, 's'},
        {"graph", no_argument, 0, 'g'},
        {0,0,0,0}

    };

    char flags = 0;
    while((opt = getopt_long(argc, argv, "sg", long_opts, NULL)) != -1) {
        switch(opt) {
            case 's':
                run_service();
                return 0;
            case 'g':
                flags |= 0b1;
                break;
        }
    }
  

    run_cli(flags); 
    return 0;
}

void run_service() {
    BatteryHistory history;
    BatteryHistory_Init(&history, true);

    time_t now = time(NULL);

    if(history.size > 0 && isSameDay(now, history.records[0].timestamp)) {
        return;
    }

    Config config;
    Config_Init(&config, true);

    Battery battery;
    Battery_Init(&battery, &config);
    Battery_UpdateCurrentEnergy(&battery);
    BatteryHistory_Write(&battery);
}

void run_cli(unsigned char flags) {
    BatteryHistory history;
    BatteryHistory_Init(&history, false);

    Config config;
    Config_Init(&config, false);

    Battery battery;
    Battery_Init(&battery, &config);
    Battery_UpdateEnergyDesign(&battery);
    Point *points;
    if(flags & 0b1)
        points = malloc( history.size * sizeof(Point));

    printf("ratio  r_cap d_cap    date\n");
    for(long i = history.size - 1; i >= 0;i--) {
        time_t * p = &history.records[i].timestamp;
        double energyFull = (double) history.records[i].energyFull;
        double val = (energyFull/(double)battery.energyDesign) * 100;
        printf("%4.2f%% %5.2f %5.2f Wh %s", val, (double)(energyFull)/1e6,(double)battery.energyDesign/1e6, ctime(p));
        if(flags & 0b1) {
            struct tm *lt = localtime(p);
            points[i].x = lt->tm_year * 365+lt->tm_yday;
            points[i].y =  (int)val;
        }

    }
    if(flags & 0b1)
        print_graph(points, history.size, 80, 20, 0, 100);

}