#include "leaderboard.h"


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