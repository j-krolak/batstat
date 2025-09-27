#include "battery.h"

#include "file_utils.h"
#include <stdlib.h>

void Battery_Init(Battery *self) {

}


void Battery_UpdateCurrentEnergy(Battery *self) {
    char* buff = malloc(32);
    read_file(buff, 32, "./BAT0/energy_full");
    self->energyFull = strtoll(buff, NULL, 10);
    free(buff);
}
