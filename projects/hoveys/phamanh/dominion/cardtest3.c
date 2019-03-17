#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define NOISY_TEST 1

int main() {

    //gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99 
    int isTestPassed = 1;
    struct gameState Game, copyOfGame;
    int cardArray[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    int j, i, returnValue;
    int x = 1000;
    int numberOfPlayers = 2;
    int randSeed = 10000000;
    int handIndex = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;
    char bee[] = "\U0001F41D";
    char angery[] = "\U0001F608";

    //Set up the game
    initializeGame(numberOfPlayers, cardArray, randSeed, &Game);
    
    #if (NOISY_TEST == 1)
    printf("----------------- Testing Council Room ----------------\n");
    printf("----------------- Test 1: Return Values ----------------\n");
    #endif
    for (i = 0; i < x; i++) {
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
    printf("----------------- Test 2: Draw Cards ----------------\n");
    #endif


    int addedCards = 4;
    int discard = 1;
    int currentPlayer = whoseTurn(&Game);

    for (i = 0; i < x; i++) {
        memcpy(&copyOfGame, &Game, sizeof(struct gameState));
        cardEffect(council_room, choice1, choice2, choice3, &copyOfGame, handIndex, &bonus);

        if (copyOfGame.handCount[currentPlayer] != Game.handCount[currentPlayer] + addedCards - discard) {
            isTestPassed = 0;
            printf("%sFAILURE, Test 2, testing handCount, number of cards in hand %s\n", angery, angery);
            printf("Actual: %d Expected: %d", Game.handCount[currentPlayer] + addedCards - discard, copyOfGame.handCount[currentPlayer] );
            break;
        };
    };
    printf("Actual: %d, Expected: %d \n\n", copyOfGame.handCount[currentPlayer], Game.handCount[currentPlayer]+addedCards-discard);
    if(isTestPassed){
        printf("%s TEST PASSED %s\n", bee, bee);
    }
    
    #if (NOISY_TEST == 1)
    printf("----------------- Test 3: Number of Buys ----------------\n");
    #endif
    int addedBuys = 1;
    currentPlayer = whoseTurn(&Game);

    for (i = 0; i < x; i++) {
        memcpy(&copyOfGame, &Game, sizeof(struct gameState));
        cardEffect(council_room, choice1, choice2, choice3, &copyOfGame, handIndex, &bonus);
        if (copyOfGame.numBuys != Game.numBuys + addedBuys) {
            isTestPassed = 0;
            printf("%sFAILURE, Test 2%s\n", angery, angery);
            break;
        };
    };

    printf("Actual: %d, Expected: %d \n\n", copyOfGame.numBuys, Game.numBuys+addedBuys);
    if(isTestPassed){
        printf("%s TEST PASSED %s\n", bee, bee);
    }

    #if (NOISY_TEST == 1)
    printf("----------------- Test 4: Draw card for other player ----------------\n");
    #endif

    int playerHand[4];
    int copyPlayerHand[4];
    addedCards = 1;
    currentPlayer = whoseTurn(&Game);

    for (i = 0; i < x; i++) {
        memcpy(&copyOfGame, &Game, sizeof(struct gameState));
        cardEffect(council_room, choice1, choice2, choice3, &copyOfGame, handIndex, &bonus);

        for (j = 0; j < Game.numPlayers; j++) {
            if (j != currentPlayer) {
                copyPlayerHand[j] = copyOfGame.handCount[j];
                playerHand[j] = Game.handCount[j];
            }
        }

        for (j = 0; j < Game.numPlayers; j++) {
            if (j != currentPlayer) {
                if (copyPlayerHand[j] != playerHand[j] + addedCards) {
                    isTestPassed = 0;
                    printf("%sFAILURE, Test 2%s\n", angery, angery);
                    break;
                }
            }
        }
    };
    
    if(isTestPassed){
        printf("%s TEST PASSED %s\n", bee, bee);
    }
    return 0;
};