#include <stdio.h>
#include <time.h>
#include <string.h>
#include <getopt.h>

#include "battery.h"
#include "battery_history.h"
#include "time_utils.h"
#include "config.h"

void run_service();
void run_ctl();

int main(int argc, char *argv[]) {
    int opt;
    char *config_path = NULL;
    static struct option long_opts[] = {
        {"service", no_argument, 0, 's'},
        {0,0,0,0}
    };

    while((opt = getopt_long(argc, argv, "s", long_opts, NULL)) != -1) {
        switch(opt) {
            case 's':
                run_service();
                return 0;
        }
    }
    run_ctl(); 
    return 0;
}

void run_service() {
    printf("Service");
    BatteryHistory history;
    BatterHistory_Init(&history, true);

    time_t now = time(NULL);

    if(history.size > 0 && isSameDay(now, history.records[0].timestamp)) {
        return;
    }

    Config config;
    Config_Init(&config);

    Battery battery;
    Battery_Init(&battery, &config);
    Battery_UpdateCurrentEnergy(&battery);
    BatteryHistory_Write(&battery);
}

void run_ctl() {
    BatteryHistory history;
    BatterHistory_Init(&history, true);


    for(long i = 0; i < history.size;i++) {
        time_t * p = &history.records[i].timestamp;
        printf("%.2f Wh %s", (double)(history.records[i].energyFull)/1e6,ctime(p));
    }
}