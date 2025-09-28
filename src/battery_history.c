#include "battery_history.h"

#include <unistd.h>
#include <stdio.h>
#include "file_utils.h"
#define BATTERY_HISTORY_FILE "/var/log/batstat/battery_capacity_history.bin"

void BatterHistory_Init(BatteryHistory *self, bool loadOnlyLastRecord) {
    FILE *fp = fopen(BATTERY_HISTORY_FILE, "rb");
    if(!fp) {
        self->size = 0;
        return;
    }

    if(loadOnlyLastRecord) {
        if(get_size_of_file(fp) < sizeof(BatterHistoryRecord)) {
            self->size = 0; 
            fclose(fp);
            return;
        }

        fseek(fp, -(long)sizeof(BatterHistoryRecord), SEEK_END);
        self->records = malloc(sizeof(BatterHistoryRecord));
        self->size = 1;
        fread(self->records, sizeof(BatterHistoryRecord), 1, fp);

        fclose(fp);
        return;
    }

    long size = get_size_of_file(fp);
    self->records = malloc(size);
    self->size = size/sizeof(BatterHistoryRecord);
    fread(self->records, size, 1, fp);

    fclose(fp);
}

void BatteryHistory_Write(Battery *battery) {
    time_t timestamp = time(NULL);
    BatterHistoryRecord record = {battery->energyFull, timestamp};

    FILE *fp = fopen(BATTERY_HISTORY_FILE, "ab");
    if(!fp) {
        perror("Failed to open file");
        return;
    }

    fwrite(&record, sizeof(BatterHistoryRecord), 1, fp);
    fclose(fp);
}