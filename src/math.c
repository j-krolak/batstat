#include "math.h"

int min(int a, int b) {
    return a < b ? a : b; 
}

int max(int a, int b) {
    return a < b ? b : a; 
}

int abs(int a) {
    return a < 0 ? -a : a;
}

int count_digits(int a) {
    int res = 1;
    a = abs(a);
    while(a = a/10)
        res++;
    
    return res;
}