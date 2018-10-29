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
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
 int main() {
     int seed = 1000;
     int r;
     int k[10] = {adventurer, council_room, feast, gardens, mine
         , remodel, smithy, village, baron, great_hall};
     struct gameState G;

     //Test 1: 2 Players -- Curse Cards = 10; Estate Cards = 8; Silver = 40
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(2, k, seed, &G); // initialize a new game - 2 players
     if(supplyCount(0,&G) == 10) // Curse = 10
         printf("Test 1: Passed\n");
     else
         printf("Test 1: Failed\n");
     if(supplyCount(1,&G) == 8) // Estate = 8
         printf("Test 2: Passed\n");
     else
         printf("Test 2: Failed\n");
     if(supplyCount(5,&G) == 40) //Silver = 40
         printf("Test 3: Passed\n");
     else
         printf("Test 3: Failed\n");
     //Test 4-6: 3 Players -- Curse Cards = 20; Estate Cards = 12; Silver = 40
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(3, k, seed, &G); // initialize a new game - 3 players
     if(supplyCount(0,&G) == 20) // Curse = 20
         printf("Test 4: Passed\n");
     else
         printf("Test 4: Failed\n");
     if(supplyCount(1,&G) == 12) // Estate = 12
         printf("Test 5: Passed\n");
     else
         printf("Test 5: Failed\n");
     if(supplyCount(5,&G) == 40) //Silver = 40
         printf("Test 6: Passed\n");
     else
         printf("Test 6: Failed\n");
     //Test 7-9: 4 Players -- Curse Cards = 30; Estate Cards = 12; Silver = 40
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(4, k, seed, &G); // initialize a new game - 4 players
     if(supplyCount(0,&G) == 30) // Curse = 30
         printf("Test 7: Passed\n");
     else
         printf("Test 7: Failed\n");
     if(supplyCount(1,&G) == 12) // Estate = 12
         printf("Test 8: Passed\n");
     else
         printf("Test 8: Failed\n");
     if(supplyCount(5,&G) == 40) //Silver = 40
         printf("Test 9: Passed\n");
     else
         printf("Test 9: Failed\n");

  printf("End of Unit Test: supplyCount(); 9 Tests\n");

     return 0;
 }
