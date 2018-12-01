#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <assert.h>

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int j;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    srand(time(NULL));
    for (int i = 0; i < 100000; i++) {
    seed = rand() % 999999999;
    j = 0;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

        for (int x= 0; x < 25; x++) {
            G.supplyCount[x] = rand() % 5;
        }

        for (int y = 0; y < 25; y++) {
            if (G.supplyCount[y] == 0) {
                j++;
            }
        }

        if (G.supplyCount[province] == 0) {
            assert(isGameOver(&G) == 1);
        }
        else if (j >= 3) {
            assert(isGameOver(&G) == 1);
        }
        else {
            assert(isGameOver(&G) == 0);
        }

    }
    printf("Passed all tests.\n");
    return 0;

}
