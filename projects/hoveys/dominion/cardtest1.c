//Test adventurer
// The adventurer card is a card that is played in the action phase of a player’s turn. 
// This card allows the player to search their deck, card by card, until they have 2 new 
// Treasure cards. Each card drawn that is not a Treasure card is discarded.

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

//gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99 
int main() {

    int isTestPassed = 1;
    //char testCard[] = "adventurer";
    struct gameState Game, copyOfGame;
    int cardArray[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    int numberOfTests = 1000;
    int i, returnValue, j;
    int numberOfPlayers = 2;
    int seed = 1000000;
    int handPos = 0;
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0;
    char bee[] = "\U0001F41D";
    char angery[] = "\U0001F608";
    
    //Set up the game
    initializeGame(numberOfPlayers, cardArray, seed, &Game);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    
    #if (NOISY_TEST == 1)
    printf("----------------- Test 1: Return Values ----------------\n");
    #endif
    
    for (i = 0; i < numberOfTests; i++) {
        memcpy(&copyOfGame, &Game, sizeof(struct gameState));
        returnValue = cardEffect(adventurer, choice1, choice2, choice3, &copyOfGame, handPos, &bonus);
        if (returnValue != 0) {
            isTestPassed = 0;
            break;
        };
    };
    printf("Actual: %d, Expected: %d \n\n", returnValue, 0);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    
    #if (NOISY_TEST == 1)
    printf("----------------- Test 2: Hand ----------------\n");
    #endif
    int addedCards = 2;
    int currentPlayer = whoseTurn(&Game);
    for (i = 0; i < numberOfTests; i++) {
        memcpy(&copyOfGame, &Game, sizeof(struct gameState));
        cardEffect(adventurer, choice1, choice2, choice3, &copyOfGame, handPos, &bonus);
        if (copyOfGame.handCount[currentPlayer] != Game.handCount[currentPlayer] + addedCards) {
            isTestPassed = 0;
            printf("%sFAILURE, Test 2%s\n", angery, angery);
            break;
        };
    }
    printf("Actual: %d, Expected: %d \n\n", copyOfGame.handCount[currentPlayer], Game.handCount[currentPlayer] + addedCards);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    
    #if (NOISY_TEST == 1)
    printf("----------------- Test 3: Coins ----------------\n");
    #endif
    
    int currentCoins, copyOfMoney;
    for (i = 0; i < numberOfTests; i++) {
        memcpy(&copyOfGame, &Game, sizeof(struct gameState));
        cardEffect(adventurer, choice1, choice2, choice3, &copyOfGame, handPos, &bonus);

        currentCoins = 0;
        j = 0;
        while (j < numHandCards(&Game)) {
            if (handCard(j, &Game) == copper) {
                currentCoins++;
            } else if (handCard(j, &Game) == silver) {
                currentCoins += 2;
            } else if (handCard(j, &Game) == gold) {
                currentCoins += 3;
            }
            j++;
        }

        copyOfMoney = 0;
        j = 0;
        while (j < numHandCards(&copyOfGame)) {
            if (handCard(j, &copyOfGame) == copper) {
                copyOfMoney++;
            } else if (handCard(j, &copyOfGame) == silver) {
                copyOfMoney += 2;
            } else if (handCard(j, &copyOfGame) == gold) {
                copyOfMoney += 3;
            }
            j++;
        };
        if (copyOfMoney < currentCoins+2) {
            isTestPassed = 0;
            printf("%sFAILURE, Test 2%s\n", angery, angery);
            break;
        }
    };

    printf("Actual: %d, Expected: >= %d \n\n", copyOfMoney, currentCoins+2);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    
    #if (NOISY_TEST == 1)
    printf("----------------- Test 3: Coins ----------------\n");
    #endif

    int cardsMovedtoHand = 2;
    int totalCards, copytotalCards;
    currentPlayer = whoseTurn(&Game);

    for (i = 0; i < numberOfTests; i++) {
        memcpy(&copyOfGame, &Game, sizeof(struct gameState));
        cardEffect(adventurer, choice1, choice2, choice3, &copyOfGame, handPos, &bonus);

        totalCards = Game.deckCount[currentPlayer] + Game.discardCount[currentPlayer];
        copytotalCards = copyOfGame.deckCount[currentPlayer] + copyOfGame.discardCount[currentPlayer];
        if (copytotalCards != totalCards - cardsMovedtoHand) {
            isTestPassed = 0;
            printf("%sFAILURE, Test 2%s\n", angery, angery);
            break;
        };
    };

    printf("Total Cards: %d, Expected: %d \n\n", copytotalCards, totalCards-cardsMovedtoHand);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }

    return 0;
};