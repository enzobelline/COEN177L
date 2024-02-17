// Name: Laurence Kim
// Date: 03/11/2022 
// Title: Lab 9.3
// Description: measure time it takes to read each file for buffers of varying sizes.

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int buffer_size = atoi(argv[2]);
    char buffer[buffer_size]; // Use the user input to create the buffer.
    
    FILE *fp;
    fp = fopen(argv[1], "rb"); // Use the user input to choose a file.
    
    while (fread(buffer, sizeof(buffer), 1, fp)){
    }
    
    fclose(fp);
}

