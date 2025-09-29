#pragma once

#include <stdlib.h>

typedef struct Point Point;
struct Point {
    int x;
    int y;
};

void print_graph(Point points[], size_t size, int width, int height, int minimalY, int maximalY);