#ifndef FUNTIONS_H
#define FUNTIONS_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dataStructure.h"
#include "colors.h"

char printMenuAndGetCommand() ;


void createArr(gameState *game, int size) ;


void initializeGameState(gameState *game) ;


void printBoard(cell **cells, int size) ;


int checkCellFull(gameState *currentGame, int i, int j) ;


void CheckWinner(gameState *currentGame , int size) ;

void checkValidity(gameState* currentGame, int* i, int* j, char* k, int size);



void currentGameTurn(gameState *currentGame, char *move, int size) ;

#endif

