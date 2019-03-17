#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

/*
Hand card Unit test
Sara Hovey
Winter, 2019
*/
//gcc -o unittest3 unittest3.c -g dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99 
int main() {

    int isTestPassed = 1;
    int i;
    int numberOfTests = 1000;
    int returnValue;


    char currentFunction[] = "fullDeckCount()";
    struct gameState Game, copyOfGame;
    int randSeed = 2;
    int numbplayerIndexs = 2;
    int playerIndex = 0;
    int card = 0;
    char bee[] = "\U0001F41D";
    char angery[] = "\U0001F608";

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    initializeGame(numbplayerIndexs, k, randSeed, &Game);

    #if (NOISY_TEST == 1)
    printf("----------------- Testing Function %s ----------------\n", currentFunction);
    printf("----------------- Test 1: Return Values ----------------\n");
    #endif
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));

    for (i = 0; i < numberOfTests; i++) {
        returnValue = fullDeckCount(playerIndex, card, &copyOfGame);
        if (returnValue != 0) {
            printf("FAILURE: Actual: %d, Expected: %d\n", copyOfGame.discardCount[playerIndex], Game.discardCount[playerIndex]);
            printf("%sFAILURE, Test1: return values%s\n", angery, angery);
            isTestPassed = 0;
        }
    }
    printf("Return Value: %d, Expected: %d \n\n", returnValue, 0);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    
    #if (NOISY_TEST == 1)
    printf("----------------- Test 2: Return Values ----------------\n");
    #endif
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));
    card = 4;

    for (i = 0; i < numberOfTests; i++) {
        fullDeckCount(playerIndex, card, &copyOfGame);
        if (copyOfGame.handCount[playerIndex] != Game.handCount[playerIndex]) {
            printf("FAILURE: Actual: %d, Expected: %d\n", copyOfGame.discardCount[playerIndex], Game.discardCount[playerIndex]);
            isTestPassed = 0;
             printf("%sFAILURE, Test1: return values%s\n", angery, angery);
        };
    }

    printf("Hand Count: %d, EnumberOfTestspected: %d \n\n", copyOfGame.handCount[playerIndex], Game.handCount[playerIndex]);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    //test and compare deck count in copied struct
    #if (NOISY_TEST == 1)
    printf("----------------- Test 3 ----------------\n");
    #endif
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));
    card = 3;

    for (i = 0; i < numberOfTests; i++) {
        fullDeckCount(playerIndex, card, &copyOfGame);
        if (copyOfGame.deckCount[playerIndex] != Game.deckCount[playerIndex]) {
            printf("FAILURE: Actual: %d, Expected: %d\n", copyOfGame.discardCount[playerIndex], Game.discardCount[playerIndex]);
            isTestPassed = 0;
            printf("%sFAILURE, Test2: return values%s\n", angery, angery);
        };
    }

    printf("Actual: %d, EnumberOfTestspected: %d \n\n", copyOfGame.deckCount[playerIndex], Game.deckCount[playerIndex]);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    //test and compare deck count in copied struct
    printf("\n----  - TEST 4: Discard Count  -  ----\n\n");
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));
    card = 5;

    for (i = 0; i < numberOfTests; i++) {
        fullDeckCount(playerIndex, card, &copyOfGame);
        if (copyOfGame.discardCount[playerIndex] != Game.discardCount[playerIndex]) {
            printf("FAILURE: Actual: %d, Expected: %d\n", copyOfGame.discardCount[playerIndex], Game.discardCount[playerIndex]);
            isTestPassed = 0;
            printf("%sFAILURE, Test1: return values%s\n", angery, angery);
        };
    }

    printf("Actual: %d, Expected: %d \n\n", copyOfGame.discardCount[playerIndex], Game.discardCount[playerIndex]);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    
    //If the tests have not already failed, return true!
    if(isTestPassed){
        printf("%s ALL TESTS PASSED %s\n", bee, bee);
    }

    return 0;
};