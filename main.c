#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "dataStructure.h"
#include "colors.h"
#include "functions.h"
// void computerTurn(gameState*currentGame, int size)
// {
//     for(int i = 0 ; i <size ; i++)
//     {
//         for(int j = 0 ; j<size ;j++)
//         {
//             if(currentGame->cells[i][j].fillCount == 3)
//             {
//                 if(currentGame->cells[i][j].up == 0)
//                 {
//                     currentGame->cells[i][j].up = 2;
//                     if (i != 0) {
//                         currentGame->cells[i - 1][j].bottom = currentGame->turn;
//                         currentGame->cells[i - 1][j].fillCount++;                
//                     }   
//                 }
//                 else if(currentGame->cells[i][j].bottom == 0)
//                 {
//                     currentGame->cells[i][j].bottom = 2;
//                      if (i != size - 1) {
//                         currentGame->cells[i + 1][j].up = currentGame->turn;
//                         currentGame->cells[i + 1][j].fillCount++;
//                      }
//                 }
//                 else if(currentGame->cells[i][j].left == 0)
//                 {
//                     currentGame->cells[i][j].left = 2;
//                     if (j != 0) {  // Fix: Check if j is not at the beginning of the row
//                         currentGame->cells[i][j - 1].right = currentGame->turn;
//                         currentGame->cells[i][j - 1].fillCount++;
//                     }    
//                 }
//                 else{
//                     currentGame->cells[i][j].right = 2;
//                     if (j != size - 1) {
//                         currentGame->cells[i][j + 1].left = currentGame->turn;
//                         currentGame->cells[i][j + 1].fillCount++;
//                     }
//                 }
                

//             }
//         }
//     }
// }
 void updateHistory(gameState*game , gameState history[] ,int counter)
 {
            history[counter].size = game->size;
            history[counter].turn = game->turn;
            history[counter].score1 = game->score1;
            history[counter].score2 = game->score2;
            history[counter].cellsFilled = game->cellsFilled;
            strcpy(history[counter].player1Name , game->player1Name);
            strcpy(history[counter].player2Name , game->player2Name);
            for(int i = 0 ; i<game->size ; i++)
            {
                for(int j = 0 ; j<game->size ; j++)
                {
                    history[counter].cells[i][j] = game->cells[i][j];
                }
            }

 }
 void debugHistory(gameState history[] , int historySize)
 {
     for(int i = 0 ; i<historySize; i++)
                {
                    for(int j = 0 ; j<history[i].size ; j++)
                    {
                        for(int x = 0 ; x<history[i].size ; x++)
                        {
                            printf("%d %d %d %d",history[i].cells[j][x].up,history[i].cells[j][x].bottom,history[i].cells[j][x].left,history[i].cells[j][x].right);
                        }
                    }
                    printf("\n");
                }

 }

int main() {
    while(1)
    {
        char order = printMenuAndGetCommand();
        system("cls");
        if (order == '1') {
            char typeofMove[2] = "1";
            gameState *game = (gameState *)malloc(sizeof(gameState)); 
            game->size = 2 ;
            createArr(game , game->size);
            scanNames(game);
           
            initializeGameState(game);
            
            gameState history[13];
            int counter = 0 ;
            for(int i = 0 ; i<13 ; i++)
            {
                  initializeGameState(&history[i]);
                  history[i].turn = 0;
                  createArr(&history[i] ,2);
            }
            while (1) {
                if(typeofMove[0] == '1')
                {
                    updateHistory(game , history ,counter);
                }
                
                CheckWinner(game);
                printf("%s:%d %s:%d\n", game->player1Name , game->score1 ,game->player2Name ,game->score2);
                printBoard(game->cells, game->size);
                printf("\n\n1)continue\n2)undo\n3)redo\n");
                (game->turn == 1) ? printf("\n%s: ", game->player1Name) : printf("\n%s: ", game->player2Name);
                scanf(" %1s", &typeofMove); 
                if(typeofMove[0] == '1')
                {
                    currentGameTurn(game, typeofMove,history,counter);
                    counter++;
                }
                else if(typeofMove[0] == '2')
                {
                    undo(game,history,&counter);
                }
                else if (typeofMove[0] == '3')
                {
                    redo(game,history,&counter);
                }
                system("cls");
                
                
            }
        } else if (order == '2') {
            char typeofMove[2];
            gameState *game = (gameState *)malloc(sizeof(gameState));
            game->size = 5;
            createArr(game , game->size);
            scanNames(game);
            initializeGameState(game);
            gameState history[61];
            int counter = 0 ;
            for(int i = 0 ; i<61 ; i++)
            {
                  initializeGameState(&history[i]);
                  history[i].turn = 0;
                  createArr(&history[i] , 5);
            }
            while (1) {
                 if(typeofMove[0] == '1')
                {
                    updateHistory(game , history ,counter);
                }
                
                CheckWinner(game);
                printf("%s:%d %s:%d\n", game->player1Name , game->score1 ,game->player2Name ,game->score2);
                printBoard(game->cells , game->size);
                printf("\n\n1)continue\n2)undo\n3)redo\n");
                (game->turn == 1) ? printf("\n%s: ", game->player1Name) : printf("\n%s: ", game->player2Name);
                scanf(" %1s", &typeofMove); 
                if(typeofMove[0] == '1')
                {
                    currentGameTurn(game, typeofMove,history,counter);
                    counter++;
                }
                else if(typeofMove[0] == '2')
                {
                    undo(game,history,&counter);
                }
                else if (typeofMove[0] == '3')
                {
                    redo(game,history,&counter);
                }
                system("cls");
                
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
    
}