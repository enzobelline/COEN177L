// Name: Laurence Kim
// Date: 03/11/2022 
// Title: Lab 9.2
// Description: measure length file.

#include <stdio.h>

int main(int argc, char *argv[]) {
    char buffer[10000];
    FILE *fp;
    fp = fopen(argv[1], "rb"); // Reads in the file name.
    while (fread(buffer, sizeof(buffer), 1, fp)){
    }
    fclose(fp);
}

