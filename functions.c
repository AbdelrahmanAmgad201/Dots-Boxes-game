#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dataStructure.h"
#include "colors.h"
#include "functions.h"
// void saveGameState(const char *filename, const gameState *gameState) {
//     FILE *file = fopen(filename, "wb");
//     if (file!=NULL) {
//         // Write the gameState structure to the file
//         fwrite(gameState, sizeof(gameState), 1, file);
//         // Write the cell data to the file
//         for (int i = 0; i < gameState->cellsFilled; i++) {
//             fwrite(gameState->cells[i], sizeof(cell), 1, file);
//         }
//         fclose(file);
//     } else {
//         printf("Error opening file '%s' for writing\n", filename);
//     }
// }

// // Function to load the game state from a binary file
// void loadGameState(const char *filename,gameState *gameState) {
//     FILE *file = fopen(filename,"rb");
//     if (file!=NULL) {
//         // Read the gameState structure from the file
//         fread(gameState,sizeof(gameState), 1, file);
//         // Allocate memory for cells based on the loaded gameState
//         gameState->cells = (cell *)malloc(gameState->cellsFilled * sizeof(cell));
//         for (int i = 0;i<gameState->cellsFilled;i++) {
//             gameState->cells[i]=(cell*)malloc(sizeof(cell));
//             fread(gameState->cells[i],sizeof(cell),1,file);
//         }
//         fclose(file);
//     } else {
//         printf("Error opening file '%s' for reading\n", filename);
//     }
// }


void undo(gameState *currentGame, gameState history[], int *count)
{
    if ((*count) > 0 && (currentGame->turn == history[(*count) - 1].turn))
    {
        (*count)--;
        *currentGame = history[*count];
    }

}

void redo(gameState *currentGame, gameState history[], int *count)
{
    if (history[(*count) + 1].turn != 0)
    {
        (*count)++;
        *currentGame = history[*count];

    }
}

void scanNames(gameState*game)
{
    printf("player 1 name: ");
    scanf("%s",game->player1Name);
    printf("player 2 name: ");
    scanf("%s",game->player2Name);

}

char printMenuAndGetCommand() {
    char command;
    printf(MAGENTA"   DOTS AND BOXES\n"RESET CYAN"\n 1)2X2\n 2)5x5\n 3)leaderboard\n 4)End Game\n"RESET);
    scanf(" %c", &command);
    return command;
}

void createArr(gameState *game, int size) { //create 2d array of cells
    game->cells = (cell **)malloc(size * sizeof(cell *));
    for (int i = 0; i < size; i++) {
        // Allocate and initialize memory for each row using calloc
        game->cells[i] = (cell *)calloc(size, sizeof(cell));
    }
}

void initializeGameState(gameState *game) { //initialize the game state at the beginning of each game
    game->score1 = 0;
    game->score2 = 0;
    game->time = 0;
    game->turn = 1;
    game->cellsFilled = 0;
}

void printBoard(cell **cells, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("+");
            if (cells[i][j].up == 1) {
                printf( RED "--" RESET );
            } else if (cells[i][j].up == 2) {
                printf( BLUE "--" RESET );
            } else {
                printf("  ");
            }
        }
        printf("+\n");

        for (int j = 0; j < size; j++) {
            if (cells[i][j].left == 1) {
                printf(RED "|  " RESET);
            } else if (cells[i][j].left == 2) {
                printf(BLUE "|  " RESET);
            } else {
                printf("   ");
            }

            if (cells[i][j].right == 1 && j == size - 1) {
                printf(RED "|" RESET);
            } else if (cells[i][j].right == 2 && j == size - 1) {
                printf(BLUE "|" RESET);
            } 
        }

        printf("\n");
        if (i == size - 1) {
            for (int j = 0; j < size; j++) {
                printf("+");
                if (cells[i][j].bottom == 1) {
                    printf(RED "--" RESET);
                } else if (cells[i][j].bottom == 2) {
                    printf(BLUE "--" RESET);
                }
                else{
                    printf("  ");
                }
            }
            printf("+");
        }
    }
}

int checkCellFull(gameState *currentGame, int i, int j) {
    if (currentGame->cells[i][j].fillCount == 4) {
        (currentGame->turn == 1) ? (currentGame->score1++) : (currentGame->score2++);
        currentGame->cellsFilled++;
        return 1;
    }

    return 0;
}
void CheckWinner(gameState *currentGame , int size) {
    if(currentGame->cellsFilled == size*size)
    {
        if(currentGame->score1 > currentGame->score2)
        {
            printf(RED "%s "RESET"is the Winner !!",currentGame->player1Name);
            exit(0);
            
        }
        else if(currentGame->score1 < currentGame->score2){
            printf(BLUE "%s "RESET"is the Winner !!",currentGame->player2Name);
            exit(0);

        }
        else{
            printf(RED"DR"BLUE"AW"RESET" :(");
            exit(0);
        }

    }
   
}
void checkValidity(gameState* currentGame, int* i, int* j, char* k, int size)
{
    while (*i > size - 1 || *i < 0 || *j > size - 1 || *j < 0 ||
           (*k != 'u' && *k != 'b' && *k != 'r' && *k != 'l') ||
           (*k == 'u' && currentGame->cells[*i][*j].up != 0) ||
           (*k == 'b' && currentGame->cells[*i][*j].bottom != 0) ||
           (*k == 'r' && currentGame->cells[*i][*j].right != 0) ||
           (*k == 'l' && currentGame->cells[*i][*j].left != 0))
    {
        printf("Invalid input! Please enter a valid command: ");
        char newMove[5];
        fgets(newMove, sizeof(newMove), stdin);
        *i = (newMove[0] - '0') - 1;
        *j = (newMove[1] - '0') - 1;
        *k = newMove[2];
        checkValidity(currentGame,i,j,k,size);

    }
}


void currentGameTurn(gameState *currentGame, char *typeofMove, int size , gameState history[] , int count) {
    if(typeofMove[0] == '2')
    {
        undo(currentGame,history, &count);
        printf("undo");
    }
    else if(typeofMove[0] == '3')
    {
        redo(currentGame,history, &count);
        printf("redo");
    }
    else if(typeofMove[0] == '1' )
    {
        printf("Enter Your Move:");
        char move[5];
        scanf(" %3s", move);    
        int i = (move[0] - '0') - 1;
        int j = (move[1] - '0') - 1;
        char k = move[2];
        int flag = 0;
        checkValidity(currentGame,&i,&j,&k,size);
        if (k == 'u') {
            currentGame->cells[i][j].up = currentGame->turn;
            if (i != 0) {
                currentGame->cells[i - 1][j].bottom = currentGame->turn;
                currentGame->cells[i - 1][j].fillCount++;
                flag = checkCellFull(currentGame,i-1,j);
                
            }
        } else if (k == 'b') {
            currentGame->cells[i][j].bottom = currentGame->turn;
            if (i != size - 1) {
                currentGame->cells[i + 1][j].up = currentGame->turn;
                currentGame->cells[i + 1][j].fillCount++;
                flag = checkCellFull(currentGame,i+1,j);
            }
        } else if (k == 'r') {
            currentGame->cells[i][j].right = currentGame->turn;
            if (j != size - 1) {
                currentGame->cells[i][j + 1].left = currentGame->turn;
                currentGame->cells[i][j + 1].fillCount++;
                flag = checkCellFull(currentGame,i,j+1);
            }
        } else if (k == 'l') {
            currentGame->cells[i][j].left = currentGame->turn;
            if (j != 0) {  // Fix: Check if j is not at the beginning of the row
                currentGame->cells[i][j - 1].right = currentGame->turn;
                currentGame->cells[i][j - 1].fillCount++;
                flag = checkCellFull(currentGame,i,j-1);
            }
        }
        currentGame->cells[i][j].fillCount++;
        if (!(checkCellFull(currentGame, i, j) || flag )) {
            currentGame->turn = (currentGame->turn == 1) ? 2 : 1;
        }

    }
    
    }
