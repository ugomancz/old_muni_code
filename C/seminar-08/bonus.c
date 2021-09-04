//
// Created by xkostik on 12-Apr-20.
//
#include <assert.h>
#include "readline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getPackets(FILE *in, int *result) {
    assert(in != NULL);
    char *line;
    while ((line = readline(in)) != NULL) { // for each line in input
        char *packet = strtok(line, " ");
        for (int i = 0; i < 10; i++) { // sets packet to point to 11th element of line
            packet = strtok(NULL, " ");
        }
        if (packet == NULL) {
            fprintf(stderr, "Input file in wrong format\n");
            return EXIT_FAILURE;
        }
        *result += strtol(packet, (char **) strtok(NULL, " "), 10);
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s INPUT\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE *input = fopen(argv[1], "r");
    int packets = 0;
    if (getPackets(input, &packets) == EXIT_FAILURE) {
        fclose(input);
        fprintf(stderr, "Couldn't complete the program\n");
        return EXIT_FAILURE;
    }
    fclose(input);
    printf("%d packets found\n", packets);
    return EXIT_SUCCESS;
}