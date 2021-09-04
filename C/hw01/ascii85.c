#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIV 85
#define ADDEND 33
#define BYTE 8
#define INPUT_LENGTH 5
#define MIN_VALUE 33
#define MAX_VALUE 117

uint32_t divideEncode(uint32_t input, uint8_t times){
    uint32_t result = input;
    for (uint8_t i = 0; i < times; i++){
        result = result / DIV;
    }
    return result;
}
/*
 * Converts input and prints
 */
void printEncode(uint32_t input) {
  uint32_t a = input % DIV;
  uint32_t b = (divideEncode(input, 1)) % DIV;
  uint32_t c = (divideEncode(input, 2)) % DIV;
  uint32_t d = (divideEncode(input, 3)) % DIV;
  uint32_t e = (divideEncode(input, 4)) % DIV;
  printf("%c%c%c%c%c", e + ADDEND, d + ADDEND, c + ADDEND, b + ADDEND, a + ADDEND);
}

int encode(void) {
  uint32_t input = 0;
  int16_t letter;
  uint8_t counter = 0;
  while ((letter = (int16_t) getchar()) != EOF) {
    input = input | (((uint32_t) letter) << BYTE * (3 - counter)); //shifts bytes to the right position
    counter++;
    if (counter == 4) { //prints the output every 4 read bytes
      counter = 0;
      printEncode(input);
      input = 0;
    }
  }
  if (counter != 0) { // prints last sequence if input length wasn't % 4 == 0
    printEncode(input);
  }
  putchar('\n');
  return 0;
}
/*
 * Converts input and prints
 */
int printDecode(const uint8_t * input) {
  uint32_t output = ((((input[0] - ADDEND) * DIV + input[1] - ADDEND) *
          DIV + input[2] - ADDEND) * DIV + input[3] - ADDEND) * DIV + (input[4] - ADDEND);
  uint8_t a = (uint8_t)(output >> (BYTE * 3));
  uint8_t b = (uint8_t)(output >> (BYTE * 2));
  uint8_t c = (uint8_t)(output >> BYTE);
  printf("%c%c%c%c", a, b, c, (uint8_t) output);
  return 0;
}

int decode(void) {
  uint8_t input[INPUT_LENGTH];
  int16_t letter;
  uint8_t counter = 0;
  while ((letter = (int16_t) getchar()) != EOF) {
    if (isspace(letter) != 0) { //skips whitespace chars
      continue;
    }
    if (letter < MIN_VALUE || letter > MAX_VALUE) { //checks for invalid input characters
      return 1;
    }
    input[counter] = (uint8_t) letter;
    counter++;
    if (counter == INPUT_LENGTH) { //5 chars have been read
      printDecode(input);
      counter = 0;
      memset(input, 0, INPUT_LENGTH * sizeof(uint8_t)); //nulls the "input" array
    }
  }
  if (counter != 0) { //length of input % 5 != 0
    return 1;
  }
  return 0;
}

// ================================
// DO NOT MODIFY THE FOLLOWING CODE
// ================================
int main(int argc, char * argv[]) {
  int retcode = 1;

  if (argc == 1 || (argc == 2 && strcmp(argv[1], "-e") == 0)) {
    retcode = encode();
  } else if (argc == 2 && strcmp(argv[1], "-d") == 0) {
    retcode = decode();
  } else {
    fprintf(stderr, "usage: %s [-e|-d]\n", argv[0]);
    return EXIT_FAILURE;
  }

  if (retcode != 0) {
    fprintf(stderr, "an error occured\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
