#include <stdio.h>
#include <stdlib.h>

#define UNUSED(A) (void) A
#define BOARD_SIZE 20
#define STRING_SIZE 32

#define NOBODY_WON 0
#define XS_WON 1
#define OS_WON 2
#define DRAW 3

#define GAMEPLAY_OK 0
#define GAMEPLAY_ERROR 1

/**
 * Prints border between the lines of gameboard
 */
static void printBorder(void);

/**
 *  Prints one line of game
 *
 *  @param i number of line within gameboard
 *  @param line one line of gameboard
 */
static void printGameLine(size_t i, char line[BOARD_SIZE]);

/**
 * Prints whole gameboard
 *
 * @param board the board to be printed
 */
static void printGameBoard(char board[BOARD_SIZE][BOARD_SIZE]);

/**
 *  Function to initialize game board
 *
 *  @param board game board to be initialized
 *  @param initValue default value of the elements within the board
 */
void initGameBoard(char board[BOARD_SIZE][BOARD_SIZE], char initValue);

/**
 * Function to process single input into the game, store it and signalize 
 * error state if input is invalid 
 * TODO implement this function below
 *
 * @param board place where the game move is to be stored
 * @param playerName name of player that is expected to be playing now
 *
 * @return GAMEPLAY_OK if one turn has ended, GAMEPLAY_ERROR is returned, when
 * unrecorevable error is found (e.g. closed input)
 */
int playTurn(char board[BOARD_SIZE][BOARD_SIZE], short iteration, char playerNames[2][STRING_SIZE]);

/**
 * Function checks if the game board contains winning line.
 * Winning line is defined as sequence of same character of length 5
 * in same row, column or diagonal.
 *
 * @param board the game board to be checked
 *
 * @return NOBODY_WON when there is no winning sequence on the game board, {XS,OS}_WON when 
 * x player or o player won and DRAW when there is no free place on the gameboard to be filled 
 */
int checkWinningMove(char board[BOARD_SIZE][BOARD_SIZE]);

int main(void)
{
    char board[BOARD_SIZE][BOARD_SIZE] = {{0}};
    char playerNames[2][STRING_SIZE] = {{'\0'}, {'\0'}}; 
    initGameBoard(board, 'E');

    printf("Enter name of first player (x): ");

    if (scanf(" %31s", playerNames[0]) != 1) {
       printf("Invalid input for name!\n");
       return EXIT_FAILURE;
    } 

    printf("Enter name of second player (o): ");
    if (scanf(" %31s", playerNames[1]) != 1) {
       printf("Invalid input for name!\n");
       return EXIT_FAILURE;
    } 
    
    int gameEnd = NOBODY_WON;
    short iteration = 0;

    while (!gameEnd) {
        if (playTurn(board, iteration, playerNames)) {
            printf("Unrecorevable error happened. Ending the game....\n");
            return EXIT_FAILURE;
        }
        
        gameEnd = checkWinningMove(board);
        iteration++;
    }

    if (gameEnd == DRAW) {
        printf("Nobody won, game si draw.\n"); 
    } else {
        printf("%s won the game\n", (gameEnd == XS_WON) ? playerNames[0] : playerNames[1]);
    }
     
    return 0;
}

int playTurn(char board[BOARD_SIZE][BOARD_SIZE], short iteration, char playerNames[2][STRING_SIZE])
{
    int currPlayer = iteration % 2;
    printf("It's %s's turn, enter two coordinates:\n", playerNames[currPlayer]);
    int x = 0;
    int y = 0;
    if (scanf(" %d %d", &x, &y) != 2){
        return GAMEPLAY_ERROR;
    }
    if (currPlayer) { // Os turn
        board[x][y] = 'O';
    } else board[x][y] = 'X'; // Xs turn
    printGameBoard(board);

    return GAMEPLAY_OK;
}

int checkWinningMove(char board[BOARD_SIZE][BOARD_SIZE])
{
    //TODO implement checking algorithm
    UNUSED(board);
    return XS_WON;
}

void printGameBoard(char board[BOARD_SIZE][BOARD_SIZE])
{
    printf("    ");
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        printf(" %2d ", (int) i);
    }
    printf("\n");
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        printBorder();
        printGameLine(i, board[i]);
    }
    printBorder();
}    
static void printBorder(void)
{
    printf("   +");
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        printf("---+");
    }
    printf("\n");
}

static void printGameLine(size_t line_no, char line[BOARD_SIZE])
{
    printf("%2d |", (int) line_no);
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        printf(" %c |", line[i]);
    }
    printf("\n");
}

void initGameBoard(char board[BOARD_SIZE][BOARD_SIZE], char initValue)
{
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = initValue;
        }
    }
}


