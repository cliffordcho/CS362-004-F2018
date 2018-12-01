#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int randInt(int range){ //a helper function to generate a random integer from 0 to range
int i=range+1;
int returnInt=rand()%i;
return returnInt;
}

void randArrIni(int range, int size, int arr[]){//a helper function to initilize a random array.
for(int i=0;i<size;i++ )
	{
		arr[i]=rand()%range;
	}

}

struct gameState emptyG;//using a empty static gamestruct for resetting during each testing

int main(){
printf("now random testing council room \n");
srand(time(0));//refresh random seed
int k[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall},//10 kingdom cards
numSuc=0, numFai=0;//count the number of successful/failed random testing

	for(int numTest=50;numTest>0;numTest--)//the actual random testing procedure, repeat 50 times
	{
	int numPlayer=randInt(2)+2; //randomize the number of players from 2 to 4
	struct gameState g; //using an actual struct  instead of a pointer //reset the game structure before each testing

	initializeGame(numPlayer,k,1000,&g); //initilze game with seed=1000
	int iniDeckCounts[]={0,0,0,0}, //record initial deck counts, start with 0 regardless of actual num of players
		iniHandCounts[]={0,0,0,0}, //record initial hand counts
		iniDisCounts[]={0,0,0,0}, //record initial discard counts
		testingCardInserted=0; //a flag to check if the testing card is in the hand of player 0

		for(int i=0;i<numPlayer;i++) //initilize deck, discard, handcard for players during each testing
		{
			g.deckCount[i]=randInt(15)+5; //every player has at least 5 deck cards, 20 at most
			iniDeckCounts[i]=g.deckCount[i];
			g.handCount[i]=randInt(10);//10 hand cards at most
			iniHandCounts[i]=g.handCount[i];
			g.discardCount[i]=randInt(10);//10 discards at most
			iniDisCounts[i]=g.discardCount[i];
			
			for(int j=0;j<g.deckCount[i];j++)
			{
				g.deck[i][j]=k[randInt(9)];//fill the decks with random kingdom cards	
			}


			for(int j=0;j<g.handCount[i];j++)
			{
				int randCard=randInt(9);
				g.hand[i][j]=k[randCard];//fill the hand with random kingdom cards
				if(randCard==1)	{testingCardInserted=1;}//if at least 1 testing card is in any handcard, update flag
			}


			for(int j=0;j<g.discardCount[i];j++)
			{
				g.discard[i][j]=k[randInt(9)];//fill the discard with random kingdom cards	
			}

		}

		if(testingCardInserted==0)//insert the testing card if it doesn't exist after random card assignment
		{g.hand[0][0]=council_room;} 

		int turn=cardEffect(council_room,0,0,0,&g,1,0);//cardEffect will return 1 if unsuccessful
		if(turn)
			{
			printf("test%d Failed,function returned non 0 value \n", (50-numTest));
			numFai++;
			continue;
			}

		if(g.handCount[0]!=(iniHandCounts[0]+3))//check the hand count increment of player 0 who used the testing card
			{
			printf("test%d Failed,wrong hand card change at player who used council room\n", (50-numTest));
			numFai++;
			continue;
			}

		int flag1=0;//a flag for easier loop exit 
		for(int j=1; j<numPlayer;j++)//check all other players' handcards
			{
			if((g.handCount[j]-iniHandCounts[j])!=1)
				{
					printf("test%d Failed,wrong hand card number for other players\n",(50-numTest));
					numFai++;
					flag1=1;
					continue;
				}
			}
		if(flag1==1){continue;}
		
		if(g.numBuys!=2)//the num of buys should increase by 1
			{
			printf("test%d Failed,num of buys is wrong\n", (50-numTest));
			numFai++;
			continue;				
			}

		printf("test%d successful \n", (50-numTest));
		numSuc++;
		}
	printf("all test done, %d out of 50 tests are succssful. \n", numSuc);
	printf("all test done, %d out of 50 tests are failed. \n", numFai);
	printf("random testing council room done\n\n\n\n");
}



















