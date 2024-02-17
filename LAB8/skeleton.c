#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    int pageno;
    int ref_bit;
} ref_page;


int main(int argc, char *argv[]) {
    int C_SIZE = atoi(argv[1]); 
    ref_page cache[C_SIZE]; 
    char pageCache[100]; 
    int totalFaults = 0; 
    int numRequests = 0; 
    

    // 1 - FIFO, 2 - LRU, 3 - Second Chance
    int algorithm = atoi(argv[2]);
    int i;
    int placeInArray = 0;

    for (i = 0; i < C_SIZE; i++){ // Init cache array and ref bits.
        cache[i].pageno = -1;
        cache[i].ref_bit = 0;
    }
    while (fgets(pageCache, 100, stdin)) {
        
        // end of the file or empty line -> skip
        if (strlen(pageCache) <= 1) {
            continue;
        }
        
        int page_num = atoi(pageCache); // Store number as int.
        numRequests++;
        
        // FIFO
        if (algorithm == 1) {
            bool foundInCache = false;
            for (i=0; i< C_SIZE; i++){
                if (cache[i].pageno == page_num){
                    foundInCache = true;
                    break; //found page_num in cache.
                }
            }
            if (foundInCache == false){// If page not found in cache, replace current page with it.
                //printf("Page Fault: %d\n", page_num);
                cache[placeInArray].pageno = page_num;
                totalFaults++;
                placeInArray = (placeInArray + 1) % C_SIZE;
            }
        }
        
        // LRU
        // cache[0] is least recently used vs cache[C_SIZE - 1] is most recently used.
        if (algorithm == 2) {
            int cacheIndex = 0;
            bool foundInCache = false;
            for (i=0; i< C_SIZE; i++){
                if (cache[i].pageno == page_num){
                    foundInCache = true;
                    cacheIndex = i;
                    break; //found page_num in cache
                }
            }
            if (foundInCache == false){                // Add if there is room in the cache.
                //printf("Page Fault: %d\n", page_num);
                if (placeInArray < C_SIZE) {
                    cache[placeInArray].pageno = page_num;
                    placeInArray++;
                }
                else {//remove the LRU (cache[0]) and add  number to end.
                    for (i = 0; i < C_SIZE-1; i++) {
                        cache[i].pageno = cache[i+1].pageno;
                    }
                    cache[C_SIZE-1].pageno = page_num;
                }
                totalFaults++;
            }
            else {// If  number is in cache, move it to most recently used.
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
                    break; //found page_num in cache.
                }
            }
            if (foundInCache == false) {
                ++totalFaults;
                //printf("Page Fault: %d\n", page_num);
                // Iterate cache until hit of reference bit of 0.
                while (cache[placeInArray].ref_bit != 0) {
                    if (cache[placeInArray].pageno == -1) {
                        // If space in the cache, add a new page and break.
                        cache[placeInArray].pageno = page_num;
                        break;
                    }
                    if (cache[placeInArray].ref_bit == 1) {
                        // Give number a second chance by changing ref bit to 0.
                        cache[placeInArray].ref_bit = 0;
                    }
                    placeInArray = (placeInArray + 1) % C_SIZE;
                }
                // Replace first found page number with ref bit 0.
                cache[placeInArray].pageno = page_num;
                placeInArray = (placeInArray + 1) % C_SIZE;
            }
            else {
                // page is in cache: set  ref bit to 1.
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

