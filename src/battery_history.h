#pragma once

#include "battery.h" 
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct BatteryHistory BatteryHistory;
typedef struct BatteryHistoryRecord BatteryHistoryRecord;

struct BatteryHistoryRecord  {
    long long energyFull;  
    time_t timestamp;
};

struct BatteryHistory {
    BatteryHistoryRecord *records;
    long size;
};


void BatteryHistory_Init(BatteryHistory*, bool loadOnlyLastRecord);
void BatteryHistory_Write(Battery*);