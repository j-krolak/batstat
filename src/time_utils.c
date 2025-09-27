#include "time_utils.h"
#include <stdio.h>

bool isSameDay(time_t a, time_t b) {
    struct tm t1 = *localtime(&a);
    struct tm t2 = *localtime(&b);

    normalizeToMidnight(&t1);
    normalizeToMidnight(&t2);
    
    time_t date1 = mktime(&t1);
    time_t date2 = mktime(&t2);

    return  date1 == date2;
}

void normalizeToMidnight(struct tm * t) {
   t->tm_hour = t->tm_min = t->tm_sec = 0; 
}