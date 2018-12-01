#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
 int main() {
     int r;
     int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
     int seed = 1000;
     int numPlayers = 2;
     struct gameState G, testG;
     int k[10] = {adventurer, great_hall, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy, council_room};

     //Test 1: Play Smithy. +3 cards to hand. -1 card to discard. +2 cards overall.
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));
     int startHandNum = 0;
     startHandNum = testG.handCount[whoseTurn(&testG)];

     cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
     if(startHandNum + 3 - 1 == testG.handCount[whoseTurn(&testG)])
         printf("Test 1: Passed.\n");
     else
         printf("Test 1: Failed.\n");
     //Test 2: Play Smithy. -3 cards from deck.
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));
     int startDeckNum = 0;
     startDeckNum = testG.deckCount[whoseTurn(&testG)];
     cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

     if(startDeckNum - 3 == testG.deckCount[whoseTurn(&testG)])
         printf("Test 2: Passed.\n");
     else
         printf("Test 2: Failed.\n");

     //Test 3 - 5: No state change for other players.
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));

     cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

     if(testG.handCount[whoseTurn(&testG)+1] == G.handCount[whoseTurn(&G)+1])
         printf("Test 3: Passed.\n");
     else
         printf("Test 3: Failed.\n");

     if(testG.deckCount[whoseTurn(&testG)+1] == G.deckCount[whoseTurn(&G)+1])
         printf("Test 4: Passed.\n");
     else
         printf("Test 4: Failed.\n");

     if(testG.discardCount[whoseTurn(&testG)+1] == G.discardCount[whoseTurn(&G)+1])
         printf("Test 5: Passed.\n");
     else
         printf("Test 5: Failed.\n");


     //Test 6 - 8: No state change for victory cards and kingdom pile cards.
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));

     cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

     if(testG.supplyCount[copper] == G.supplyCount[copper])
         printf("Test 6: Passed.\n");
     else
         printf("Test 6: Failed.\n");

     if(testG.supplyCount[silver] == G.supplyCount[silver])
         printf("Test 7: Passed.\n");
     else
         printf("Test 7: Failed.\n");

     if(testG.supplyCount[silver] == G.supplyCount[silver])
         printf("Test 8: Passed.\n");
     else
         printf("Test 8: Failed.\n");

     for(int i = 0; i < 10; i++) {
         if(testG.supplyCount[k[i]] != G.supplyCount[k[i]]) {
             printf("Test 9: Failed.\n");
             break;
         }

         if (i == 9)
             printf("Test 9: Passed.\n");

     }

     return 0;
 }
