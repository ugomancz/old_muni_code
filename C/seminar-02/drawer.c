#include <ctype.h>
#include <math.h>
#include <stdio.h>

void printChar(char a){
    putchar(a);
    putchar(a);
}

void drawLine(int length){
    if (length < 0){
        printf("You weren't gonna put in a negative number, were you? ;)\n");
        length = abs(length);
    }
    while (length != 0){
        putchar('#');
        length--;
    }
    putchar('\n');
}

void drawSquare(int side){
    for (int i = 0; i < side; i++){
        for (int j = 0; j < side; j++){
            printChar('#');
        }
        putchar('\n');
    }
}

void drawRectangle(int a, int b, char fill){
    for (int i = 0; i < a; i++){
        for (int j = 0; j < b; j++){
            printChar(fill);
        }
        putchar('\n');
    }
}

int myPow(int a, int b){
    int result = a;
    for (int i = 1; i<b; i++){
        result = result*a;
    }
    return result;
}

void drawCircle(int radius, char fill, char space){
    if (radius < 0 || isspace(fill) != 0 || isspace(space) != 0){
        perror("wrong input");
        return;
    }
    for (int i = -radius; i <= radius; i++){
    	if (i == 0) continue;
        for (int j = -radius; j <= radius; j++){
            if (i*i + j*j <= radius*radius){
                printChar(fill);
            }
            else {
                printChar(space);
            }
        }
        putchar('\n');
    }
}

void drawEllipse(int aAxis, int bAxis, char fill, char space){ //aAxis je x
    if (aAxis < 0 || bAxis < 0 || isspace(fill) != 0 || isspace(space) != 0){
        perror("wrong input");
        return;
    }
    for (int x = -bAxis; x <= bAxis; x++){
        for (int y = -aAxis; y <= aAxis; y++){
            if (x*aAxis*x*aAxis+y*bAxis*y*bAxis < aAxis*aAxis*bAxis*bAxis){
                printChar(fill);
            }
            else printChar(space);
        }
        putchar('\n');
    }
}

int main(void)
{
    int aAxis;
    int bAxis;
    char fill;
    char space;
  /*  if (scanf(" %d %d %c %c", &aAxis, &bAxis, &fill, &space) != 4){
        return 1;
    }
    drawEllipse(aAxis, bAxis, fill, space); //vyska, sirka, fill, space*/
    drawCircle(10, '#', '^');
    printf("Zde se bude kreslit!\n");
    return 0;
}
