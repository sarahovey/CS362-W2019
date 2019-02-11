#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
//gcc -o unittest2 unittest2.c -g dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99 
#define NOISY_TEST 1

/*
Hand card Unit test
Sara Hovey
Winter, 2019
*/

//Main
int main(){
    //Set up game
    //My team at my internship has been on me about short variables names
    //without further ado, please enjoy Long Variable Names
    int i;
    int randomSeed = 1000;
    int numberOfTests = 1000;
    int numberOfPlayers = 2;
    int isTestPassed = 1;
    char bee[] = "\U0001F41D";
    char angery[] = "\U0001F608";
    int player;
    int bonus;
    
    char currentFunction[] = "updateCoins()";
    int returnValue;
    struct gameState Game, copyOfGame;
    int cardArray[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
                 
    initializeGame(numberOfPlayers, cardArray, randomSeed, &Game );
    
    //Test return value- I used ints instead of voids, so I can use this as a kind-of useless test
    // to make sure nothing went catastrophically wrong
    #if (NOISY_TEST == 1)
    printf("----------------- Testing Function %s ----------------\n", currentFunction);
    printf("----------------- Test 1: Return Values ----------------\n");
    #endif
    
    bonus = 0;
    player = 0;
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));
    for(i = 0; i<numberOfTests; i++){
        returnValue = updateCoins(player, &copyOfGame, bonus);
        if (returnValue !=0) {
            printf("FAILURE: return value invalid");
            isTestPassed = 0;
        }
        
        if(!isTestPassed){
            printf("%s TEST FAILED ON RETURN VALUE %s\n", angery, angery);
        }
        
    }
    
    if(isTestPassed){
        printf("TEST 1 PASSED\n");
    }
    
    printf("Hand Count: %d, Expected: %d \n\n", copyOfGame.handCount[player], Game.handCount[player]);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    
     #if (NOISY_TEST == 1)
    printf("----------------- Testing Function %s ----------------\n", currentFunction);
    printf("----------------- Test: A hand of no coins ----------------\n");
    #endif
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));
    copyOfGame.handCount[player] = 5;
    int expectedCoinCount = 0;
    copyOfGame.coins = 0;

    for (i = 0; i < numberOfTests; i++) {
        copyOfGame.hand[player][0] = feast;
        copyOfGame.hand[player][1] = smithy;
        copyOfGame.hand[player][2] = village;
        copyOfGame.hand[player][3] = tribute;
        copyOfGame.hand[player][4] = ambassador;

        updateCoins(player, &copyOfGame, bonus);
        if (copyOfGame.coins != expectedCoinCount) {
            isTestPassed = 0;
        }
    }
    if (!isTestPassed){
        printf("%sFAILURE, Test Empty%s\n Actual: %d, Expected: %d\n", angery, angery,copyOfGame.coins, expectedCoinCount);
    }
    printf("Actual: %d, Expected: %d \n\n", copyOfGame.coins, expectedCoinCount);
    
    
    #if (NOISY_TEST == 1)
    printf("----------------- Testing Function %s ----------------\n", currentFunction);
    printf("----------------- Test 3: A hand of copper coins ----------------\n");
    #endif
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));
    int copyHandCount = copyOfGame.handCount[player];
    int j;
    int coinValue = 1;
    expectedCoinCount = copyHandCount *coinValue;

    //Each run of the test, fill the player's hand with silver coins
    for (i = 0; i < numberOfTests; i++) {
        for (j = 0; j < copyHandCount; j++) {
            copyOfGame.hand[player][j] = copper;
        }
        updateCoins(player, &copyOfGame, bonus);
        if (copyOfGame.coins != expectedCoinCount) {
            printf("FAILURE, Test 3 Copper\n Actual: %d, Expected: %d\n", copyOfGame.coins, expectedCoinCount);
            isTestPassed = 0;
        }
    }
    printf("Coins: %d, Expected: %d \n\n", copyOfGame.coins, expectedCoinCount);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    //Case: a hand of silvers
    #if (NOISY_TEST == 1)
    printf("----------------- Testing Function %s ----------------\n", currentFunction);
    printf("----------------- Test 4: A hand of silver coins ----------------\n");
    #endif
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));
    copyHandCount = copyOfGame.handCount[player];
    coinValue = 2;
    expectedCoinCount = copyHandCount *coinValue;

    //Each run of the test, fill the player's hand with silver coins
    for (i = 0; i < numberOfTests; i++) {

        for (j = 0; j < copyHandCount; j++) {
            copyOfGame.hand[player][j] = silver;
        }
        updateCoins(player, &copyOfGame, bonus);
        if (copyOfGame.coins != expectedCoinCount) {
            printf("FAILURE, Test 4 Silver\n Actual: %d, Expected: %d\n", copyOfGame.coins, expectedCoinCount);
            isTestPassed = 0;
        }
    }
    printf("Actual: %d, Expected: %d \n\n", copyOfGame.coins, expectedCoinCount);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    //Case: a hand of golds
    #if (NOISY_TEST == 1)
    printf("----------------- Testing Function %s ----------------\n", currentFunction);
    printf("----------------- Test 5: A hand of gold coins ----------------\n");
    #endif
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));
    copyHandCount = copyOfGame.handCount[player];
    coinValue = 3;
    expectedCoinCount = copyHandCount *coinValue;

    for (i = 0; i < numberOfTests; i++) {
        //Each run of the test, fill the player's hand with silver coins
        for (j = 0; j < copyHandCount; j++) {
            copyOfGame.hand[player][j] = gold;
        }
        updateCoins(player, &copyOfGame, bonus);
        if (copyOfGame.coins != expectedCoinCount) {
            printf("FAILURE, Test 5 Gold\n Actual: %d, Expected: %d\n", copyOfGame.coins, expectedCoinCount);
            isTestPassed = 0;
        }
    }
    printf("Actual: %d, Expected: %d \n\n", copyOfGame.coins, expectedCoinCount);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    
    //case: a mixed hand of cards
    #if (NOISY_TEST == 1)
    printf("----------------- Testing Function %s ----------------\n", currentFunction);
    printf("----------------- Test 6: A hand of mixed coins ----------------\n");
    #endif
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));
    copyOfGame.handCount[player] = 5;
    expectedCoinCount = 11;

    for (i = 0; i < numberOfTests; i++) {
        copyOfGame.hand[player][0] = gold;
        copyOfGame.hand[player][1] = silver;
        copyOfGame.hand[player][2] = silver;
        copyOfGame.hand[player][3] = copper;
        copyOfGame.hand[player][4] = gold;

        updateCoins(player, &copyOfGame, bonus);
        if (copyOfGame.coins != expectedCoinCount) {
            printf("FAILURE, Test 6 Mixed\n Actual: %d, Expected: %d\n", copyOfGame.coins, expectedCoinCount);
            isTestPassed = 0;
        }
    }
    printf("Actual: %d, Expected: %d \n\n", copyOfGame.coins, expectedCoinCount);
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    
    #if (NOISY_TEST == 1)
    printf("----------------- Testing Function %s ----------------\n", currentFunction);
    printf("----------------- Test 7: Bonus ----------------\n");
    #endif
    memcpy(&copyOfGame, &Game, sizeof(struct gameState));
    copyOfGame.handCount[player] = 0;
    bonus = 1;
    expectedCoinCount = 1;

    for (i = 0; i < numberOfTests; i++) {
        updateCoins(player, &copyOfGame, bonus);
        if (copyOfGame.coins != expectedCoinCount) {
            printf("%sFAILURE, Test 7 With Bonus%s\n Actual: %d, Expected: %d\n", angery, angery, copyOfGame.coins, expectedCoinCount);
            isTestPassed = 0;
        }
    }
    printf("Actual: %d, Expected: %d \n\n", copyOfGame.coins, expectedCoinCount);
    
    if(isTestPassed){
        printf("%s TESTS PASSED %s\n", bee, bee);
    }
    
    //If the tests have not already failed, return true!
    if(isTestPassed){
        printf("%s ALL TESTS PASSED %s\n", bee, bee);
    }
}