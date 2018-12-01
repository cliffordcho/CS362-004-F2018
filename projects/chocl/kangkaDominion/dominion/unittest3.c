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
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
 int main() {
     int seed = 1000;
     int r;
     int k[10] = {adventurer, council_room, feast, gardens, mine
         , remodel, smithy, village, baron, great_hall};
     struct gameState G;

     //Test 1-3: 2 players - start with player 0, then player 1, then player 0
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(2, k, seed, &G); // initialize a new game - 2 players
     if(whoseTurn(&G) == 0)
         printf("Test 1: Passed\n");
     else
         printf("Test 1: Failed\n");
     endTurn(&G);
     if(whoseTurn(&G) == 1)
         printf("Test 2: Passed\n");
     else
         printf("Test 2: Failed\n");
     endTurn(&G);
     if(whoseTurn(&G) == 0)
         printf("Test 3: Passed\n");
     else
         printf("Test 3: Failed\n");
     endTurn(&G);

     //Test 4-7: 3 players - start with player 0, then player 1, then player 2, then player 0
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(3, k, seed, &G); // initialize a new game - 3 players
     if(whoseTurn(&G) == 0)
         printf("Test 4: Passed\n");
     else
         printf("Test 4: Failed\n");
     endTurn(&G);
     if(whoseTurn(&G) == 1)
         printf("Test 5: Passed\n");
     else
         printf("Test 5: Failed\n");
     endTurn(&G);
     if(whoseTurn(&G) == 2)
         printf("Test 6: Passed\n");
     else
         printf("Test 6: Failed\n");
     endTurn(&G);
     if(whoseTurn(&G) == 0)
         printf("Test 7: Passed\n");
     else
         printf("Test 7: Failed\n");
     endTurn(&G);

     //Test 8-12: 4 players - start with player 0, then player 1, then player 2, then player 3, then player 0
     memset(&G, 23, sizeof(struct gameState));   // clear the game state
     r = initializeGame(4, k, seed, &G); // initialize a new game - 4 players
     if(whoseTurn(&G) == 0)
         printf("Test 8: Passed\n");
     else
         printf("Test 8: Failed\n");
     endTurn(&G);
     if(whoseTurn(&G) == 1)
         printf("Test 9: Passed\n");
     else
         printf("Test 9: Failed\n");
     endTurn(&G);
     if(whoseTurn(&G) == 2)
         printf("Test 10: Passed\n");
     else
         printf("Test 10: Failed\n");
     endTurn(&G);
     if(whoseTurn(&G) == 3)
         printf("Test 11: Passed\n");
     else
         printf("Test 11: Failed\n");
     endTurn(&G);
     if(whoseTurn(&G) == 0)
         printf("Test 12: Passed\n");
     else
         printf("Test 12: Failed\n");
     endTurn(&G);
     printf("End of Unit Test: whoseTurn(); 12 Tests\n");
     return 0;
 }
