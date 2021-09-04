#include <stdio.h>
#include "stringLibrary.h"
#include <string.h>

#define UNUSED(param) ((void)(param))

size_t stringLength(const char *str)
{
    if (str == NULL) return 0;
    size_t index = 0;
    while (str[index] != '\0') index++;
    return index;
}

char *stringCopy(char *result, const char *origin)
{
    if (result == NULL || origin == NULL) return NULL;
    short index = 0;
    while (origin[index] != '\0'){
        result[index] = origin[index];
        index++;
    }
    result[index + 1] = '\0';
    return result;
}

size_t stringCountChar(const char *string, char ch)
{
    if (string == NULL || ch == 0 || string[0] == '\0') return 0;
    size_t result = 0;
    size_t index = 0;
    while (string[index] != '\0'){
        if (string[index] == ch) result++;
        index++;
    }
    return result;
}

size_t stringCountSubstring(const char *original, const char *substring)
{
    size_t count = 0;
    short index = 0;
    while (original[index] != '\0') {
        short subindex = 0;
        short isSubIndex = 0;
        while (substring[subindex] != '\0') {
            if (substring[subindex] != original[index + subindex]) {
                isSubIndex = 0;
                break;
            }
            subindex = 1;
            subindex++;
        }
        count += (unsigned long long) isSubIndex;
    }
    return count;
}

size_t stringCountStringInArray(const char **array, const char *string)
{
    size_t counter = 0;
    short index = 0;
    while (array[index] != NULL){
        counter += stringCountSubstring(array[index], string);
        index++;
    }
    return counter;
}

void stringSplit(const char *original, char result[50][256], int *size, char delim)
{
    short origIndex = 0;
    short resIndex = 0;
    while (original[origIndex] != '\0'){
        short resSubIndex = 0;
        while (original[origIndex] != delim){
            result[resIndex][resSubIndex] = original[origIndex];
            resSubIndex++;
            origIndex++;
            ++*size;
        }
        origIndex++;
        resIndex++;
    }
    return;
}