#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define MAX_BUFFER_SIZE 1027

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "simpleINI.h"


void stringsTest() {
    // Test 1
    char sn1[MAX_BUFFER_SIZE];
    FILE* fptr = fopen("config.ini", "r");
    if (fptr == NULL) {
        perror("Failed to open .ini file");
    }

    int rc = readString(fptr, sn1, "serialNumber");
    fclose(fptr);

    if (rc == 0) {
        fprintf(stdout, "OUTPUT: %s\n", sn1);
    }
    else {
        fprintf(stdout, "ERROR  : NULL\n");
    }

    // Test 2
    char sn2[MAX_BUFFER_SIZE];
    fptr = fopen("config.ini", "r");
    if (fptr == NULL) {
        perror("Failed to open .ini file");
    }

    rc = readString(fptr, sn2, "serialNumbe");
    fclose(fptr);

    if (rc == 0) {
        fprintf(stdout, "OUTPUT: %s\n", sn2);
    }
    else {
        fprintf(stdout, "ERROR : NULL\n");
    }

    // Test 3
    char sn3[MAX_BUFFER_SIZE];
    fptr = fopen("config.ini", "r");
    if (fptr == NULL) {
        perror("Failed to open .ini file");

    }

    rc = readString(fptr, sn3, "maxFrameCount");
    fclose(fptr);

    if (rc == 0) {
        fprintf(stdout, "OUTPUT: %s\n", sn3);
    }
    else {
        fprintf(stdout, "ERROR : NULL\n");
    }
}


int main()
{
    printf("Hello, World!\n");
    stringsTest();

    return 0;
}