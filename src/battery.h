#pragma once
#include "config.h"

typedef struct Battery Battery;
struct Battery {
    long long energyFull;
    long long energyDesign;
    Config *config;
};

void Battery_Init(Battery*, Config*);
void Battery_UpdateCurrentEnergy(Battery*);
void Battery_UpdateEnergyDesign(Battery*);