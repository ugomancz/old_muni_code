//
// Created by Wermington on 15.2.16.
//

#include "dynamicLib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define UNUSED(a) ((void)(a))

char *dynamicStringCopy(const char *str)
{
    if (str == NULL) return NULL;
    size_t sizeOfString = 10;
    char* newString = calloc(sizeOfString, sizeof (char));
    char* reallocatedString = newString;
    short index = 0;
    while (str[index] != '\0') {
        if (index % 10 == 9) { // if newString is full, allocates and initializes 10 more sizeof (char) to '\0'
            sizeOfString += 10;
            reallocatedString = realloc(newString, sizeOfString * sizeof (char));
            memset(reallocatedString + index, '\0', 10 * sizeof (char));
        }
        if (reallocatedString == NULL || newString == NULL) {
            fprintf(stderr, "Couldn't allocate memory\n");
            return 0;
        }
        newString = reallocatedString;
        newString[index] = str[index];
        ++index;

    }
    return newString;
}

char *dynamicStringJoin(const char *pre, const char *post)
{
    if (pre == NULL || post == NULL) return NULL;
    size_t newSize = 1;
    int index = 0;
    while (pre[index] != '\0') {
        ++newSize;
    }
    index = 0;
    while (post[index] != '\0') {
        ++newSize;
    }
    char* newString = calloc(newSize, sizeof (char));
    if (newString == NULL) {
        fprintf(stderr, "Couldn't allocate memory\n");
        return 0;
    }
    index = 0;
    char* middle = NULL;
    while (pre[index] != '\0') {
        newString[index] = pre[index];
        ++index;
    }
    middle = newString + index; // holds pointer to newString where post starts
    index = 0;
    while (post[index] != '\0') {
        *(middle + (size_t) index * sizeof (char)) = post[index];
        ++index;
    }
    return newString;

}

char *readLine()
{
    char* line = calloc(20, sizeof (char)); // initializes a 20 char array to '\0'
    char* reallocatedLine = line;
    int letter = 0; // stores the char from input
    short index = 0; // stores the index of input and line strings
    if (line == NULL) {
        fprintf(stderr, "Couldn't allocate memory\n");
        return 0;
    }
    while ((letter = getchar()) != EOF) {
        if (index % 20 == 19) { // line is almost full, more memory needs to be allocated
            reallocatedLine = realloc(line, sizeof (*line) + 10 * sizeof (char));
            memset(reallocatedLine + index, '\0', 10 * sizeof (char));
        }
        if (reallocatedLine == NULL) { // realloc couldn't allocate more memory
            fprintf(stderr, "Couldn't allocate more memory, input too long\n");
        }
        line[index] = (char) letter;
        ++index;
    }
    return line;
}

/*
 * Deallocates first "rows" rows of "array" and the the "array" itself.
 * Auxillery function to free already-allocated part of "array"
 * for dynamic2DAlloc.
 */
void deallocHalfDoneArray(void** array, int rows) {
    for (int i = 0; i <= rows; i++) {
        free(array[i]);
    }
    free(array);
}

void **dynamic2DAlloc(size_t rows, size_t colSizes[rows])
{
    if (rows == 0 || colSizes == NULL) {
        fprintf(stderr, "Invalid arguments\n");
        return NULL;
    }
    void** mainArray = calloc(rows, sizeof (void*)); // initializes an array of NULL pointers
    for (int i = 0; i < (int) rows; i++) {
        if (colSizes[i] == 0) continue; //skips allocating an empty array
        mainArray[i] = calloc(colSizes[i], sizeof (void*));
        if (mainArray[i] == NULL) {
            fprintf(stderr, "Couldn't allocate memory, requested array might be too big\n");
            deallocHalfDoneArray(mainArray, i); // frees previously allocated memory in case of error
            return NULL;
        }
    }
    return mainArray;
}

int dynamic2DFree(void **memory, size_t rows)
{
    if (memory == NULL || rows == 0) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }
    for (int i = 0; i < (int) rows; i++) { // frees nested arrays
        free(memory[i]);
    }
    free(memory); // frees the main array
    return 0;
}

/**
 * BONUSES
 */

unsigned **pascalTriangle(size_t depth)
{
    UNUSED(depth);
    return NULL;
}

/*
 * It ain't much and it doesn't work
 *
 * Has so many bugs, memory leaks etc. Not even worth fixing and
 * I'm not feeling like redoing this with some simpler solution.
 */
char **dynamicStringSplitSub(const char *orig, const char *splitter, size_t *size)
{
    if (orig == NULL || splitter == NULL || size == NULL) { // checks for invalid arguments
        fprintf(stderr, "Invalid arguments\n");
        return NULL;
    }
    size_t arraySize = 3;
    char** array = calloc(arraySize, sizeof (char*));
    //printf("array size set to: 3 char*\n");
    if (array == NULL) { // checks if allocation failed
        fprintf(stderr, "Couldn't allocate memory\n");
        return NULL;
    }
    int firstChar = 0;
    int index = 0;
    int shouldSplit = 0;
    int arrayIndex = 0;
    size_t sizeOfSplitter = 0;
    while (splitter[index] != '\0') {
        ++sizeOfSplitter;
        ++index;
    }
    index = 0;
    while (orig[index] != '\0') {
        //printf("array size: %d\n", (int) (sizeof (array) / sizeof (char*)));
        //printf("sizeofsplitter: %d\n", sizeOfSplitter);
        for (int i = 0; i < (int) sizeOfSplitter; i++) {
            if (splitter[i] != orig[index + i]) break;
            ++shouldSplit;
        }
        //printf("1\n");
        if (shouldSplit != (int) sizeOfSplitter) {
            ++index;
            shouldSplit = 0;
            continue;
        }
        //printf("2\n");
        //printf("found a delimiter, follows: %c%c%c, arrayIndex: %d\n", orig[index +1], orig[index+2], orig[index+3], arrayIndex);
        array[arrayIndex] = calloc((size_t) (index - firstChar), sizeof (char));
        if (array[arrayIndex] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }
        //printf("3\n");
        //printf("allocated string at arrayIndex %d\n", arrayIndex);
        for (int j = 0; j < (index - firstChar - 1); j++) {
            array[arrayIndex][j] = orig[firstChar + j + 1];
        }
        //printf("4\n");
        //printf("added string to array[%d]\n", arrayIndex);
        index += (int) sizeOfSplitter - 1;
        firstChar = index;
        ++index;
        //printf("array[%d] = %s; ready for next iteration\n", arrayIndex, array[arrayIndex]);
        ++arrayIndex;
        ++(*size);
        shouldSplit = 0;
        if (arrayIndex % 3 == 2) {
            //printf("array not long enough\n");
            arraySize += 20;
            char** reallocatedArray = realloc(array, arraySize * sizeof (char*));
            printf("array size se to: %d\n", (int) arraySize);
            if (reallocatedArray == NULL) { // memory allocation failed
                free(reallocatedArray);
                free(array);
                fprintf(stderr, "Couldn't allocate more memory\n");
                return NULL;
            }
            //printf("allocated more memory\n");
            array = reallocatedArray;
        }
        //printf("5\n");
    }
    return array;
}
