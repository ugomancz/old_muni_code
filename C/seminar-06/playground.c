#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamicLib.h"

void playDynamicStringCopy()
{
    const char *orig = "Ahoj svet !";
    char *copy = dynamicStringCopy(orig);
    printf("Original: %s\n", orig);
    printf("Copy: %s\n", copy);
    free(copy);
}

void playDynamicStringJoin()
{
    const char *ahoj = "Ahoj ";
    const char *svet = "svet!";
    char *result = dynamicStringJoin(ahoj, svet);
    printf("Joined strings: \"%s\"\n", result);
    free(result);
}

void playReadLine()
{
    printf("Write something: ");
    char *line = readLine();
    printf("You have typed: \"%s\"\n", line);
    free(line);
}

void stringsPrinter(char **array, size_t size)
{
    for (int i = 0; i < (int)size; i++) {
        printf("%d - \"%s\"\n", i + 1, array[i]);
    }
}

void playSplit()
{
    const char *orig = "carrot, bannana, orange, kebab, mouse";
    size_t size;
    char **split = dynamicStringSplitSub(orig, ", ", &size);
    printf("Original string: %s\n", orig);
    printf("Splited:\n");
    stringsPrinter(split, size);
    for (size_t i = 0; i < size + 1; i++) {
        free(split[i]);
    }
    free(split);
}

int main()
{
    playDynamicStringCopy();
    playDynamicStringJoin();
    //playReadLine();
    //playSplit();

    return 0;
}
