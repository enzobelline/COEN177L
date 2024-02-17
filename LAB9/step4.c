// Name: Laurence Kim
// Date: 03/11/2022 
// Title: Lab 9.4
// Description: measure time it takes to read and write to a new file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int buffer_size = atoi(argv[2]);
    char buffer[buffer_size]; // Use the user input to create the buffer.
    
    FILE *fp;
    fp = fopen(argv[1], "rb"); // Use the user input to choose a file.
    
    // Create and open a new file.
    FILE *new_file;
    new_file = fopen("newfile.txt", "wb");
    
    while (fread(buffer, sizeof(buffer), 1, fp)){
        // Write into the new file.
        fwrite(&buffer, sizeof(buffer), 1, new_file);
    }
    
    fclose(new_file);
    fclose(fp);
}

