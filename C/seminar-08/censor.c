#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readline.h"

#define UNUSED(VAR) \
    ((void) (VAR))

/**
 * Searches for \p search in each line of \p in and replaces it with
 * stars. The result is written into \p out.
 *
 * \param   search      string to censor
 * \param   in          input file
 * \param   out         output file
 * \return  0 on success, an arbitrary error code on failure
 */
int censor(const char *search, FILE *in, FILE *out)
{
    char* line;
    size_t filterLength = strlen(search);
    while ((line = readline(in)) != NULL) { // while there are lines of input file
        char* found;
        while ((found = strstr(line, search)) != NULL) { // while search is found on line
            for (int i = 0; i < (int) filterLength; i++) {
                *(found + i) = '*'; // replaces string with a string of '*'
            }
        }
        fputs(line, out); // saves modified line to the output file
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "usage: %s STRING SOURCE DESTINATION\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE* input = fopen(argv[2], "r");
    FILE* output = fopen(argv[3], "w");
    censor(argv[1], input, output);
    fclose(input);
    fclose(output);
    return EXIT_SUCCESS;
}
