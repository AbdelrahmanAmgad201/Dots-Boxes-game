#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dataStructure.h"
#include "colors.h"
#include "functions.h"
char savefiles[10][14]={"savefile1.bin","savefile2.bin","savefile3.bin","savefile4.bin","savefile5.bin","savefile6.bin","savefile7.bin","savefile8.bin","savefile9.bin","savefile10.bin"};

 void updateHistory(gameState*game , gameState history[] ,int counter)
 {
            history[counter].flagComp = game->flagComp;
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
 int gameLoop(gameState*game , int size , int historySize,int loaded)
 {          int mode;
            if (loaded==0){
            printf("1)Multiplayer\n2)Vs AI\n");
            scanf("%d",&mode);
            }
            char typeofMove[2] = "1";
            game->size = size ;
            if (loaded==0)
            {
            if(mode == 2)
            {
                game->flagComp = 1;
            }
            else { game->flagComp == 0;}  
            if (loaded==0)
            {  
            createArr(game , game->size);
            scanNames(game);
            initializeGameState(game);
            }
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
                
                int replay = CheckWinner(game);
                if (replay==1)
                {
                    return 1;
                }
                printf(MAGENTA"    DOTS AND BOXES\n"RESET);
                printBoard(game->cells, game->size);
                printData(game);
                if(game->turn == 2 && game->flagComp == 1)
                {
                    typeofMove[0] = '1';
                }
                else{
                printf("\n\n1)continue\n2)undo\n3)redo\n4)Save\n5)Exit Game\n");
                (game->turn == 1) ? printf("\n%s: ", game->player1Name) : printf("\n%s: ", game->player2Name);
                scanf(" %1s", &typeofMove); 
                }
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
                    printf("File number:\n");
                    scanf("%d",&n);
                    saveGameState(savefiles[n-1],game);
                }
                else if (typeofMove[0] == '5')
                {
                    printf("Come Again Later <3\n");
                    exit(0);
                }
                clock_t endTime = clock();
                game->time = (endTime - startTime) / CLOCKS_PER_SEC;
                system("cls");
                
                
            }
        }


int main() {
    while(1)
    {   
        int replay;
        char order = printMenuAndGetCommand();
        system("cls");
        if (order == '1') {
            gameState *game = (gameState *)malloc(sizeof(gameState));     
        replay = gameLoop(game,2,13,0);
           if (replay==1)
        {   system("cls");
            continue;
        }
            free(game);
            } else if (order == '2') {
            char typeofMove[2];
            gameState *game = (gameState *)malloc(sizeof(gameState));
            replay = gameLoop(game , 5 ,61,0); 
            if (replay==1)
        {
            system("cls");
            continue;
        }
            free(game);          
        } else if (order == '3') {
            displayLeaderboard();
        } 
        else if (order == '4') {
        gameState *game = (gameState *)malloc(sizeof(gameState));
        int n;
        printf("Which File?\n");
        scanf("%d",&n);
        if (n>0&&n<=10)
        {
        loadGameState(savefiles[n-1],game);
        replay = gameLoop(game,game->size,61,1);
        free(game);
        }
        else
        {
        system("cls");
        printf("File not found\n");
        continue;
        }
        if (replay==1)
        {   
            system("cls");
            continue;
        }
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