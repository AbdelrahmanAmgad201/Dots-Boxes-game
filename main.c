#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dataStructure.h"
#include "colors.h"
#include "functions.h"
char savefiles[5][14]={"savefile1.bin","savefile2.bin","savefile3.bin","savefile4.bin","savefile5.bin"};
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
void printData(gameState*currentGame)
{
    printf("\n");
    printf(RED"%s score: %d\n"RESET,currentGame->player1Name,currentGame->score1);
    printf(BLUE"%s score: %d\n"RESET,currentGame->player2Name,currentGame->score2);
    printf(YELLOW"Cells Left: %d\n"RESET,currentGame->size*currentGame->size-currentGame->cellsFilled);
    printf(YELLOW"Time Passed: %d\n"RESET,currentGame->time);
}
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
 void gameLoop(gameState*game , int size , int historySize,int loaded)
 {
            char typeofMove[2] = "1";
            game->size = size ;
            if (loaded==0)
            {
            createArr(game , game->size);
            scanNames(game);
            initializeGameState(game);
            }
            system("cls");
            gameState history[historySize];
            int counter = 0 ;
            for(int i = 0 ; i<historySize ; i++)
            {
                  initializeGameState(&history[i]);
                  history[i].turn = 0;
                  createArr(&history[i] ,size);
            }
            clock_t startTime = clock();
            while (1) {
                if(typeofMove[0] == '1')
                {
                    updateHistory(game , history ,counter);
                }
                
                CheckWinner(game);
                printf(MAGENTA"   DOTS AND BOXES\n"RESET);
                printBoard(game->cells, game->size);
                printData(game);
                printf("\n\n1)continue\n2)undo\n3)redo\n4)Save\n5)Exit Game\n");
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
                else if (typeofMove[0] == '4')
                {
                    int n;
                    printf("Which File?\n");
                    scanf("%d",&n);
                    saveGameState(savefiles[n-1],game);
                }
                else if (typeofMove[0] == '5')
                {
                    printf("salamo 3leko :)");
                    exit(0);
                }
                clock_t endTime = clock();
                game->time = (endTime - startTime) / CLOCKS_PER_SEC;
                system("cls");
                
                
            }
        }


int main() {
    
    while(1)
    {   system("cls");
        char order = printMenuAndGetCommand();
        system("cls");
        if (order == '1') {
            gameState *game = (gameState *)malloc(sizeof(gameState)); 
            gameLoop(game,2,13,0);
            free(game);
            } else if (order == '2') {
            char typeofMove[2];
            gameState *game = (gameState *)malloc(sizeof(gameState));
            gameLoop(game , 5 ,61,0); 
            free(game);          
        } else if (order == '3') {
            displayLeaderboard();
        } 
        else if (order == '4') {
        gameState *game = (gameState *)malloc(sizeof(gameState));
        int n;
        printf("Which File?\n");
        scanf("%d",&n);
        //printf("z");
        initializeGameState(game);
        loadGameState(savefiles[n-1],game);
        //printf("x");
        gameLoop(game,game->size,61,1);
       // printf("y");
        free(game);
        }
        else if (order == '5') {
            printf("Come Again Later <3\n");
            return 0;
        } else {
            printf("invalid Command\n");
            return 1;
        }

        }
    
}