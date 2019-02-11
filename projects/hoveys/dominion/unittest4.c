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
    
    char currentFunction[] = "handCard()";
    int returnValue;
    struct gameState Game, copyOfGame;
    int cardArray[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
                 
    initializeGame(numberOfPlayers, cardArray, randomSeed, &Game );
    
    #if (NOISY_TEST == 1)
    printf("----------------- Testing Function %s ----------------\n", currentFunction);
    printf("----------------- Test 1: Return Values ----------------\n");
    #endif
    
    for(i = 0; i<numberOfTests; i++){
        memcpy(&copyOfGame, &Game, sizeof(struct gameState));
        copyOfGame.whoseTurn = 0;
        returnValue = whoseTurn(&copyOfGame);
        if (returnValue != Game.whoseTurn) {
            printf("FAILURE: return value invalid");
            isTestPassed = 0;
        }
        
        if(!isTestPassed){
            printf("%s TEST FAILED ON RETURNING CORRECT TURN %s\n", angery, angery);
        }
        
    }
    
    //If the tests have not already failed, return true!
    if(isTestPassed){
        printf("%s ALL TESTS PASSED %s\n", bee, bee);
    }
}