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

    stringValue = strtok(line, "\"");     // Find the first double quote
    stringValue = strtok(NULL, "\"");     // Find the second double quote

    return stringValue;
}

// Returns a string matched to a given key.
// Returns NULL if no string is found.
const char* readString(FILE* fptr, char* key) {
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
                fprintf(stderr, "DEBUG: Memory allocation failed\n");
                return NULL;
            }

            // Split the string into tokens 
            token = strtok_s(currentLine, delimiter, &next_token);
            // token[strcspn(token, "\n")] = '\0';
            
             if (strcmp(stripWhitespace(currentLine), key) == 0) {
                char* subString = extractStringToken(next_token);
                if (next_token){
                    return subString; 
                }
                return NULL;
            }



        }
    }
    return NULL;
}

// Reads and pritns the entire contents of an .ini file
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


void stringsTest() {
    // Test 1
    FILE* fptr = fopen("config.ini", "r");
    if (fptr == NULL) {
        perror("Failed to open .ini file");
        return EXIT_FAILURE;
    }

    char* sn1 = readString(fptr, "serialNumber");
    fprintf(stdout, "GOOD  : %s\n", sn1);
    fclose(fptr);

    // Test 2
    fptr = fopen("config.ini", "r");
    if (fptr == NULL) {
        perror("Failed to open .ini file");
        return EXIT_FAILURE;
    }

    char* sn2 = readString(fptr, "serialNumber ");
    fprintf(stdout, "SERIAL: %s\n", sn2);
    fclose(fptr);

    // Test 3
    fptr = fopen("config.ini", "r");
    if (fptr == NULL) {
        perror("Failed to open .ini file");
        return EXIT_FAILURE;
    }

    char* sn3 = readString(fptr, "serialNumberrr");
    fprintf(stdout, "SERIAL: %s\n", sn3);
    fclose(fptr);

    // Test 4
    fptr = fopen("config.ini", "r");
    if (fptr == NULL) {
        perror("Failed to open .ini file");
        return EXIT_FAILURE;
    }

    char* sn4 = readString(fptr, "serialNumbe");
    fprintf(stdout, "SERIAL: %s\n", sn4);
    fclose(fptr);
    return;
}

int main()
{
    printf("Hello, World!\n");
    stringsTest();   

    return 0;
}