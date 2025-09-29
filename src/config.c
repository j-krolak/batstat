#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"

#define CONFIG_PATH "/etc/batstat/config.conf"  

int Config_Init(Config *conf, bool log) {
    
    conf->batteryPath = "/sys/class/power_supply/BAT0";        
    FILE *f = fopen(CONFIG_PATH, "r");


    if(!f) {
        if(log)
            printf("Config file not founded.\n");
        return 0;
    }
    if(log)
        printf("Config file founded.\n");
    char line[256];
    char *n;
    SectionType currentSection = SectionNone;
    const char *batteryPrefix = "[battery]";
    const int batteryPrefixLen = strlen(batteryPrefix);

    const char *pathPrefix = "path=";
    const int pathPrefixLen = strlen(pathPrefix);

    while((n = fgets(line, 256, f)) > 0) {
        if(strncmp(line, batteryPrefix, batteryPrefixLen) == 0) {
            currentSection = SectionBattery;
        }
        switch(currentSection) {
            case SectionBattery:
                if(strncmp(line, pathPrefix, pathPrefixLen) == 0) {
                    size_t i = strcspn(line, "\n");
                    if(i < strlen(line))
                        line[i] = '\0';
                        
                    char *batteryPath = line + pathPrefixLen;
                    conf->batteryPath = malloc(strlen(batteryPath));
                    strcpy(conf->batteryPath, batteryPath);
                }
                break;
        }
    }
}
