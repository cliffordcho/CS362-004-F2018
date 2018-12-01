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
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
 int main() {
     int seed = 1000;
     int numPlayer = 2;
     int r;
     int k[10] = {adventurer, council_room, feast, gardens, mine
         , remodel, smithy, village, baron, great_hall};
     struct gameState G;

     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
     //Test 1: numBuys < 1
     G.numBuys = 0;
     G.coins = 100;
     if(buyCard(1,&G) == -1)
         printf("Test 1: Passed\n");
     else
         printf("Test 1: Failed\n");

     //Test 2: numBuys = 1
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
     G.numBuys = 1;
     G.coins = 100;
     if(buyCard(1,&G) == 0)
         printf("Test 2: Passed\n");
     else
         printf("Test 2: Failed\n");

     //Test 3: supplyCount = 0
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
     G.numBuys = 10;
     G.coins = 100;
     G.supplyCount[1] = 0;
     if(buyCard(1,&G) == -1)
         printf("Test 3: Passed\n");
     else
         printf("Test 3: Failed\n");

     //Test 4: supplyCount = 1
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
     G.numBuys = 10;
     G.coins = 100;
     G.supplyCount[1] = 1;
     if(buyCard(1,&G) == 0)
         printf("Test 4: Passed\n");
     else
         printf("Test 4: Failed\n");
     //Test 5: coins = 0
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
     G.numBuys = 10;
     G.coins = 0;
     if(buyCard(1,&G) == -1)
         printf("Test 5: Passed\n");
     else
         printf("Test 5: Failed\n");
     //Test 6: coins = 100
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
     G.numBuys = 10;
     G.coins = 100;
     if(buyCard(1,&G) == 0)
         printf("Test 6: Passed\n");
     else
         printf("Test 6: Failed\n");
     //Test 7: Buys - 1
     //Test 8: Coins - 1
     //Test 9: Supply - 1
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
     G.numBuys = 10;
     G.coins = 100;

     buyCard(1,&G);

     if(G.numBuys == 9) //Buys 10 - 1 = 9
         printf("Test 7: Passed\n");
     else
         printf("Test 7: Failed\n");
     if(G.coins == 98) //Cost is 2 coins (Coins 100 - 2 = 98)
         printf("Test 8: Passed\n");
     else
         printf("Test 8: Failed\n");

     if(G.supplyCount[1] == 7) //Supply Starts with 8 (Supply 8 - 1 = 7)
         printf("Test 9: Passed\n");
     else
         printf("Test 9: Failed\n");

    printf("End of Unit Test: buyCard(); 9 Tests\n");
     return 0;
 }
