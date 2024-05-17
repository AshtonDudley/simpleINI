#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define MAX_BUFFER_SIZE 1027

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Extracts a string between two quotations marks.
// Returns NULL if no string is found.
const char* extractStringToken(const char* token) {

    char line[MAX_BUFFER_SIZE]; // Copy of the input
    char* subString;            // The result with the quotes

    strcpy(line, token);

    subString = strtok(line, "\"");     // Find the first double quote
    subString = strtok(NULL, "\"");     // Find the second double quote

    return subString;
}

int readString(FILE* fptr) {
    char fileInput[MAX_BUFFER_SIZE];
      
    while (fgets(fileInput, MAX_BUFFER_SIZE, fptr)) {
        
        
        if (validLine(fileInput))
        {
            // fprintf(stderr, "%s", fileInput); // Print the entire file

            char* token;
            char* next_token = NULL;
            char delimiter[] = "=";
            char* currentLine = _strdup(fileInput);

            if (currentLine == NULL) {
                fprintf(stderr, " Memory allocation failed\n");
                return -1;
            }

            // Split the string into tokens 
            token = strtok_s(currentLine, delimiter, &next_token);
            
            while (token != NULL) {
                // Get the next token
                if (token != NULL) {
                    token[strcspn(token, "\n")] = '\0';
                    fprintf(stderr, "DEBUG: %s\n", token);
                    
                    // Check if token contains a stirng 
                    char *subString = extractStringToken(token);
                    if (subString) {
                        fprintf(stderr, "TOKEN: %s\n", subString);
                    }
                    
                    
                    token = strtok_s(NULL, delimiter, &next_token);

                }
            }
            fprintf(stderr, "\n");
            free(currentLine);
        }
    }

    return 0;
}



int validLine(char* line) {
    if (line[0] == '#') {
        return 0;
    }
    if (line[0] == '\n') {
        return 0;
    }
    return 1;
}


int main()
{
    printf("Hello, World!\n");
    FILE* fptr = fopen("config.ini", "r");

    if (fptr == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    readString(fptr);
    fclose(fptr);

    return 0;
}