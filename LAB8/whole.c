#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct {//to
    int pageno;
    int ref_bit;
} ref_page;


int main(int argc, char *argv[]) {
    int C_SIZE = atoi(argv[1]); // Size of Cache passed by user.
    ref_page cache[C_SIZE]; // Cache that stores pages.
    char pageCache[100]; // Cache that holds the input from test file.
    
    // Decide page replacement algorithm:
    // 1 - FIFO, 2 - LRU, 3 - Second Chance
    int algorithm = atoi(argv[2]);

    int i;
    int totalFaults = 0; // Keeps track of the total page faults.
    int numRequests = 0; // Keeps track of the total requests.
    
    for (i = 0; i < C_SIZE; i++){ // Initialize cache array and reference bits.
        cache[i].pageno = -1;
        cache[i].ref_bit = 0;
    }

    int placeInArray = 0;
    while (fgets(pageCache, 100, stdin)) {
        
        // If we reach the end of the file or an empty line skip it.
        if (strlen(pageCache) <= 1) {
            continue;
        }
        
        int page_num = atoi(pageCache); // Stores number read from file as an int.
        numRequests++;
        
        // FIFO
        if (algorithm == 1) {
            bool foundInCache = false;
            for (i=0; i< C_SIZE; i++){
                if (cache[i].pageno == page_num){
                    foundInCache = true;
                    break; // Break out loop because found page_num in cache.
                }
            }
            if (foundInCache == false){
                // If the page is not found in cache, replace the current page with it.
                printf("Page Fault: %d\n", page_num);
                cache[placeInArray].pageno = page_num;
                totalFaults++;
                placeInArray = (placeInArray + 1) % C_SIZE; //Need to keep the value within the cacheSize.
            }
        }
        
        // LRU
        // cache[0] is least recently used.
        // cache[C_SIZE - 1] is most recently used.
        if (algorithm == 2) {
            int cacheIndex = 0;
            bool foundInCache = false;
            for (i=0; i< C_SIZE; i++){
                if (cache[i].pageno == page_num){
                    foundInCache = true;
                    cacheIndex = i;
                    break; //break out loop because found page_num in cache
                }
            }
            if (foundInCache == false){
                printf("Page Fault: %d\n", page_num);
                // If there is room in the cache, add it.
                if (placeInArray < C_SIZE) {
                    cache[placeInArray].pageno = page_num;
                    placeInArray++;
                }
                else {
                    // Otherwise remove the LRU (cache[0]) and add the number to the end.
                    for (i = 0; i < C_SIZE-1; i++) {
                        cache[i].pageno = cache[i+1].pageno;
                    }
                    cache[C_SIZE-1].pageno = page_num;
                }
                totalFaults++;
            }
            else {
                // If the number is already in cache, move it to be most recently used.
                for (i = cacheIndex; i < placeInArray; i++) {
                    cache[i].pageno = cache[i+1].pageno;
                }
                cache[placeInArray-1].pageno = page_num;
            }
        }
        
        // SECOND CHANCE
        if (algorithm == 3) {
            int pageIndex = 0;
            bool foundInCache = false;
            for (i=0; i< C_SIZE; i++){
                if (cache[i].pageno == page_num){
                    foundInCache = true;
                    pageIndex = i;
                    break; // Break out loop because found page_num in cache.
                }
            }
            if (foundInCache == false) {
                ++totalFaults;
                printf("Page Fault: %d\n", page_num);
                // Go through the cache until we find an number with reference bit of 0.
                while (cache[placeInArray].ref_bit != 0) {
                    if (cache[placeInArray].pageno == -1) {
                        // If there is space in the cache, add a new page and break.
                        cache[placeInArray].pageno = page_num;
                        break;
                    }
                    if (cache[placeInArray].ref_bit == 1) {
                        // Give the number a second chance, change reference bit to 0.
                        cache[placeInArray].ref_bit = 0;
                    }
                    placeInArray = (placeInArray + 1) % C_SIZE;
                }
                // Replace the first found page number with reference bit 0.
                cache[placeInArray].pageno = page_num;
                placeInArray = (placeInArray + 1) % C_SIZE;
            }
            else {
                // The page is already in the cache: change the reference bit to 1.
                cache[pageIndex].ref_bit = 1;
            }
            
        }
            
    }
    
    float hitRate = ((float)numRequests - (float)totalFaults) / (float)numRequests;

    printf("numMisses: %d\n", totalFaults);
    printf("numRequests: %d\n", numRequests);
    printf("Hit Rate: %.6f\n", hitRate);
    
    return 0;



}

