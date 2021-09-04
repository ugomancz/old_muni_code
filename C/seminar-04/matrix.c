#include <stdlib.h>
#include <stdio.h>
#include <limits.h>



void fillMatrix(int minValue, int maxValue, size_t mrows, size_t mcols, int matrix[mrows][mcols]);
void printMatrix(size_t mrows, size_t mcols, int matrix[mrows][mcols]);
void multiplyMatrix(int mrows, int mcols, int matrix[mrows][mcols], int number);
int findMaxMinInArray(size_t length, int *array, int *max, int *min);
int findMaxMinPointers(size_t length, int *array, int **max, int **min);
int findPalindromes(size_t mrows, size_t mcols, int matrix[mrows][mcols], short palindromes[mrows]);

int main(void)
{
    int matrix[10][10] = {{0}};
    printf("matrix is pointing to %p with size of %zu bytes\n", (void*) matrix, sizeof (matrix));
    printf("matrix[0] is pointing to %p with size of %zu bytes\n", (void*) matrix[0], sizeof (matrix[0]));
    printf("matrix[1] is pointing to %p with size of %zu bytes\n", (void*) matrix[1], sizeof (matrix[1]));
    printf("matrix[1][1] is pointing to %p with size of %zu bytes\n", (void*) &matrix[1][1], sizeof (matrix[1][1]));
    fillMatrix(1, 100, 10, 10, matrix);
    printMatrix(10, 10, matrix);
    multiplyMatrix(10, 10, matrix, 2); //multiplies the matrix by 2
    printf("edited matrix:\n");
    printMatrix(10, 10, matrix);
    int min = INT_MAX;
    int max = INT_MIN;
    findMaxMinInArray(sizeof (matrix) / sizeof (int), (int*) matrix, &max, &min);
    printf("Max: %d, Min: %d\n", max, min);
    for (int i = 0; i < 10; i++){
       min = INT_MAX;
       max = INT_MIN;
       findMaxMinInArray(sizeof (matrix[0]) / sizeof (int), (int*) matrix[i], &max, &min);
       printf("Row no. %d, max: %d, min: %d\n", i, max, min);
    }
    int* minPointer = NULL;
    int* maxPointer = NULL;
    findMaxMinPointers(sizeof (matrix) / sizeof (int), (int*) matrix, &maxPointer, &minPointer);
    printf("Found max in matrix %p on coordinates %d, %d\n", (void*) maxPointer, (int) ((int) ((maxPointer - (int*) &matrix) / 10)), ((int) ((maxPointer - (int*) &matrix) % 10)));
    printf("Found min in matrix %p on coordinates %d, %d\n", (void*) minPointer, (int) ((minPointer - (int*) &matrix) / 10), (int) ((minPointer - (int*) &matrix) % 10));
    short palindromes[10];
    findPalindromes(10, 10, matrix, palindromes);
}


void fillMatrix(int minValue, int maxValue, size_t mrows, size_t mcols, int matrix[mrows][mcols])
{
    if (maxValue <= minValue) {
        return;
    }
    for (size_t i = 0; i < mrows; i++) {
        for (size_t j = 0; j < mcols; j++) {
            matrix[i][j] = rand() % (maxValue - minValue) + minValue;
        }
    }
}

void printMatrix(size_t mrows, size_t mcols, int matrix[mrows][mcols]) 
{
    for (size_t i = 0; i < mrows; i++) {
        for (size_t j = 0; j < mcols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void multiplyMatrix(int mrows, int mcols, int matrix[mrows][mcols], int number){
    for (int x = 0; x < mrows; x++){
        for (int y = 0; y < mcols; y++){
            matrix[x][y] *= number;
        }
    }
}

int findMaxMinInArray(size_t length, int *array, int *max, int *min)
{
    if (array == NULL || (max == NULL && min == NULL)) {
        return 0;
    }
    for (size_t i = 0; i < length; i++) {
        if (max && *max < array[i]) {
            *max = array[i];
        }

        if (min && *min > array[i]) {
            *min = array[i];
        }
    }
    return (max && min) ? 2 : 1;
}

int findMaxMinPointers(size_t length, int *array, int **max, int **min)
{
    int minTemp = INT_MAX;
    int maxTemp = INT_MIN;
    for (size_t i = 0; i < length; i++) {
        if (maxTemp < array[i]) {
            maxTemp = array[i];
            *max = &array[i];
        }

        if (minTemp > array[i]) {
            minTemp = array[i];
            *min = &array[i];
        }
    }
    return (max && min) ? 2 : 1;
}

int palindromeCheck(int* min, int* max){
    short counter = 0;
    while (*min < *max){
        if (*(min + counter) == *(max - counter)){
            min += counter;
            max -= counter;
            continue;
        } else return 0;
    }
    return 1;
}

int findPalindromes(size_t mrows, size_t mcols, int matrix[mrows][mcols], short palindromes[mrows]){
    int counter = 0;
    for (short i = 0; i < (short) mrows; i++){
        short isPalindrome = 0;
        isPalindrome = (short) palindromeCheck(matrix[i], matrix[i + (int) sizeof (matrix[i]) / (int) sizeof (int)]);
        counter += isPalindrome;
        palindromes[i] = isPalindrome;
    }
    return counter;
}


