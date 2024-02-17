// Name: Laurence Kim
// Date: 03/11/2022 
// Title: Lab 9.5
// Description: measure time of step 4 with threads.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Define the threadInfo struct so thread information can be easily transferred.
struct threadInfo {
    char * readFileName;
    int threadNumber;
    int buffer_size;
};

// Read from a file and write to a new file.
void* readAndWrite(void *info) {
    char* readFileName = ((struct threadInfo*)info)->readFileName;
    int threadNumber = ((struct threadInfo*)info)->threadNumber;
    int buffer_size = ((struct threadInfo*)info)->buffer_size;
    
    FILE *readFile;
    readFile = fopen(readFileName, "rb");
    
    char buffer[buffer_size];
    
    // Create and open a new file.
    FILE *new_file;
    char newFileName[25];
    sprintf(newFileName, "step5results/%d.txt", threadNumber);
    new_file = fopen(newFileName, "wb");
    
    while (fread(buffer, sizeof(buffer), 1, readFile)){
        // Write into the new file.
        fwrite(&buffer, sizeof(buffer), 1, new_file);
    }
    
    fclose(new_file);
    fclose(readFile);
    return 0;
}

int main(int argc, char *argv[]) {
    int buffer_size = atoi(argv[2]);
    char buffer[buffer_size]; // Use the user input to create the buffer.
    
    // Use the user input to decide the number of threads.
    int numberofThreads = atoi(argv[3]);
    int threadNumbers[numberofThreads];
    pthread_t threads[numberofThreads];
    
    for (int i = 0; i < numberofThreads; i++) {
        threadNumbers[i] = i;
        
        // Create a new thread.
        struct threadInfo* info = (struct threadInfo*)malloc(sizeof(struct threadInfo));
        info->readFileName = argv[1]; // Use the user input to choose the file.
        info->threadNumber = threadNumbers[i];
        info->buffer_size = buffer_size;
        
        pthread_create(&threads[i], NULL, readAndWrite, (void*)info);
        
//        free(info);
    }
    
    for (int i = 0; i < numberofThreads; i++) {
        pthread_join(threads[i], NULL);
    }
}

