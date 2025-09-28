#pragma once
#include "config.h"

typedef struct Battery Battery;
struct Battery {
    long long energyFull;
    Config *config;
};

void Battery_Init(Battery*, Config*);
void Battery_UpdateCurrentEnergy(Battery*);