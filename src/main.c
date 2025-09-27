#include <stdio.h>
#include "battery.h"
#include "battery_history.h"
#include <time.h>

int main(int argc, char* const argv[]) {
    BatteryHistory history;
    BatterHistory_Init(&history, true);


    for(long i = 0; i < history.size;i++) {
        time_t * p = &history.records[i].timestamp;
        printf("%.2f Wh %s", (double)(history.records[i].energyFull)/1e6,ctime(p));
    }

    return 0;
}