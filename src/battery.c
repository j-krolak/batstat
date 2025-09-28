#include "battery.h"

#include <stdlib.h>
#include <stdio.h>

#include "file_utils.h"
#include "config.h"

void Battery_Init(Battery *self) {
    Config config;
    Config_Init(&config);
}


void Battery_UpdateCurrentEnergy(Battery *self) {
    char* buff = malloc(32);
    read_file(buff, 32, self->batteryPath);
    self->energyFull = strtoll(buff, NULL, 10);
    free(buff);
}
