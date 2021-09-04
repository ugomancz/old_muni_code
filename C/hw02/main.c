#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_CARDS 7
#define CARDS_ON_TABLE 5
#define COMB_NOT_FOUND 50 // return code used by check-functions in case no combination is found

typedef enum Color {HEARTS, DIAMONDS, SPADES, CLUBS} Color; // used to represent the cards' color
typedef enum Value {EMPTY, TWO, THREE, FOUR, FIVE, SIX, SEVEN, // used to represent the cards' value
    EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE} Value;

typedef struct Card // represents one card
{
    Value value;
    Color color;
} Card;

typedef struct Player // struct used to represent one player's hand when checking (Straight) Flush
{
    int heartsIndex;
    Card hearts[NUMBER_OF_CARDS];
    int diamondsIndex;
    Card diamonds[NUMBER_OF_CARDS];
    int spadesIndex;
    Card spades[NUMBER_OF_CARDS];
    int clubsIndex;
    Card clubs[NUMBER_OF_CARDS];
} Player;

/*
 * Checks the validity of a card on input, converts it into struct Card, and saves it into Card* cards
 */
int processCard(char value, char color, Card* cards, int index) {
    if (!((value >= '2' && value <= '9') || value == 'A' || value == 'J' || // checks valid values
            value == 'K' || value == 'Q' || value == 'T')){
        fprintf(stderr, "Card with invalid value on input\n");
        return false;
    }
    if (!(color == 'c' || color == 'd' || color == 'h' || color == 's')) { // checks valid colors
        fprintf(stderr, "Card with invalid color on input\n");
        return false;
    }
    Card card = { 0 };
    if (value >= '2' && value <= '9') {
        card.value = (Value) (value - 49); // sets value for 2-9 cards
    }
    switch (value) {
    case 'T': // sets value for 10
        card.value = TEN;
        break;
    case 'J': // sets value for Jack
        card.value = JACK;
        break;
    case 'Q': // sets value for Queen
        card.value = QUEEN;
        break;
    case 'K': // sets value for King
        card.value = KING;
        break;
    case 'A': // sets value for Ace
        card.value = ACE;
        break;
    }
    switch (color) {
    case 'h': // sets color for Hearts
        card.color = HEARTS;
        break;
    case 'd': // sets color for Diamonds
        card.color = DIAMONDS;
        break;
    case 's': // sets color for Spades
        card.color = SPADES;
        break;
    case 'c': // sets color for Clubs
        card.color = CLUBS;
        break;
    }
    cards[index] = card;
    return true;
}

/*
 * Scans 2 cards from input, checks the input format and passes
 * cards to processCard(), if flag (bool) isEOFError is true,
 * prints error "Uncomplete instance".
 */
bool readHand(Card* cards, bool isEOFError) {
    char fst[2] = {0};
    char sec[2] = {0};
    int firstChar = getchar();
    if (firstChar == EOF) { //checks for EOF in case there are no more instances
        if (isEOFError) {
            fprintf(stderr, "Uncomplete instance\n");
        }
        return false;
    }
    fst[0] = (char) firstChar;
    if (scanf("%c", &fst[1]) != 1) {
        fprintf(stderr, "Card input in wrong format\n"); // scans the first card
        return false;
    }
    if (!isspace(getchar())) {
        fprintf(stderr, "Card input in wrong format\n"); // checks whitespace between cards
        return false;
    }
    if (!(processCard(fst[0], fst[1], cards, 0))) {
        return false;
    }
    if (scanf(" %c%c", &sec[0], &sec[1]) != 2) {
        fprintf(stderr, "Card input in wrong format\n"); // scans the second card
        return false;
    }
    if (getchar() != '\n') {
        fprintf(stderr, "Card input in wrong format\n"); // checks for \n at end of line
        return false;
    }
    if (processCard(sec[0], sec[1], cards, 1) != 0) {
        return false;
    }
    return true;
}

/*
 * Scans 5 cards from input, checks the input format and passes cards to processCard()
 */
bool readTable(Card* playerOne, Card* playerTwo) {
    char cards[CARDS_ON_TABLE][2] = {{0}};
    int firstChar = getchar();
    if (firstChar == EOF) {
        fprintf(stderr, "Uncomplete instance\n");
        return false;
    }
    cards[0][0] = (char) firstChar;
    if (scanf("%c", &cards[0][1]) != 1) {
        fprintf(stderr, "Card input in wrong format\n");
        return false;
    }
    if (!isspace(getchar())) { // checks whitespace between cards
        fprintf(stderr, "Card input in wrong format\n");
        return false;
    }
    for (int i = 1; i < CARDS_ON_TABLE; i++) {
        if (scanf(" %c%c", &cards[i][0], &cards[i][1]) != 2) {
            fprintf(stderr, "Card input in wrong format\n");
            return false;
        }
    }
    int ch = 0;
    if ((ch = getchar()) != '\n' || ch == EOF) { // checks for \n at end of line
        fprintf(stderr, "Card input in wrong format\n");
        return false;
    }
    for (int i = 0; i < CARDS_ON_TABLE; i++) {
        if (!(processCard(cards[i][0], cards[i][1], playerOne,  (i + 2)))) {
            return false;
        }
        if (!(processCard(cards[i][0], cards[i][1], playerTwo,  (i + 2)))) {
            return false;
        }
    }
    return true;
}

/*
 * Comparator for qsort(), compares two cards based on their value
 */
int compareCards(const void *card1, const void *card2) {
    return (int) (((const Card*) card1)->value - ((const Card*) card2)->value);
}

/*
 * Checks for duplicate cards
 * Prints error to stderr if duplicates found
 */
bool checkDuplicates(Card* playerOne, Card* playerTwo) {
    for (int i = 0; i < NUMBER_OF_CARDS; i++) {
        for (int j = 0; j < 2; j++){
            if (compareCards(&playerOne[i], &playerTwo[j]) == 0
                    && playerOne[i].color == playerTwo[j].color) {
                fprintf(stderr, "A duplicate card detected\n");
                return true;
            }
        }
        for (int k =  (i + 1); k < NUMBER_OF_CARDS; k++) {
            if (compareCards(&playerOne[i], &playerOne[k]) == 0
                    && playerOne[i].color == playerOne[k].color) {
                fprintf(stderr, "A duplicate card detected\n");
                return true;
            }
        }
    }
    return false;
}

/*
 * Checks who has the higher card
 * return > 0, if playerOne wins
 * return < 0, if playerTwo wins
 * return == 0, if it's a draw
 */
int checkHighCardAdvanced(Card* playerOne, Card* playerTwo, int sizeOfArray, int topIndex) {
    int result = 0;
    for (int i = sizeOfArray - 1; i >= sizeOfArray - topIndex; i--) {
        result = compareCards(&playerOne[i], &playerTwo[i]);
        if (result != 0) return result;
    }
    return result;
}
/*
 * FiltersCards with specified values
 * Returns new and sorted cards
 */
Card* removeCards(Card* cards, Card* newCards, int value) {
    for (int i = 0; i < NUMBER_OF_CARDS; i++) {
        if (cards[i].value != (Value) value) {
            newCards[i] = cards[i];
        }
    }
    qsort(newCards, NUMBER_OF_CARDS, sizeof (Card), compareCards); // sorts the cards [lowest -> highest]
    return newCards;
}

/*
 * Uses two player structs to store information about their cards
 * Switch appends cards from cardsOne and cardsTwo to correct lists of cards
 * in the structs.
 */
int checkFlush(Card* cardsOne, Card* cardsTwo) {
    Player playerOne = {NUMBER_OF_CARDS - 1, {{0}}, NUMBER_OF_CARDS - 1, {{0}},
                        NUMBER_OF_CARDS - 1, {{0}}, NUMBER_OF_CARDS - 1, {{0}}};
    Player playerTwo = {NUMBER_OF_CARDS - 1, {{0}}, NUMBER_OF_CARDS - 1, {{0}},
                        NUMBER_OF_CARDS - 1, {{0}}, NUMBER_OF_CARDS - 1, {{0}}};
    for (int i = NUMBER_OF_CARDS - 1; i >= 0; i--) {
        switch (cardsOne[i].color) { // parses playerOne's cards
        case HEARTS:
            playerOne.hearts[playerOne.heartsIndex] = cardsOne[i];
            playerOne.heartsIndex--;
            break;
        case DIAMONDS:
            playerOne.diamonds[playerOne.diamondsIndex] = cardsOne[i];
            playerOne.diamondsIndex--;
            break;
        case SPADES:
            playerOne.spades[playerOne.spadesIndex] = cardsOne[i];
            playerOne.spadesIndex--;
            break;
        case CLUBS:
            playerOne.clubs[playerOne.clubsIndex] = cardsOne[i];
            playerOne.clubsIndex--;
            break;

        }
        switch (cardsTwo[i].color) { // parses playerTwo's cards
        case HEARTS:
            playerTwo.hearts[playerTwo.heartsIndex] = cardsTwo[i];
            playerTwo.heartsIndex--;
            break;
        case DIAMONDS:
            playerTwo.diamonds[playerTwo.diamondsIndex] = cardsTwo[i];
            playerTwo.diamondsIndex--;
            break;
        case SPADES:
            playerTwo.spades[playerTwo.spadesIndex] = cardsTwo[i];
            playerTwo.spadesIndex--;
            break;
        case CLUBS:
            playerTwo.clubs[playerTwo.clubsIndex] = cardsTwo[i];
            playerTwo.clubsIndex--;
            break;
        }
    }
    Card* playerOneCards = 0;
    Card* playerTwoCards = 0;
    /*
     * Takes arrays of certain color, if they have 5 cards in them,
     * pointers to them are saved in playerOneCards/playerTwoCards
     */
    if (playerOne.heartsIndex < 2) {
        playerOneCards = playerOne.hearts;
    }
    if (playerOne.diamondsIndex < 2) {
        playerOneCards = playerOne.diamonds;
    }
    if (playerOne.spadesIndex < 2) {
        playerOneCards = playerOne.spades;
    }
    if (playerOne.clubsIndex < 2) {
        playerOneCards = playerOne.clubs;
    }
    if (playerTwo.heartsIndex < 2) {
        playerTwoCards = playerTwo.hearts;
    }
    if (playerTwo.diamondsIndex < 2) {
        playerTwoCards = playerTwo.diamonds;
    }
    if (playerTwo.spadesIndex < 2) {
        playerTwoCards = playerTwo.spades;
    }
    if (playerTwo.clubsIndex < 2) {
        playerTwoCards = playerTwo.clubs;
    }
    if (playerOneCards == NULL || playerTwoCards == NULL) {// checks for winner in case only one of them has Flush
        if (playerOneCards == NULL && playerTwoCards != NULL) return -1; // playerTwo has Flush
        if (playerOneCards != NULL && playerTwoCards == NULL) return 1; // playerOne has Flush
        return COMB_NOT_FOUND; // nobody has Flush
    }
    /*
     * Probably could just return checkHighCardAdvanced() without the if and remove the
     * last return, but I couldn't get the tests working and didn't wanna risk it
     */
    if (playerOneCards[NUMBER_OF_CARDS - 1].value != (Value) 0 && playerTwoCards[NUMBER_OF_CARDS - 1].value != (Value) 0) { // both players have Flush
        return checkHighCardAdvanced(playerOneCards, playerTwoCards, NUMBER_OF_CARDS, 5);
    }
    return (int) playerOneCards[NUMBER_OF_CARDS - 1].value - (int) playerTwoCards[NUMBER_OF_CARDS - 1].value;
}

/*
 * Checks whether a card with specified value and color is in the array
 */
bool checkCard(Card* cards, Value value, Color color) {
    for (int i =0; i < NUMBER_OF_CARDS; i++){
        if (cards[i].value == value){
            if (cards[i].color == color) return true;
        }
    }
    return false;
}

/*
 * Uses "bucketsort" to sort cards into arrays of cards with
 * indexes corresponding to the cards values. Those are then
 * checked from top index for straights - five  !0 values in the
 * array in row. Or 4 bottom values and an ACE.
 */
int checkStraight(Card* playerOne, Card* playerTwo){
    int playerOneCards[NUMBER_OF_CARDS * 2] = {0};
    int playerTwoCards[NUMBER_OF_CARDS * 2] = {0};
    int playerOneMaxCard = 0; // highest card of straight
    int playerTwoMaxCard = 0; // highest card of straight
    for (int i = 0; i < NUMBER_OF_CARDS; i++) {
        playerOneCards[(int) playerOne[i].value]++;
        playerTwoCards[(int) playerTwo[i].value]++;
    }
    for (int i = NUMBER_OF_CARDS * 2 - 1; i > 4; i--) { // non-ACE straights
        if (playerOneCards[i] > 0 && playerOneCards[i - 1] > 0 && playerOneCards[i - 2]
                && playerOneCards[i - 3] > 0 && playerOneCards[i - 4] > 0 && playerOneMaxCard == 0){
            playerOneMaxCard = i;
        }
        if (playerTwoCards[i] > 0 && playerTwoCards[i - 1] > 0 && playerTwoCards[i - 2]
                && playerTwoCards[i - 3] > 0 && playerTwoCards[i - 4] > 0 && playerTwoMaxCard == 0){
            playerTwoMaxCard = i;
        }
    }
    if (playerOneCards[NUMBER_OF_CARDS * 2 - 1] > 0 && playerOneCards[1] > 0 && playerOneCards[2] // playerOne ACE-straight check
            && playerOneCards[3] > 0 && playerOneCards[4] > 0 && playerOneMaxCard == 0){
        playerOneMaxCard = 4;
    }
    if (playerTwoCards[NUMBER_OF_CARDS * 2 - 1] > 0 && playerTwoCards[1] > 0 && playerTwoCards[2] // playerTwo ACE-straight check
            && playerTwoCards[3] > 0 && playerTwoCards[4] > 0 && playerTwoMaxCard == 0){
        playerTwoMaxCard = 4;
    }
    if (playerOneMaxCard == 0 && playerTwoMaxCard == 0) return COMB_NOT_FOUND; // nobody has a straight
    if (playerOneMaxCard > 0 && playerTwoMaxCard == 0) return 1; // playerOne has a straight, but playerTwo doesn't
    if (playerOneMaxCard == 0 && playerTwoMaxCard > 0) return -1; // playerTwo has a straight, but playerOne doesn't
    return playerOneMaxCard - playerTwoMaxCard; // both have straight, their highest cards' values are compared
}

/*
 * Uses "bucketsort" to sort cards into arrays of cards with
 * indexes corresponding to the cards values. Those are then
 * checked for two values of 2 and those pairs' values are saved.
 */
int checkTwoPairs(Card* playerOne, Card* playerTwo){
    int playerOneCards[NUMBER_OF_CARDS * 2] = {0};
    int playerTwoCards[NUMBER_OF_CARDS * 2] = {0};
    int playerOnePairOne = 0; // at 0 is number of such cards, at 1 is their value
    int playerOnePairTwo = 0; // at 0 is number of such cards, at 1 is their value
    int playerTwoPairOne = 0; // at 0 is number of such cards, at 1 is their value
    int playerTwoPairTwo = 0; // at 0 is number of such cards, at 1 is their value
    bool playerOneHasTwoPairs = false; // flag to represent whether playerOne has two pairs or not
    bool playerTwoHasTwoPairs = false; // flag to represent whether playerTwo has two pairs or not
    for (int i = 0; i < NUMBER_OF_CARDS; i++){
        playerOneCards[(int) playerOne[i].value]++;
        playerTwoCards[(int) playerTwo[i].value]++;
    }
    for (int i = NUMBER_OF_CARDS * 2 - 1; i > 0; i--) {
        if (playerOneCards[i] == 2) {
            if (playerOnePairOne == 0){
                playerOnePairOne = i;
            } else {
                if (playerOnePairTwo == 0) {
                    playerOnePairTwo = i;
                    playerOneHasTwoPairs = true;
                }
            }
        }
        if (playerTwoCards[i] == 2) {
            if (playerTwoPairOne == 0){
                playerTwoPairOne = i;
            } else {
                if (playerTwoPairTwo == 0){
                    playerTwoPairTwo = i;
                    playerTwoHasTwoPairs = true;
                }
            }
        }
    }
    if (playerOneHasTwoPairs == false && playerTwoHasTwoPairs == false) return COMB_NOT_FOUND; // nobody has two pairs
    if (playerOneHasTwoPairs == true && playerTwoHasTwoPairs == false) return 1; // playerOne has two pairs, playerTwo doesn't
    if (playerOneHasTwoPairs == false && playerTwoHasTwoPairs == true) return -1; // playerTwo has two pairs, playerOne doesn't
    if (playerOnePairOne - playerTwoPairOne != 0) { // win based upon higher pair
        return playerOnePairOne - playerTwoPairOne;
    }
    if (playerOnePairTwo - playerTwoPairTwo != 0) { // win based upon lower pair
        return playerOnePairTwo - playerTwoPairTwo;
    }
    /*
     * In case both have two pairs with same values as the other
     * player cards filtered from the pairs' values are stored in
     * temp and then final cards
     */
    Card tempPlayerOne[NUMBER_OF_CARDS] = {{0}};
    Card tempPlayerTwo[NUMBER_OF_CARDS] = {{0}};
    removeCards(playerOne, tempPlayerOne, playerOnePairOne);
    removeCards(playerTwo, tempPlayerTwo, playerTwoPairOne);
    Card finalPlayerOne[NUMBER_OF_CARDS] = {{0}};
    Card finalPlayerTwo[NUMBER_OF_CARDS] = {{0}};
    removeCards(tempPlayerOne, finalPlayerOne, playerOnePairTwo);
    removeCards(tempPlayerTwo, finalPlayerTwo, playerTwoPairTwo);
    return compareCards(&finalPlayerOne[NUMBER_OF_CARDS - 1], &finalPlayerTwo[NUMBER_OF_CARDS - 1]); // checks for highest card among the cards left
}

/*
 * Uses "bucketsort" to sort cards into arrays of cards with
 * indexes corresponding to the cards values. Those are then
 * checked for a value of nTuple and those pairs values are saved.
 * (int*) playerOneValue and (int*) playerTwoValue are used from
 * caller functions to store the found nTuples' values. (bool) check
 * is a flag whether to check for leftover highest cards, it's use
 * depends on the caller function
 */
int checkNOfAKind(Card* playerOne, Card* playerTwo, int nTuple, int* playerOneValue, int* playerTwoValue, bool check){
    int playerOneCards[NUMBER_OF_CARDS * 2] = {0};
    int playerTwoCards[NUMBER_OF_CARDS * 2] = {0};
    int playerOneCardValue = 0; // value of n-tuple of cards found
    int playerTwoCardValue = 0; // value of n-tuple of cards found
    for (int i = 0; i < NUMBER_OF_CARDS; i++){
        playerOneCards[(int) playerOne[i].value]++;
        playerTwoCards[(int) playerTwo[i].value]++;
    }
    for (int i = NUMBER_OF_CARDS * 2 - 1; i > 0; i--) { // saves value of highest nTuple for each player
        if (playerOneCards[i] >= nTuple && playerOneCardValue == 0) {
            playerOneCardValue = i;
            *playerOneValue = i;
        }
        if (playerTwoCards[i] >= nTuple && playerTwoCardValue == 0) {
            playerTwoCardValue = i;
            *playerTwoValue = i;
        }
    }
    if (playerOneCardValue == 0 && playerTwoCardValue == 0) return COMB_NOT_FOUND; // nobody has N of a kind
    if (playerOneCardValue != 0 && playerTwoCardValue == 0) return 1; // playerOne has N of a kind
    if (playerOneCardValue == 0 && playerTwoCardValue != 0) return -1; // playerTwo has N of a kind
    if (playerOneCardValue == playerTwoCardValue) { // they both have N of a kind with same card value
        if (check == false) return 0; // no checking for leftover highest cards
        Card newPlayerOne[NUMBER_OF_CARDS] = {{0}};
        Card newPlayerTwo[NUMBER_OF_CARDS] = {{0}};
        return checkHighCardAdvanced(removeCards(playerOne, newPlayerOne, playerOneCardValue),
                             removeCards(playerTwo, newPlayerTwo, playerTwoCardValue), NUMBER_OF_CARDS, 5 - nTuple);
    }
    return playerOneCardValue - playerTwoCardValue;
}

/*
 * Uses checkNOfAKind to check the cards for highest pairs
 * (int) playerOnePairValue, playerTwoPairValue is redundant
 * in here, but was neccessary to call the checkNOfAKind
 */
int checkPair(Card* playerOne, Card* playerTwo){
    int playerOnePairValue = 0;
    int playerTwoPairValue = 0;
    //printf("pair happens here:\n");
    return checkNOfAKind(playerOne, playerTwo, 2, &playerOnePairValue, &playerTwoPairValue, true);
}

/*
 * Uses checkNOfAKind to check the cards for highest 3-tuples
 * (int) playerOnePairValue, playerTwoPairValue is redundant
 * in here, but was neccessary to call the checkNOfAKind
 */
int checkThreeOfAKind(Card* playerOne, Card* playerTwo){
    int playerOneCardsValue = 0;
    int playerTwoCardsValue = 0;
    return checkNOfAKind(playerOne, playerTwo, 3, &playerOneCardsValue, &playerTwoCardsValue, true);
}

/*
 * Uses checkNOfAKind to check the cards for highest 4-tuples
 * (int) playerOnePairValue, playerTwoPairValue is redundant
 * in here, but was neccessary to call the checkNOfAKind
 */
int checkFourOfAKind(Card* playerOne, Card* playerTwo){
    int playerOneCardsValue = 0;
    int playerTwoCardsValue = 0;
    return checkNOfAKind(playerOne, playerTwo, 4, &playerOneCardsValue, &playerTwoCardsValue, true);
}

/*
 * Uses checkNOfAKind to find 3-tuple and a pair. checkNOfAKind's
 * (bool) check flag is set to false, because checking for highest
 * cards is not required here and messes up the results of the function
 */
int checkFullHouse(Card* playerOne, Card* playerTwo){
    int playerOnePairValue = 0;
    int playerTwoPairValue = 0;
    int playerOne3OAKValue = 0;
    int playerTwo3OAKValue = 0;
    bool playerOneHasFH = false;
    bool playerTwoHasFH = false;
    int threeOAKResult = checkNOfAKind(playerOne, playerTwo, 3, &playerOne3OAKValue, &playerTwo3OAKValue, false);
    if (threeOAKResult == COMB_NOT_FOUND) return COMB_NOT_FOUND; // no 3 of a kind found in either player's cards -> no Fullhouse
    Card newPlayerOne[NUMBER_OF_CARDS] = {{0}};
    Card newPlayerTwo[NUMBER_OF_CARDS] = {{0}};
    removeCards(playerOne, newPlayerOne, playerOne3OAKValue);
    removeCards(playerTwo, newPlayerTwo, playerTwo3OAKValue);
    int pairResult = checkNOfAKind(newPlayerOne, newPlayerTwo, 2, &playerOnePairValue, &playerTwoPairValue, false);
    if (pairResult == COMB_NOT_FOUND) return COMB_NOT_FOUND; // no pairs were found in either player's cards -> no Fullhouse
    if (playerOne3OAKValue != 0 && playerOnePairValue != 0) {
        playerOneHasFH = true;
    }
    if (playerTwo3OAKValue != 0 && playerTwoPairValue != 0) {
        playerTwoHasFH = true;
    }
    if (playerOneHasFH == false && playerTwoHasFH == false) return COMB_NOT_FOUND; // nobody has fullhouse
    if (playerOneHasFH == true && playerTwoHasFH == false) return 1; // playerOne has Fullhouse, playerTwo doesn't
    if (playerOneHasFH == false && playerTwoHasFH == true) return  -1; // playerTwo has Fullhouse, playerOne doesn't
    if (playerOne3OAKValue - playerTwo3OAKValue != 0) { // both have Fullhouse, 3-tuple's values decide
        return playerOne3OAKValue - playerTwo3OAKValue;
    }
    return playerOnePairValue - playerTwoPairValue; // both have Fullhouse, pairs' values decide
}

/*
 * Uses "bucketsort" to sort cards into arrays of cards with
 * indexes corresponding to the cards values. Those are then
 * checked from top index for straight flushes - five cards
 * with the same color in a row. Sadly checking for such cards
 * is ineffective and slow, but I didn't have time to find a
 * better solution.
 */
int checkStraightFlush(Card* playerOne, Card* playerTwo){
    int playerOneCards[NUMBER_OF_CARDS * 2] = {0};
    int playerTwoCards[NUMBER_OF_CARDS * 2] = {0};
    int playerOneMaxCard = 0; // highest card of straight
    int playerTwoMaxCard = 0; // highest card of straight
    for (int i = 0; i < NUMBER_OF_CARDS; i++) {
        playerOneCards[(int) playerOne[i].value]++;
        playerTwoCards[(int) playerTwo[i].value]++;
    }
    for (int i = NUMBER_OF_CARDS * 2 - 1; i > 4; i--) { // checks for non-ACE straight flushes
        if (playerOneCards[i] > 0 && playerOneCards[i - 1] > 0 && playerOneCards[i - 2]
                && playerOneCards[i - 3] > 0 && playerOneCards[i - 4] > 0 && playerOneMaxCard == 0){
            for (int j = 0; j < 4; j++){
                if (checkCard(playerOne, (Value) i, (Color) j) && checkCard(playerOne, (Value) i - 1,(Color) j)
                        && checkCard(playerOne, (Value) i - 2, (Color) j) && checkCard(playerOne, (Value) i - 3, (Color) j)
                        && checkCard(playerOne, (Value) i - 4, (Color) j)){
                    playerOneMaxCard = i;
                    break;
                }
            }
        }
        if (playerTwoCards[i] > 0 && playerTwoCards[i - 1] > 0 && playerTwoCards[i - 2]
                && playerTwoCards[i - 3] > 0 && playerTwoCards[i - 4] > 0 && playerTwoMaxCard == 0){
            for (int j = 0; j < 4; j++){
                if (checkCard(playerTwo, (Value) i, (Color) j) && checkCard(playerTwo, (Value) i - 1,(Color) j)
                        && checkCard(playerTwo, (Value) i - 2, (Color) j) && checkCard(playerTwo, (Value) i - 3, (Color) j)
                        && checkCard(playerTwo, (Value) i - 4, (Color) j)) {
                    playerTwoMaxCard = i;
                    break;
                }
            }
        }
    }
    if (playerOneCards[NUMBER_OF_CARDS * 2 - 1] > 0 && playerOneCards[1] > 0 && playerOneCards[2] // checks for ACE-straight flush
            && playerOneCards[3] > 0 && playerOneCards[4] > 0 && playerOneMaxCard == 0){
        for (int j = 0; j < 4; j++){
            if (checkCard(playerOne, (Value) NUMBER_OF_CARDS * 2 - 1, (Color) j) && checkCard(playerOne, (Value) 1,(Color) j)
                    && checkCard(playerOne, (Value) 2, (Color) j) && checkCard(playerOne, (Value) 3, (Color) j)
                    && checkCard(playerOne, (Value) 4, (Color) j)){
                playerOneMaxCard = 4;
                break;
            }
        }
    }
    if (playerTwoCards[NUMBER_OF_CARDS * 2 - 1] > 0 && playerTwoCards[1] > 0 && playerTwoCards[2] // checks for ACE-straight flush
            && playerTwoCards[3] > 0 && playerTwoCards[4] > 0 && playerTwoMaxCard == 0){
        for (int j = 0; j < 4; j++){
            if (checkCard(playerTwo, (Value) NUMBER_OF_CARDS * 2 - 1, (Color) j) && checkCard(playerTwo, (Value) 1,(Color) j)
                    && checkCard(playerTwo, (Value) 2, (Color) j) && checkCard(playerTwo, (Value) 3, (Color) j)
                    && checkCard(playerTwo, (Value) 4, (Color) j)) {
                playerTwoMaxCard = 4;
                break;
            }
        }
    }
    if (playerOneMaxCard == 0 && playerTwoMaxCard == 0) return COMB_NOT_FOUND; // nobody has a straight
    if (playerOneMaxCard > 0 && playerTwoMaxCard == 0) return 1; // playerOne has a straight, but playerTwo doesn't
    if (playerOneMaxCard == 0 && playerTwoMaxCard > 0) return -1; // playerTwo has a straight, but playerOne doesn't
    return playerOneMaxCard - playerTwoMaxCard; // both have straight flushes, highest cards decide
}

int checkHighCard(Card* playerOne, Card* playerTwo) {
    return checkHighCardAdvanced(playerOne, playerTwo, NUMBER_OF_CARDS, 5);
}

/*
 * Saves check-functions' pointers to an array, those
 * are then called in a loop, while no combination is found.
 * Once one is found, the result is returned.
 */
char checkWinner(Card* playerOne, Card* playerTwo) {
    int result = COMB_NOT_FOUND;
    int counter = 0;
    int (*fun_ptr_arr[])(Card*, Card*) = {checkStraightFlush, checkFourOfAKind, checkFullHouse, checkFlush,
        checkStraight, checkThreeOfAKind, checkTwoPairs, checkPair, checkHighCard};
    while (result == COMB_NOT_FOUND) {
        result = fun_ptr_arr[counter](playerOne, playerTwo);
        ++counter;
        if (counter > 8) break;
    }
    if (result > 0) return 'W';
    if (result < 0) return 'L';
    return 'D';
}

/*
 * Decides who won a game of Texas Hold'em Poker
 * based on cards on input.
 */
int main(void)
{
    while (1) { // while there are new instances of the game available on input
        Card playerOne[NUMBER_OF_CARDS] = {{0}};
        Card playerTwo[NUMBER_OF_CARDS] = {{0}};
        if (readHand(playerOne, false)) { // if input isn't valid
            break;
        }
        if (readHand(playerTwo, true)) { // if input isn't valid
            break;
        }
        if (!readTable(playerOne, playerTwo)) { // if input isn't valid
            break;
        }
        if (checkDuplicates(playerOne, playerTwo)) { // if input isn't valid
            break;
        }
        qsort(playerOne, NUMBER_OF_CARDS, sizeof (Card), compareCards);
        qsort(playerTwo, NUMBER_OF_CARDS, sizeof (Card), compareCards);
        printf("%c\n", checkWinner(playerOne, playerTwo));
    }
    return 0;
}
