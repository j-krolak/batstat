#include <stdio.h>
#include <time.h>
#include <string.h>
#include <getopt.h>

#include "battery.h"
#include "battery_history.h"
#include "time_utils.h"
#include "config.h"

void run_service();
void run_cli();

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

    run_cli(); 
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

void run_cli() {
    BatteryHistory history;
    BatteryHistory_Init(&history, true);

    Config config;
    Config_Init(&config, false);

    Battery battery;
    Battery_Init(&battery, &config);
    Battery_UpdateEnergyDesign(&battery);

    for(long i = 0; i < history.size;i++) {
        time_t * p = &history.records[i].timestamp;
        double energyFull = (double) history.records[i].energyFull;
        printf("%.2f%% %.2f Wh %s", (energyFull/(double)battery.energyDesign), (double)(energyFull)/1e6,ctime(p));
        
    }
}