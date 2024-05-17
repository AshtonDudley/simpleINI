#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define MAX_BUFFER_SIZE 1027

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* key;
    char* value;
} token_data_t;



// Extracts a string between two quotations marks.
// Returns NULL if no string is found.
const char* extractStringToken(const char* token) {

    char line[MAX_BUFFER_SIZE]; // Copy of the input
    char* stringValue;            // The result with the quotes

    strcpy(line, token);

    stringValue = strtok(line, "\"");     // Find the first double quote
    stringValue = strtok(NULL, "\"");     // Find the second double quote

    return stringValue;
}

// Returns a string matched to a given key.
// Returns NULL if no string is found.
const char* readString(FILE* fptr, const char* key) {

}

int readAll(FILE* fptr) {
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
            int i = 0;
            
            token_data_t data;

            while (token != NULL) {
                // Get the next token
                if (token != NULL) {
                    token[strcspn(token, "\n")] = '\0';
                    fprintf(stderr, "DEBUG: %s\n", token);
                    
                    
                    if (i == 0) {
                        data.key = token;
                        fprintf(stderr, "KEY  : %s\n", data.key);
                    }

                    // Check if token contains a stirng 
                    char *subString = extractStringToken(token);
                    if (i == 1 && subString) {
                        data.value = subString;
                        fprintf(stderr, "VALUE: %s\n", data.value);
                        // fprintf(stderr, "VALUE: %s\n", subString);
                    }
                    
                    
                    token = strtok_s(NULL, delimiter, &next_token);

                    // fprintf(stderr, "INDEX: %d\n", i);
                    i++;
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
    readAll(fptr);
    fclose(fptr);

    return 0;
}