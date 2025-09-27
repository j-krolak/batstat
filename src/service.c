#include <stdio.h>
#include "battery.h"
#include "battery_history.h"
#include "time_utils.h"
#include <time.h>

int main(int argc, char* const argv[]) {
    BatteryHistory history;
    BatterHistory_Init(&history, true);

    time_t now = time(NULL);

    if(history.size > 0 && isSameDay(now, history.records[0].timestamp)) {
        return 0;
    }

    Battery battery;
    Battery_Init(&battery);
    Battery_UpdateCurrentEnergy(&battery);
    BatteryHistory_Write(&battery);

    return 0;
}