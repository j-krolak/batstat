#include "graph.h"

#include <stdio.h>
#include <string.h>

#include "math.h"

void print_star(unsigned char row, unsigned char pattern) {
    if(row & pattern) 
        printf("*");
    else
        printf(" ");
}

void print_graph(Point points[], size_t size, int width, int height, int minimalY, int maximalY) {
    int minimalX = points[0].x;
    int maximalX = points[size-1].x;
    
    //Bitmap of graph
    size_t bitmap_size = (width*height)/8;
    unsigned char *bitmap = calloc(bitmap_size, 1);
   
    for(int i = 0; i < size; i++) {
        int normalizedY = (int)((double)(points[i].y - minimalY)/(double)(max(maximalY-minimalY,1))*(double)(height-1));
        int normalizedX = (int)((double)(points[i].x - minimalX)/(double)(max(maximalX-minimalX, 1))*(double)(width-1));
        int index = (height-normalizedY-1) * (width/8) + normalizedX/8;
        bitmap[index] |= (1 << (7 - normalizedX%8));
    }

    int maximalYDigits = count_digits(maximalY);     

    for(int i = 0; i < maximalYDigits + 1; i++)
        printf(" ");
    printf(" +");
    for(int i = 0; i < width; i++) {
        printf("-");
    }
    printf("+\n");

    for(int i = 0; i < height; i++) {
        int current_height = maximalY - (int)((double)(maximalY-minimalY)*((double)(i)/(double)(height)));

        if(current_height % 10 == 0) {
            for(int j = 0; j < (maximalYDigits -  count_digits(current_height)); j++)
                printf(" ");
            printf("%d%%", current_height);

        } else {
            for(int i = 0; i < maximalYDigits+1; i++)
                printf(" ");
        }
        printf(" |");
        for(int j = 0; j < width/8; j++) {
            int index = i * (width/8) + j;
            unsigned char excerpt = bitmap[index];
            for(char k = 7; k >= 0; k--) {
                print_star(excerpt, 1 << k);
            }
            
        }
        printf("|\n");
    }

    for(int i = 0; i < maximalYDigits+1; i++)
        printf(" ");
 
    printf(" +");
    for(int i = 0; i < width; i++) {
        printf("-");
    }
    printf("+\n");
}