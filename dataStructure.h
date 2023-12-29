#ifndef DATA_H
#define DATA_H
typedef struct {
    int up;
    int bottom;
    int right;
    int left;
    int fillCount;  // ranges from 0-4
} cell;

typedef struct {
    int size; // 2 or 5
    int time;
    int score1;
    int score2;
    int turn;
    int cellsFilled; // 0-4 or 0-25 depending on easy/hard modes
    cell **cells; // 2d array of structs either 2*2 or 5*2
    char player1Name[20];
    char player2Name[20];
} gameState;

typedef struct {
    char name[100];
    int score;
} LeaderboardEntry;


#endif