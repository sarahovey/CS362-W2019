#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define NOISY_TEST 1

int main() {

    //gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99 
    int isTestPassed = 1;
    struct gameState Game, copyOfGame;
    int cardArray[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int j, i, returnValue;
    int numberOfTests = 50;
    int numberOfplayerIndexs = 2;
    int randSeed = 10000000;
    int handIndex = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;
    char bee[] = "\U0001F41D";
    char angery[] = "\U0001F608";
    int playerIndex = 0;
    int handPosition;
    int expectedHandCount = 5;

    //Set up the game
    initializeGame(numberOfplayerIndexs, cardArray, randSeed, &Game);
    
    #if (NOISY_TEST == 1)
    printf("----------------- Testing Cutpurse ----------------\n");
    printf("----------------- Test 1: Return Values ----------------\n");
    #endif
    for (i = 0; i < numberOfTests; i++) {
        memcpy(&copyOfGame, &Game, sizeof(struct gameState));
        returnValue = cardEffect(council_room, choice1, choice2, choice3, &copyOfGame, handIndex, &bonus);
        if (returnValue != 0) {
            isTestPassed = 0;
            break;
        };
    };
    printf("Actual: %d, Expected: %d \n\n", returnValue, 0);
    if(isTestPassed){
        printf("%s TEST PASSED %s\n", bee, bee);
    }
    
    #if (NOISY_TEST == 1)
    printf("----------------- Test 2: Check Coppers ----------------\n");
    #endif
    //Fill a hand with no copper
    //I expect the hand size to remain the same, no discarding
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));
    copyOfGame.handCount[playerIndex] = 5;
    expectedHandCount = 5;

    for (i = 0; i < numberOfTests; i++) {
        copyOfGame.hand[playerIndex][0] = gold;
        copyOfGame.hand[playerIndex][1] = silver;
        copyOfGame.hand[playerIndex][2] = silver;
        copyOfGame.hand[playerIndex][3] = gold;
        copyOfGame.hand[playerIndex][4] = gold;

        cardEffect(cutpurse, choice1, choice2, choice3, &copyOfGame, handPosition, &bonus);
        if (copyOfGame.handCount[playerIndex] != expectedHandCount) {
            printf(" %s FAILURE, Test 2 No coppers %s \n Actual: %d, Expected: %d\n", angery, angery, copyOfGame.handCount[playerIndex], expectedHandCount);
            isTestPassed = 0;
        }
    }
    printf("Actual: %d, Expected: %d \n\n", copyOfGame.coins, expectedHandCount);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    
     #if (NOISY_TEST == 1)
    printf("----------------- Test 2: Check Hand with One Copper ----------------\n");
    #endif
    //Fill a hand with no copper
    //I expect the hand size to remain the same, no discarding
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));
    copyOfGame.handCount[playerIndex] = 5;
    expectedHandCount = 4;

    for (i = 0; i < numberOfTests; i++) {
        copyOfGame.hand[playerIndex][0] = copper;
        copyOfGame.hand[playerIndex][1] = silver;
        copyOfGame.hand[playerIndex][2] = silver;
        copyOfGame.hand[playerIndex][3] = gold;
        copyOfGame.hand[playerIndex][4] = gold;

        cardEffect(cutpurse, choice1, choice2, choice3, &copyOfGame, handPosition, &bonus);
        if (copyOfGame.handCount[playerIndex] != expectedHandCount) {
            printf(" %s FAILURE, Test 2 No coppers %s \n Actual: %d, Expected: %d\n", angery, angery, copyOfGame.handCount[playerIndex], expectedHandCount);
            isTestPassed = 0;
        }
    }
    printf("Actual: %d, Expected: %d \n\n", copyOfGame.coins, expectedHandCount);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
}