#include "saveLoad.h"
void saveGameState(const char *filename, const gameState *currentGame) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(&currentGame->size,sizeof(int),1,file);
        fwrite(&currentGame->flagComp,sizeof(int),1,file);
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
        fread(&currentGame->flagComp,sizeof(int),1,file);
        currentGame->cells = (cell**)malloc(currentGame->size * sizeof(cell*));
        for (int i = 0; i < currentGame->size; i++) {
            currentGame->cells[i] = (cell*)malloc(currentGame->size * sizeof(cell));
        }
        if (currentGame->cells != NULL) {
         for (int i = 0; i < currentGame->size; i++) {
        free(currentGame->cells[i]);
            }
        free(currentGame->cells);
        }
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
        printf("ERROR");
    } else {
        printf("Error opening file '%s' for reading\n", filename);
        exit(0);
    }
}