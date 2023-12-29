#ifndef FUNTIONS_H
#define FUNTIONS_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dataStructure.h"
#include "colors.h"
void undo(gameState *currentGame, gameState history[], int *count);

void redo(gameState *currentGame, gameState history[], int *count);

void scanNames(gameState*game);

char printMenuAndGetCommand() ;


void createArr(gameState *game, int size) ;


void initializeGameState(gameState *game) ;


void printBoard(cell **cells , int size) ;


int checkCellFull(gameState *currentGame, int i, int j) ;


void CheckWinner(gameState *currentGame ) ;

void checkValidity(gameState* currentGame, int* i, int* j, char* k);



void currentGameTurn(gameState *currentGame, char* typeofMove,gameState history[], int count );

#endif

