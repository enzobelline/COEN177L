#include <stdio.h>

typedef struct {
    int pageno;
    //. . .
} ref_page; 


int main(int argc, const char * argv[]) {
    int cacheSize = atoi(argv[1]); // Size of Cache passed by user
    
    ref_page cache[cacheSize]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file
    int totalFaults = 0; // keeps track of the total page faults
    
    while(fgets(pageCache, 100, stdin)) {
         int page_num = atoi(pageCache); // Stores number read from file as an int

    }

    
}

