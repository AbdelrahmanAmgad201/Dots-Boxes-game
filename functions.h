#ifndef FUNTIONS_H
#define FUNTIONS_H
#include<ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dataStructure.h"
#include "colors.h"
void dfs(gameState*currentGame , int i , int j , int **visited , int cameFrom , int *stop , int directions[4][2]);
int chainChecker(gameState*currentGame , int i , int j , char k);
void printData(gameState * currentGame);

int computerTurn(gameState * currentGame, int target);


void saveWinner(const char * name, int score);

void placeLine(gameState * currentGame, int i, int j, char k);


void CheckForChain(gameState * currentGame, int i, int j);

void checkforempty(gameState * currentGame, int i, int j);

void undo(gameState * currentGame, gameState history[], int * count);

void redo(gameState * currentGame, gameState history[], int * count);

void scanNames(gameState * game);

char printMenuAndGetCommand();

void createArr(gameState * game, int size);

void initializeGameState(gameState * game);

void printBoard(cell ** cells, int size);

int checkCellFull(gameState * currentGame, int i, int j);

int CheckWinner(gameState * currentGame);

void checkValidity(gameState * currentGame, int * i, int * j, char * k);

void currentGameTurn(gameState * currentGame, gameState history[], int count);

#endif

