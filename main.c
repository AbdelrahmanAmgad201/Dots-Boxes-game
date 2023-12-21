#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
//fsafsafopajfoaspfasfsajfoap
typedef struct{
    int up;
    int bottom;
    int right;
    int left;
    int fillCount;  //  ranges from 0-4 
    int lastPlayer; // 1 Or 2 depending on the last player 

}cell;

typedef struct{
    int time;
    int score1;
    int score2;
    int turn;
    int cellsFilled; // 0-4 or 0-25 depending on easy/hard modes
    cell **cells; // 2d array of structs either 2*2 or 5*2 (still needs work) 


}gameState;

char printMenuAndGetCommand()
{
    char command;
    printf("   DOTS AND BOXES\n\n 1)2X2\n 2)5x5\n 3)leaderboard\n 4)End Game\n");
    scanf("%c", &command);
    return command;
}


void createArr(cell**x , int size) // create the 2d array of variable size (2x2 or 5x5)
{
    x = (cell**)calloc(size ,sizeof(cell*));
    for(int i = 0 ; i<size ; i++)
    {
        x[i] = (cell*)calloc(size,sizeof(cell));

    }
}
void initializeGameState(gameState*game)
{
    game->score1 = 0;
    game->score2 = 0;
    game->time = 0;
    game->turn = 1;
    game->cellsFilled = 0;
}

int main()
{
    char order = printMenuAndGetCommand();
    if(order == '1') {
        printf("play easy");


    } else if (order == '2') {
        printf("play hard");

    } else if (order == '3') {
        printf("leaderboard\n");
    } else if (order == '4') {
        printf("Come Again Later :)\n");
        return 0;
    } else {
        printf("invalid Command\n");
        return 0;
    }

}