#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "dataStructure.h"
#include "colors.h"
#include "functions.h"
void saveGameState(const char *filename, const gameState *currentGame) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(&currentGame->size,sizeof(int),1,file);
        fwrite(&currentGame->score1, sizeof(int), 1, file);
        fwrite(&currentGame->score2, sizeof(int), 1, file);
        fwrite(&currentGame->time, sizeof(int), 1, file);
        fwrite(&currentGame->turn, sizeof(int), 1, file);
        fwrite(&currentGame->cellsFilled, sizeof(int), 1, file);
        fwrite(currentGame->player1Name, sizeof(char), 20, file);
        fwrite(currentGame->player2Name, sizeof(char), 20, file);
        for (int i = 0; i < currentGame->size; i++) {
            for (int j=0;j<currentGame->size;j++)
            {
            fwrite(&currentGame->cells[i][j], sizeof(cell), 1, file);
            }
}

        fclose(file);
    } else {
        printf("Error opening file '%s' for writing\n", filename);
    }
}
void loadGameState(const char *filename, gameState *currentGame) {
    FILE *file = fopen(filename, "rb");
    if (file != NULL) { 
        fread(&currentGame->size, sizeof(int), 1, file);
        for (int i=0;i<currentGame->size;i++)
        {
            free(currentGame->cells[i]);
        }
        free(currentGame->cells);
        currentGame->cells=(cell**)malloc(currentGame->size*sizeof(cell*));
        for (int i=0;i<currentGame->size;i++)
        {
            currentGame->cells[i]=(cell*)malloc(currentGame->size*sizeof(cell));
        }
        fread(&currentGame->score1, sizeof(int), 1, file);
        fread(&currentGame->score2, sizeof(int), 1, file);
        fread(&currentGame->time, sizeof(int), 1, file);
        fread(&currentGame->turn, sizeof(int), 1, file);
        fread(&currentGame->cellsFilled, sizeof(int), 1, file);
        fread(currentGame->player1Name, sizeof(char), 20, file);
        fread(currentGame->player2Name, sizeof(char), 20, file);
        for (int i = 0; i < currentGame->size; i++) {
            for (int j=0;j<currentGame->size;j++)
            {
            fread(&currentGame->cells[i][j], sizeof(cell), 1, file);
            }
}
        fclose(file);
    } else {
        printf("Error opening file '%s' for reading\n", filename);
    }
}
LeaderboardEntry leaderboard[10];
void loadLeaderboard() {
    FILE *file = fopen("leaderboard.txt", "r");

    if (file != NULL) {
        for (int i = 0; i < 10 && fscanf(file, "%s  %d", leaderboard[i].name, &leaderboard[i].score) == 2; i++) {
            // Load only up to 10 entries
        }
        fclose(file);
    }
}

void saveLeaderboard() {
    FILE *file = fopen("leaderboard.txt", "w");

    for (int i = 0; i < 10; i++) {
        fprintf(file, "%s %d\n", leaderboard[i].name, leaderboard[i].score);
    }

    fclose(file);
}

void saveWinner(const char *name, int score) {
    loadLeaderboard();

    // Add the new winner to the leaderboard
    strcpy(leaderboard[10 - 1].name, name);
    leaderboard[10 - 1].score = score;

    // Sort the leaderboard in descending order based on scores
    for (int i = 0; i < 10 - 1; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (leaderboard[i].score < leaderboard[j].score) {
                // Swap entries
                LeaderboardEntry temp = leaderboard[i];
                leaderboard[i] = leaderboard[j];
                leaderboard[j] = temp;
            }
        }
    }

    // Save the updated leaderboard to the file
    saveLeaderboard();
}

void displayLeaderboard() {
    loadLeaderboard();
    printf("   Leaderboard\n");
    int rank = 1;
    for (int i = 0; i < 10; i++) {
        if (strlen(leaderboard[i].name) > 0 && leaderboard[i].score != 0) {
            printf("%d) %s : %d\n", rank, leaderboard[i].name, leaderboard[i].score);
            rank++;
        }
    }
}
void undo(gameState *currentGame, gameState history[], int *count)
{
    if ((*count) > 0 && (currentGame->turn == history[(*count)-1].turn))
    {
                (*count)--;
                printf("UNDOO");
                currentGame->score1 = history[*count].score1;
                currentGame->score2 = history[*count].score2;
                currentGame->cellsFilled = history[*count].cellsFilled;
                strcpy(currentGame->player1Name , history[*count].player1Name);
                strcpy(currentGame->player2Name , history[*count].player2Name);
                for(int i = 0 ; i<currentGame->size ; i++)
                {
                    for(int j = 0 ; j<currentGame->size ; j++)
                    {
                        currentGame->cells[i][j] = history[*count].cells[i][j];
                    }
                }
    }
    else{
        printf("No valid Undo");
    }

}

void redo(gameState *currentGame, gameState history[], int *count)
{
    if (history[(*count) + 1].turn != 0)
    {
        (*count)++;
        currentGame->score1 = history[*count].score1;
        currentGame->score2 = history[*count].score2;
        currentGame->cellsFilled = history[*count].cellsFilled;
        strcpy(currentGame->player1Name , history[*count].player1Name);
        strcpy(currentGame->player2Name , history[*count].player2Name);
        for(int i = 0 ; i<currentGame->size ; i++)
        {
            for(int j = 0 ; j<currentGame->size ; j++)
            {
                currentGame->cells[i][j] = history[*count].cells[i][j];
            }
        }
        

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
    printf(MAGENTA"   DOTS AND BOXES\n"RESET CYAN"\n1)2X2\n2)5x5\n3)leaderboard\n4)Load\n5)Exit Game\n"RESET);
    scanf(" %c", &command);
    return command;
}

void createArr(gameState *game , int size) { //create 2d array of cells
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
                printf( RED "----" RESET );
            } else if (cells[i][j].up == 2) {
                printf( BLUE "----" RESET );
            } else {
                printf("    ");
            }
        }
        printf("+\n");

        for (int j = 0; j < size; j++) {
            if (cells[i][j].left == 1) {
                printf(RED "|    " RESET);
            } else if (cells[i][j].left == 2) {
                printf(BLUE "|    " RESET);
            } else {
                printf("     ");
            }

            if (cells[i][j].right == 1 && j == size - 1) {
                printf(RED "|" RESET);
            } else if (cells[i][j].right == 2 && j == size - 1) {
                printf(BLUE "|" RESET);
            } 
        }

        printf("\n");
        for (int j = 0; j < size; j++) {
            if (cells[i][j].left == 1) {
                printf(RED "|    " RESET);
            } else if (cells[i][j].left == 2) {
                printf(BLUE "|    " RESET);
            } else {
                printf("     ");
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
                    printf(RED "----" RESET);
                } else if (cells[i][j].bottom == 2) {
                    printf(BLUE "----" RESET);
                }
                else{
                    printf("    ");
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
void CheckWinner(gameState *currentGame) {
    int size = currentGame->size;
    if(currentGame->cellsFilled == size*size)
    {
        if(currentGame->score1 > currentGame->score2)
        {
            printf(RED "%s "RESET"is the Winner !!",currentGame->player1Name);
            saveWinner(currentGame->player1Name,currentGame->score1);
            exit(0);
            
        }
        else if(currentGame->score1 < currentGame->score2){
            printf(BLUE "%s "RESET"is the Winner !!",currentGame->player2Name);
            saveWinner(currentGame->player2Name,currentGame->score2);
            exit(0);

        }
        else{
            printf(RED"DR"BLUE"AW"RESET" :(");
            exit(0);
        }

    }
   
}
void checkValidity(gameState* currentGame, int* i, int* j, char* k)
{
    int size = currentGame->size;
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
        checkValidity(currentGame,i,j,k);

    }
}


void currentGameTurn(gameState *currentGame, char *typeofMove, gameState history[], int count ) {
        int size = currentGame->size ;
        printf("Enter Your Move:");
        char move[5];
        scanf(" %3s", move);    
        int i = (move[0] - '0') - 1;
        int j = (move[1] - '0') - 1;
        char k = move[2];
        int flag = 0;
        checkValidity(currentGame,&i,&j,&k);
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
    
    
