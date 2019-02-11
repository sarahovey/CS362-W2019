#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define NOISY_TEST 1

//gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99 
int main() {

    int isTestPassed = 1;
    struct gameState Game, copyOfGame;
    int cardArray[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int x = 1000;
    int i, returnValue;
    int numberOfPlayers = 2;
    int randSeed = 2;
    int handPos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;
    char bee[] = "\U0001F41D";
    char angery[] = "\U0001F608";

    //Set up the game
    initializeGame(numberOfPlayers, cardArray, randSeed, &Game);
    
    #if (NOISY_TEST == 1)
    printf("----------------- Testing Smithy ----------------\n");
    printf("----------------- Test 1: Return Values ----------------\n");
    #endif

    for (i = 0; i < x; i++) {
        memcpy(&copyOfGame, &Game, sizeof(struct gameState));
        returnValue = cardEffect(smithy, choice1, choice2, choice3, &copyOfGame, handPos, &bonus);
        if (returnValue != 0) {
            isTestPassed = 0;
            break;
        };
    };
    printf("Actual: %d, Expected: %d \n", returnValue, 0);
    if(isTestPassed){
        printf("%s TEST PASSED %s\n", bee, bee);
    }
    
    #if (NOISY_TEST == 1)
    printf("----------------- Test 2: Draw Cards ----------------\n");
    #endif

    int addedCards = 3;
    int discard = 1;
    int currentPlayer = whoseTurn(&Game);

    for (i = 0; i < x; i++) {
        memcpy(&copyOfGame, &Game, sizeof(struct gameState));
        cardEffect(smithy, choice1, choice2, choice3, &copyOfGame, handPos, &bonus);
        if (copyOfGame.handCount[currentPlayer] != Game.handCount[currentPlayer]+addedCards-discard){
            isTestPassed = 0;
            printf("%sFAILURE, Test 2%s\n", angery, angery);
            break;
        }
    }

    printf("Actual: %d, Expected: %d \n", copyOfGame.handCount[currentPlayer], Game.handCount[currentPlayer]+addedCards-discard);
    if(isTestPassed){
        printf("%s TEST PASSED %s\n", bee, bee);
    }
    return 0;
};