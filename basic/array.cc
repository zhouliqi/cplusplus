#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <memory>
#include <iostream>

int main() {
    printf("1. array is consecutive.\n");
    {
        int abc[5][4] ={
            {0,1,2,3},
            {4,5,6,7},
            {8,9,10,11},
            {12,13,14,15},
            {16,17,18,19}
            };
        /* The correct way of displaying an address would be
         * printf("%p ",abc[i]); but for the demonstration
         * purpose I am displaying the address in int so that
         * you can relate the output with the diagram above that
         * shows how many bytes an int element uses and how they
         * are stored in contiguous memory locations.
         */
        for (int i = 0; i < 20; ++i) {
            printf("(addr = %p, value = %d)\n", (abc[i / 4] + (i % 4)), (*abc)[i]);
        }
    }

    return 0;
}