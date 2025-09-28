#pragma once
#include <stdbool.h>

typedef struct Config Config;
struct  Config {
    char *batteryPath;
};

typedef enum SectionType SectionType;
enum SectionType {
    SectionNone,
    SectionBattery
};

int Config_Init(Config*);

void create_config_file();