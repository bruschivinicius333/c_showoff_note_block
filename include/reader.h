#pragma once

#include <stdio.h>

#define CSV_TOKEN_LENGTH 512

extern char inputBuffer[512];

const char *read();
const char *readInput(const char *print);
int readInt();

char *csv_next(FILE *fp);