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
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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

     int treasureCardsStart = 0;
     int treasureCardsEnd = 0;
     int discardCardsStart = 0;
     int discardCardsEnd = 0;
     int estateCardsStart = 0;
     int estateCardsEnd = 0;

     //Test 1: Game starts with 7 Copper, 3 Estates. Treasure Cards in Hand should be +2 from start of game.
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));
     treasureCardsStart = 0;
     treasureCardsEnd = 0;

     for (int x = 0; x < 10; x++) {
         if(testG.hand[whoseTurn(&testG)][x] == copper || testG.hand[whoseTurn(&testG)][x] == silver || testG.hand[whoseTurn(&testG)][x] == gold)
             treasureCardsStart++;
     }
     cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
     for (int x = 0; x < 10; x++) {
         if(testG.hand[whoseTurn(&testG)][x] == copper || testG.hand[whoseTurn(&testG)][x] == silver || testG.hand[whoseTurn(&testG)][x] == gold)
             treasureCardsEnd++;
     }
     //printf("Treasure Cards Before: %i -- Treasure Cards After: %i\n",treasureCardsStart,treasureCardsEnd);
     if(treasureCardsStart + 2 == treasureCardsEnd)
         printf("Test 1: Passed\n");
     else
         printf("Test 1: Failed\n");


     //Test 2: Game starts with 7 Copper, 3 Estates. Play 3 adventurer cards. Final Result: 7 Tresure cards in hand. Estate Card in hand + Estate card in discard = 3.
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));
     treasureCardsStart = 0;
     treasureCardsEnd = 0;
     estateCardsStart = 0;
     estateCardsEnd = 0;
     discardCardsStart = 0;
     discardCardsEnd = 0;
     for (int x = 0; x < 10; x++) {
         if(testG.hand[0][x] == copper)
             treasureCardsStart++;
     }

     for (int x = 0; x < 10; x++) {
         if(testG.hand[0][x] == estate)
             estateCardsStart++;
     }

     for (int x = 0; x < 10; x++) {
         if(testG.discard[0][x] == estate)
             discardCardsStart++;
     }

     cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
     cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
     cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

     for (int x = 0; x < 10; x++) {
         if(testG.hand[0][x] == copper)
             treasureCardsEnd++;
     }
     for (int x = 0; x < 10; x++) {
         if(testG.hand[0][x] == estate)
             estateCardsEnd++;
     }

     for (int x = 0; x < 10; x++) {
         if(testG.discard[0][x] == estate)
             discardCardsEnd++;
     }

     //printf("Treasure Cards Before: %i -- Treasure Cards After: %i\n",treasureCardsStart,treasureCardsEnd);
     //printf("Estate Cards Before: %i -- Estate Cards After: %i\n",estateCardsStart,estateCardsEnd);
     //printf("Discard Cards Before: %i -- Discard Cards After: %i\n",discardCardsStart,discardCardsEnd);
     if(treasureCardsEnd == 7)
         printf("Test 2: Passed\n");
     else
         printf("Test 2: Failed\n");
     if(treasureCardsEnd + estateCardsEnd + discardCardsEnd == 10)
         printf("Test 3: Passed\n");
     else
         printf("Test 3: Failed\n");

     //Test 3 - 5: No state change for other players.
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));

     cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

     if(testG.handCount[whoseTurn(&testG)+1] == G.handCount[whoseTurn(&G)+1])
         printf("Test 4: Passed.\n");
     else
         printf("Test 4: Failed.\n");

     if(testG.deckCount[whoseTurn(&testG)+1] == G.deckCount[whoseTurn(&G)+1])
         printf("Test 5: Passed.\n");
     else
         printf("Test 5: Failed.\n");

     if(testG.discardCount[whoseTurn(&testG)+1] == G.discardCount[whoseTurn(&G)+1])
         printf("Test 6: Passed.\n");
     else
         printf("Test 6: Failed.\n");


     //Test 6 - 8: No state change for victory cards and kingdom pile cards.
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
     memcpy(&testG, &G, sizeof(struct gameState));

     cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

     if(testG.supplyCount[copper] == G.supplyCount[copper])
         printf("Test 7: Passed.\n");
     else
         printf("Test 7: Failed.\n");

     if(testG.supplyCount[silver] == G.supplyCount[silver])
         printf("Test 8: Passed.\n");
     else
         printf("Test 8: Failed.\n");

     if(testG.supplyCount[silver] == G.supplyCount[silver])
         printf("Test 9: Passed.\n");
     else
         printf("Test 9: Failed.\n");

     for(int i = 0; i < 10; i++) {
         if(testG.supplyCount[k[i]] != G.supplyCount[k[i]]) {
             printf("Test 10: Failed.\n");
             break;
         }

         if (i == 9)
             printf("Test 10: Passed.\n");

     }
     return 0;
 }
