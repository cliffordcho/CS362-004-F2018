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
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    srand(time(NULL));
    for (int i = 0; i < 1000000; i++) {
    seed = rand() % 999999999;
    int cardPos = rand() % 10;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    G.numBuys = rand() % 20 - 15;
    G.coins = rand() % 10 - 5;
    G.supplyCount[cardPos] = rand() % 10 - 5;

        if (G.numBuys < 1) {
        assert(buyCard(cardPos,&G) == -1);
        }
        else if (G.supplyCount[cardPos] < 1) {
        assert(buyCard(cardPos,&G) == -1);
        }
        else if (G.coins < getCost(cardPos)) {
        assert(buyCard(cardPos,&G) == -1);
        }
        else {
        assert(buyCard(cardPos,&G) == 0);
        }

    }
    printf("Passed all tests.\n");
    return 0;

}
