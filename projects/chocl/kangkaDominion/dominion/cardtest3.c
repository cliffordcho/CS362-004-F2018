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
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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

     //Test 1: Play Council Room. +4 Cards. +1 Buy. -1 Discard. Final state: +3 cards total.
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));
     int startHandNum = 0;
     startHandNum = testG.handCount[whoseTurn(&testG)];
     cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

     if(startHandNum + 4 - 1 == testG.handCount[whoseTurn(&testG)])
         printf("Test 1: Passed.\n");
     else
         printf("Test 1: Failed.\n");
     //Test 2: Play Council Room. +4 Cards. +1 Buy. -1 Discard. Final state: +1 Buy.
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));
     int startBuyNum = 0;
     startBuyNum = testG.numBuys;
     cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
     if(startBuyNum + 1 == testG.numBuys)
         printf("Test 2: Passed.\n");
     else
         printf("Test 2: Failed.\n");

     //Test 3: Other players draw a card. (2 Player Game)
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));
     cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

     if(testG.handCount[whoseTurn(&testG)+1] == G.handCount[whoseTurn(&G)+1] + 1)
         printf("Test 3: Passed.\n");
     else
         printf("Test 3: Failed.\n");

     //Test 4 - 5: Other players draw a card. (3 Player Game)
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(3, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));
     cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

     if(testG.handCount[whoseTurn(&testG)+1] == G.handCount[whoseTurn(&G)+1] + 1)
         printf("Test 4: Passed.\n");
     else
         printf("Test 4: Failed.\n");
     if(testG.handCount[whoseTurn(&testG)+2] == G.handCount[whoseTurn(&G)+2] + 1)
         printf("Test 5: Passed.\n");
     else
         printf("Test 5: Failed.\n");

     //Test 6 - 8: Other players draw a card. (3 Player Game)
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(4, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));
     cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

     if(testG.handCount[whoseTurn(&testG)+1] == G.handCount[whoseTurn(&G)+1] + 1)
         printf("Test 6: Passed.\n");
     else
         printf("Test 6: Failed.\n");
     if(testG.handCount[whoseTurn(&testG)+2] == G.handCount[whoseTurn(&G)+2] + 1)
         printf("Test 7: Passed.\n");
     else
         printf("Test 7: Failed.\n");
     if(testG.handCount[whoseTurn(&testG)+3] == G.handCount[whoseTurn(&G)+3] + 1)
         printf("Test 8: Passed.\n");
     else
         printf("Test 8: Failed.\n");
     return 0;
 }
