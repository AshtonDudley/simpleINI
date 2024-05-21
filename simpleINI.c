#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define MAX_BUFFER_SIZE 1027

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "simpleINI.h"

typedef struct {
    char* key;
    char* value;
} token_data_t;

// Returns 0 if a vaild string ini entry is found
int validStringLine(char* line) {
    if (line[0] == '#') {
        return 0;
    }
    else if (line[0] == '\n') {
        return 0;
    }
    // Check if input is a vaild string type
    else if (strchr(line, '\"') == NULL)
    {
        return 0;
    }
    return 1;
}

// Returns 0 if a vaild int ini entry is found
int validStringLine(char* line) {
    if (line[0] == '#') {
        return 0;
    }
    else if (line[0] == '\n') {
        return 0;
    }
    // Check if input is a vaild string type
    else if (strchr(line, '\"') == NULL)
    {
        return 0;
    }
    return 1;
}


char* stripWhitespace(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';
    return str;
}


// Extracts a string between two quotations marks.
// Returns NULL if no string is found.
const char* extractStringToken(const char* token) {

    char line[MAX_BUFFER_SIZE]; // Copy of the input
    char* stringValue;            // The result with the quotes

    strcpy(line, token);
    // Check if the token contains a vaild string
    int stringCheck = strchr(line, '\"') != NULL;
    if (!stringCheck) {
        return NULL;
    }

    stringValue = strtok(line, "\"");     // Find the first double quote
    stringValue = strtok(NULL, "\"");     // Find the second double quote

    return stringValue;
}

// Returns a string matched to a given key.
// Returns 0 if a string is found.
int readString(FILE* fptr, char* returnString, char* key) {
    char fileInput[MAX_BUFFER_SIZE];

    while (fgets(fileInput, MAX_BUFFER_SIZE, fptr)) {


        if (validStringLine(fileInput))
        {
            // fprintf(stderr, "%s", fileInput); // Print the entire file

            char* token;
            char* next_token = NULL;
            char delimiter[] = "=";
            char* currentLine = _strdup(fileInput);

            if (currentLine == NULL) {
                fprintf(stderr, "DEBUG: Memory allocation failed\n");
                return -1;
            }

            // Split the string into tokens 
            token = strtok_s(currentLine, delimiter, &next_token);
            // token[strcspn(token, "\n")] = '\0';
            
             if (strcmp(stripWhitespace(currentLine), key) == 0) {
                char* subString = extractStringToken(next_token);

                if (next_token){
                    strcpy(returnString, subString);
                    return 0; 
                }
                return -1;
            }
        }
    }
    return -1;
}
