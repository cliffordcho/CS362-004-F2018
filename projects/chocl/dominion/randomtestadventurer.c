#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>


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
    int testPass = 0;
    int testFail = 0;
    srand(time(NULL));

    for (int x = 0; x < 10000; x++) {
        seed = rand() % 999999999;
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
            testPass++;
        else
            testFail++;


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
            testPass++;
        else
            testFail++;
        if(treasureCardsEnd + estateCardsEnd + discardCardsEnd == 10)
            testPass++;
        else
            testFail++;

        //Test 3 - 5: No state change for other players.
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
        memcpy(&testG, &G, sizeof(struct gameState));

        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

        if(testG.handCount[whoseTurn(&testG)+1] == G.handCount[whoseTurn(&G)+1])
            testPass++;
        else
            testFail++;

        if(testG.deckCount[whoseTurn(&testG)+1] == G.deckCount[whoseTurn(&G)+1])
            testPass++;
        else
            testFail++;

        if(testG.discardCount[whoseTurn(&testG)+1] == G.discardCount[whoseTurn(&G)+1])
            testPass++;
        else
            testFail++;


        //Test 6 - 8: No state change for victory cards and kingdom pile cards.
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayers, k, seed, &G); // initialize a new game - 2 players
        memcpy(&testG, &G, sizeof(struct gameState));

        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

        if(testG.supplyCount[copper] == G.supplyCount[copper])
            testPass++;
        else
            testFail++;

        if(testG.supplyCount[silver] == G.supplyCount[silver])
            testPass++;
        else
            testFail++;

        if(testG.supplyCount[silver] == G.supplyCount[silver])
            testPass++;
        else
            testFail++;

        for(int i = 0; i < 10; i++) {
            if(testG.supplyCount[k[i]] != G.supplyCount[k[i]]) {
                testFail++;
                break;
            }

            if (i == 9)
                testPass++;

        }
    }
    printf("Test Passed: %i times\n",testPass);
    printf("Test Failed: %i times\n",testFail);
    return 0;
}
