#pragma once

typedef struct Battery Battery;
struct Battery {
    long long energyFull;
};

void Battery_Init(Battery*);
void Battery_UpdateCurrentEnergy(Battery*);