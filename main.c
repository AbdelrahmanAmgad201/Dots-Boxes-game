#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dataStructure.h"
#include "colors.h"
#include "functions.h"





int main() {
    char order = printMenuAndGetCommand();
    if (order == '1') {
        int size = 2;
        char move[5];
        gameState *game = (gameState *)malloc(sizeof(gameState)); 
        createArr(game, size);
        scanNames(game);
        initializeGameState(game);
        int counter = 0;
        gameState history[12] ={0};

        while (1) {
            CheckWinner(game , size);
            printf("%s:%d %s:%d\n", game->player1Name , game->score1 ,game->player2Name ,game->score2);
            printBoard(game->cells, size);
            (game->turn == 1) ? printf("\n%s: ", game->player1Name) : printf("\n%s: ", game->player2Name);
            scanf("%s", move);
            currentGameTurn(game, move, size, history, counter);
            system("cls");
            history[counter++] =* game;
            printf("%d\n",history[counter-1].cellsFilled);
            
        }
    } else if (order == '2') {
        int size = 5;
        char move[5];
        gameState *game = (gameState *)malloc(sizeof(gameState));
        createArr(game, size);
        scanNames(game);
        initializeGameState(game);
        int counter = 0;
        gameState history[60] ={0};

        while (1) {
            CheckWinner(game , size);
            printf("%s:%d %s:%d\n", game->player1Name , game->score1 ,game->player2Name ,game->score2);
            printBoard(game->cells, size);
            (game->turn == 1) ? printf("\n%s: ", game->player1Name) : printf("\n%s: ", game->player2Name);
            scanf("%s", move);
            currentGameTurn(game, move, size, history, counter);
            system("cls");
            history[counter++] = *game;
            printf("%d\n",history[counter-1].cellsFilled);

            
        }
    } else if (order == '3') {
        printf("leaderboard\n");
    } else if (order == '4') {
        printf("Come Again Later <3\n");
        return 0;
    } else {
        printf("invalid Command\n");
        return 1;
    }
}