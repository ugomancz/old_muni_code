#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "asciifont.h"

#define UNUSED(var) ((void) (var))

int scanInput(char input[]) // scans and checks the validity of input
{
    for (int i = 0; i < 101; i++) {
        int temp = getchar();
        if (temp == '\n' || temp == EOF) {
            input[i] = '\0';
            break;
        }
        if (temp > 127) {
            perror("Wrong input!");
            return -1;
        }
        input[i] = (char) (temp);
    }
    return 0;
}

void printRow(const unsigned char x) // prints one row of ASCII letter
{
    for (unsigned char i = 0; i < 8; i++) {
        unsigned char mask = 128;
        mask = (unsigned char) (mask >> i);
        if ((x & mask) > 0) {
            printf("#");
        } else {
            printf(" ");
        }
    }
}

void printASCII(char input[], int row_length, int input_position) // takes individual rows of characters and sends them to printRow
{
    int temp_value = 1;
    for (int iteration = 0; temp_value != 0; iteration++){
        for (int i = 0; i < 8; i++) {
            for (int j = 0; input[j + input_position * iteration] != '\0'; j++) {
                if ((j+1) * 8 > row_length) { // checks whether a letter surpasses maximum length of printed characters
                    temp_value = j;
                    break;
                }
                printRow(FONT_DATA[(int) input[j + input_position * iteration]][i]);
            }
            if (i != 7) {
                putchar('\n');
            }
        }
        if (temp_value > 0) {
            putchar('\n');
            break;
        }
        if (iteration == 0) {
            putchar('\n');
        }
    }
}
int main(int argc, char *argv[]) // works forpretty much every letter or a combination, except for NUL (0x00)
{
    if (argc != 2) { // verifies the argument
        perror("Wrong number of arguments!");
        return -1;
    }
    for (unsigned int i = 0; argv[1][i] != '\0'; i++) { // verifies the argument
        if (!isdigit(argv[1][i])){
            perror("Argument isn't a number");
            return -1;
        }
    }
    int row_length = atoi(argv[1]); // converts length argument from string to integer
    if (row_length < 8){            // verifies the argument
        perror("Too small argument, make it at least 8!");
        return -1;
    }
    char input[100];
    if (scanInput(input) == -1)
        return -1;
    if (input[0] == '\0') { // checks for an empty input
        return 0;
    }
    printASCII(input, row_length, 0);
    return 0;
}
