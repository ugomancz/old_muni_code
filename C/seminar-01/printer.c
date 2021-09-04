#include <stdio.h>

int main(void)
{
    int number = 12;
    long long longNumber = 0x27BFE;
    double floatingNumber = 2.71828182;
    char singleChar = 'A';
    char string[] = "This is string";

    /* Zde definujte formatovaci retezce */
    printf("Number is: %d\n", number);
    printf("Long number is: %llx in hexadecimal\n", longNumber);
    printf("Long number is: %lld in decimal\n", longNumber);
    printf("Floating number is: %.8f\n", floatingNumber);
    printf("Floating number is: %.4f with precision to 4 decimal places\n", floatingNumber);
    printf("Char is: \'%c\'\n", singleChar);
    printf("String is: \"%s\"\n", string);
    return 0;
}
