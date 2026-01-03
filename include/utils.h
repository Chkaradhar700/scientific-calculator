#ifndef UTILS_H
#define UTILS_H

/*
 * Declares general utility functions used across multiple modules.
 */


void printError(int, int);

void writeInString(char[], int, int, char const *);
void deleteFromString(char[], int, int, int);
char *copyFromString(char[], int, int);

void scan(char *, int);
void emptyBuffer();


#endif /* UTILS_H */