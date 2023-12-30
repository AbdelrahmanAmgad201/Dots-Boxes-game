#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "dataStructure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructure.h"


void loadLeaderboard();

void saveLeaderboard();

void saveWinner(const char * name, int score);


void displayLeaderboard();



#endif

