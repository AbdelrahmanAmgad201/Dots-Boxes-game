#ifndef FUNTIONS_H
#define FUNTIONS_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dataStructure.h"
#include "colors.h"
void printData(gameState * currentGame);

int computerTurn(gameState * currentGame, int target);

void saveGameState(const char * filename,
  const gameState * currentGame);

void loadGameState(const char * filename, gameState * currentGame);

void loadLeaderboard();

void saveLeaderboard();

void saveWinner(const char * name, int score);

void placeLine(gameState * currentGame, int i, int j, char k);

void displayLeaderboard();

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

