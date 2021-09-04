#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Do *NOT* use ‹readline()› in this exercise! It will not work as you expect.
// #include "readline.h"

#define UNUSED(VAR) \
    ((void) (VAR))

/**
 * Reads 512 binary bytes from \p key and uses it as key to "encrypt"
 * each block of 512 from \p in. Resulting blocks are written to \p out.
 *
 * @param   key         the file to read key from
 * @param   in          input file
 * @param   out         output file
 * @return  0 on success, an arbitrary error code on failure
 */
int xorcrypt(FILE *key, FILE *in, FILE *out)
{
    int8_t keyInput[512] = {0};
    int8_t data[512] = {0};
    fread(keyInput, sizeof(int8_t), 512, key);
    while (!feof(in)) {
        fread(data, sizeof(int8_t), 512, in);
        for (int i = 0; i < 512; i++) {
            data[i] = data[i] ^ keyInput[i];
        }
        fwrite(data, sizeof(int8_t), 512, out);
        memset(data, 0, 512 * sizeof(int8_t));
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "usage: %s KEY INPUT OUTPUT\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE* key = fopen(argv[1], "wb");
    FILE* input = fopen(argv[2], "rb");
    FILE* output = fopen(argv[3], "wb");
    xorcrypt(key, input, output);
    fclose(key);
    fclose(input);
    fclose(output);
    return EXIT_SUCCESS;
}
