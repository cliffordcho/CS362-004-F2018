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
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

 int main() {
     int seed = 1000;
     int r;
     int k[10] = {adventurer, council_room, feast, gardens, mine
         , remodel, smithy, village, baron, great_hall};
     struct gameState G;

     //Test 1: Province = 8
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(2, k, seed, &G); // initialize a new game - 2 players
     if(isGameOver(&G) == 0) //Game not over; Province = 8
         printf("Test 1: Passed\n");
     else
         printf("Test 1: Failed\n");
     //Test 2: Province = 0
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(2, k, seed, &G); // initialize a new game - 2 players
     G.supplyCount[province] = 0;
     if(isGameOver(&G) == 1)
         printf("Test 2: Passed\n");
     else
         printf("Test 2: Failed\n");
     //Test 3-5: Number of Supply Piles w/ 0 Cards = 1,2,3
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(2, k, seed, &G); // initialize a new game - 2 players

     G.supplyCount[adventurer] = 0;
     if(isGameOver(&G) == 0) //Game not over
         printf("Test 3: Passed\n");
     else
         printf("Test 3: Failed\n");
     G.supplyCount[council_room] = 0;
     if(isGameOver(&G) == 0) //Game not over
         printf("Test 4: Passed\n");
     else
         printf("Test 4: Failed\n");

     G.supplyCount[feast] = 0;
     if(isGameOver(&G) == 1) //Game over
         printf("Test 5: Passed\n");
     else
         printf("Test 5: Failed\n");

     printf("End of Unit Test: isGameOver(); 5 Tests\n");
     return 0;
 }
