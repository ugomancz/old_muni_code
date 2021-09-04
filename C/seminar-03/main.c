#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Zadejte 10 cislic: ");
    int input[10];
    for (int i = 0; i <10; i++){
        scanf(" %i", &(input[i]));
    }
    return 0;
}
