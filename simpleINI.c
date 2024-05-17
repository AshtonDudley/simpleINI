#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define MAX_BUFFER_SIZE 257

#include <stdio.h>
#include <stdbool.h>





int main()
{
    printf("Hello, World!\n");
    FILE* fptr = fopen("config.ini", "r");
    readString(fptr);
    fclose(fptr);
}

//
int readString(FILE* fptr) {
    char myString[MAX_BUFFER_SIZE];
    while (fgets(myString, MAX_BUFFER_SIZE, fptr)) {
        fprintf(stderr, "%s", myString);
    }
    return 0;
}