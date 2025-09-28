#include "battery.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "file_utils.h"
#include "config.h"

void Battery_Init(Battery *self, Config *config) {
    self->config = config;
}


void Battery_UpdateCurrentEnergy(Battery *self) {
    char* buff = malloc(32);
    char* capacityPath = concat_paths(self->config->batteryPath, "/energy_full");
    read_file(buff, 32,capacityPath);
    self->energyFull = strtoll(buff, NULL, 10);

    free(buff);
    free(capacityPath);
}
