#pragma once

#include <stdbool.h>
#include <time.h>

bool isSameDay(time_t, time_t);
void normalizeToMidnight(struct tm * t);