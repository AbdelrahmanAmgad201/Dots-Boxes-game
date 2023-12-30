#ifndef SAVE_H
#define SAVE_H
#include "functions.h"
#include "dataStructure.h"

void saveGameState(const char * filename,const gameState * currentGame);

void loadGameState(const char * filename, gameState * currentGame);

void loadLeaderboard();

void saveLeaderboard();


#endif

