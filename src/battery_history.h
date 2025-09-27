#pragma once

#include "battery.h" 
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct BatteryHistory BatteryHistory;
typedef struct BatteryHistoryRecord BatterHistoryRecord;

struct BatteryHistoryRecord  {
    long long energyFull;  
    time_t timestamp;
};

struct BatteryHistory {
    BatterHistoryRecord *records;
    long size;
};


void BatterHistory_Init(BatteryHistory*, bool loadOnlyLastRecord);
void BatteryHistory_Write(Battery*);