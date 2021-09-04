#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline(FILE *file)
{
    assert(file);
    size_t capacity =  0u;
    size_t length =  0u;
    size_t chunkSize = 64u;
    size_t offset =  0u;
    char *memory = NULL;
    char *tmp;

    do {
        // increase buffer size
        capacity += chunkSize;
        if ((tmp = realloc(memory, capacity)) == NULL) {
            free(memory);
            return NULL;
        }

        // read next chunk
        memory = tmp;
        tmp = memory + length - offset;

        if (fgets(tmp, chunkSize + offset, file) == NULL)
            break;

        offset  = 1;
        length += chunkSize;

        // found newline?
    } while (strchr(tmp, '\n') == NULL);

    if (length == 0u || ferror(file)) {
        free(memory);
        return NULL;
    }

    return memory;
}
