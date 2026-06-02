#include "../include/reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char inputBuffer[512] = {0};

const char *read() {
    if(!fgets(inputBuffer, sizeof(inputBuffer), stdin)) {
        exit(EXIT_FAILURE);
    }
    inputBuffer[strlen(inputBuffer)-1] = '\0';
    return inputBuffer;
}

const char *readInput(const char *print) {
    printf("%s", print);
    return read();
}

int readInt() {
    int this = 0;
    char *endptr = NULL;
    while(1) {
        read();
        endptr = &inputBuffer[strlen(inputBuffer)];
        this = strtol(inputBuffer, &endptr, 10);
        if(endptr != NULL) break;
    }
    return this;
}

char *csv_next(FILE *filePointer) {

    static char field[CSV_TOKEN_LENGTH] = {0};

    if(!filePointer) return 0;

    char retrievedChar = 0;

    while(1) {
        retrievedChar = getc(filePointer);

        if(retrievedChar == EOF) return 0;

        if(isalnum(retrievedChar)) {
            break;
        }
    }
    ungetc(retrievedChar, filePointer);

    for(int iField = 0; (retrievedChar = getc(filePointer)) && (isalnum(retrievedChar) || retrievedChar == ' '); ++iField) {
        field[iField] = retrievedChar;
    }

    char *toRemove = 0;
    if(*(toRemove = &field[strlen(field)-1]) == '\n') {
        *toRemove = '\0';
    }

    return field;
}