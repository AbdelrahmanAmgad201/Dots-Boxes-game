#include "functions.h"

void printData(gameState*currentGame)
{
    printf("\n");
    printf(RED"%s score: %d\n"RESET,currentGame->player1Name,currentGame->score1);
    printf(BLUE"%s score: %d\n"RESET,currentGame->player2Name,currentGame->score2);
    printf(YELLOW"Cells Left: %d\n"RESET,currentGame->size*currentGame->size-currentGame->cellsFilled);
    printf(YELLOW"Time Passed: %d\n"RESET,currentGame->time);
}


void undo(gameState *currentGame, gameState history[], int *count)
{
    if ((*count) > 0 )
    {
                (*count)--;
                printf("UNDOO");
                currentGame->score1 = history[*count].score1;
                currentGame->score2 = history[*count].score2;
                currentGame->turn = history[*count].turn;
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

void scanNames(gameState *game) {
    printf("Player 1 name: ");
    scanf("%19s", game->player1Name);
    while (getchar() != '\n');  // Consume remaining characters in the input buffer

    if (game->flagComp == 0) {
        printf("Player 2 name: ");
        scanf("%19s", game->player2Name);
        while (getchar() != '\n');  // Consume remaining characters in the input buffer
    } else if (game->flagComp == 1) {
        strcpy(game->player2Name, "computer");
    }
    for (int i = 0; game->player1Name[i] != '\0'; i++) {
        game->player1Name[i] = tolower(game->player1Name[i]);
    }

    for (int i = 0; game->player2Name[i] != '\0'; i++) {
        game->player2Name[i] = tolower(game->player2Name[i]);
    }
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
                printf( RED "---------" RESET );
            } else if (cells[i][j].up == 2) {
                printf( BLUE "---------" RESET );
            } else {
                printf("         ");
            }
        }
        printf("+\n");
        for(int x = 0 ; x<3 ; x++)
        {
            for (int j = 0; j < size; j++) {
            if (cells[i][j].left == 1) {
                if(cells[i][j].fillCount == 4)
                {
                    printf(RED "|"RESET  RED_BACKGROUND"         " COLOR_RESET);
                }
                else
                {
                    printf(RED "|         " RESET);
                }
                
            } else if (cells[i][j].left == 2) {
                if(cells[i][j].fillCount == 4)
                {
                    printf(BLUE "|"RESET  BLUE_BACKGROUND"         " COLOR_RESET);
                }
                else
                {
                    printf(BLUE "|         " RESET);
                }
                
            } else {
                printf("          ");
            }

            if (cells[i][j].right == 1 && j == size - 1) {
                printf(RED "|" RESET);
            } else if (cells[i][j].right == 2 && j == size - 1) {
                printf(BLUE "|" RESET);
            } 
        }

        printf("\n");
        }
        if (i == size - 1) {
            for (int j = 0; j < size; j++) {
                printf("+");
                if (cells[i][j].bottom == 1) {
                    printf(RED "---------" RESET);
                } else if (cells[i][j].bottom == 2) {
                    printf(BLUE "---------" RESET);
                }
                else{
                    printf("         ");
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
        currentGame->cells[i][j].up = currentGame->turn;
        currentGame->cells[i][j].bottom = currentGame->turn;
        currentGame->cells[i][j].left = currentGame->turn;
        currentGame->cells[i][j].right = currentGame->turn;

        // Update neighboring cells
        if (i != 0) {
            currentGame->cells[i - 1][j].bottom = currentGame->turn;
        }
        if (i != currentGame->size - 1) {
            currentGame->cells[i + 1][j].up = currentGame->turn;
        }
        if (j != 0) {
            currentGame->cells[i][j - 1].right = currentGame->turn;
        }
        if (j != currentGame->size - 1 && currentGame->cells[i][j + 1].fillCount!=4) {
            currentGame->cells[i][j + 1].left = currentGame->turn;
        }

        return 1;
    }

    return 0;
}

int CheckWinner(gameState *currentGame) {
    int size = currentGame->size;
    if (currentGame->cellsFilled == size * size) {
        printf(MAGENTA"   DOTS AND BOXES\n"RESET);
        printBoard(currentGame->cells, currentGame->size);
        printf("\n");
        printData(currentGame);
        if (currentGame->score1 > currentGame->score2) {
            printf(RED "%s "RESET"is the Winner !!", currentGame->player1Name);
            saveWinner(currentGame->player1Name, currentGame->score1);
        } else if (currentGame->score1 < currentGame->score2) {
            printf(BLUE "%s "RESET"is the Winner !!", currentGame->player2Name);
            saveWinner(currentGame->player2Name, currentGame->score2);
        } else {
            printf(RED"DR"BLUE"AW"RESET" :(");
        }

        printf("\n1) Play Again\n2) Exit Game\n");
        char input;
        scanf(" %c", &input);
        if (input == '1') {
            return (1);
        } else if (input == '2') {
            
            exit(0);
        } else {
            // Invalid input, handle accordingly
            printf("Invalid input. Exiting game.\n");
            exit(1);
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
        printf(RED"Please enter a valid command: "RESET);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        char newMove[5];
        fgets(newMove, sizeof(newMove), stdin);
        *i = (newMove[0] - '0') - 1;
        *j = (newMove[1] - '0') - 1;
        *k = newMove[2];
    }
}
int checkValidityDfs(gameState* currentGame, int* i, int* j, char* k)
{
    int size = currentGame->size;

    if (
           (*k == 'u' && currentGame->cells[*i][*j].up != 0) ||
           (*k == 'b' && currentGame->cells[*i][*j].bottom != 0) ||
           (*k == 'r' && currentGame->cells[*i][*j].right != 0) ||
           (*k == 'l' && currentGame->cells[*i][*j].left != 0))
    {
        return 1 ;

    }
        return 0;
}



void currentGameTurn(gameState *currentGame,gameState history[], int count ) {
        for(int i = count+1 ; history[i].turn != 0 ;i++)
        {
            history[i].turn = 0 ;
        }
        if((currentGame->flagComp) == 1 && (currentGame->turn == 2))
        {
            int x = 1;
            int targets[] = {3,1,0,2};
            int played = 0;
            while(x == 1)
            {
                played = 0;
                for(int i = 0 ; i<4 && !played; i++)
                {
                    
                    x=computerTurn(currentGame , targets[i]);
                    printf("%d ",x);
                    played = (x!=0)? 1 : 0;
                }

            }
        }
        else{
            int size = currentGame->size ;
            printf("Enter Your Move:");
            char move[5];
            scanf(" %3s", move);    
            int i = (move[0] - '0') - 1;
            int j = (move[1] - '0') - 1;
            char k = move[2];
            checkValidity(currentGame,&i,&j,&k);
            if(chainChecker(currentGame, i ,j ,k) == 1)
            {
            placeLine(currentGame,i,j,k);
            }

        }
      

    }
    void placeLine (gameState*currentGame, int i , int j , char k )
    {
        int flag = 0;
        int size = currentGame->size ;
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

int computerTurn(gameState*currentGame, int target)
{
    int size = currentGame->size ;
    char move[4];
    int flag = 0;
    int placed = 0 ;
    for(int i = 0 ; i <size && !placed ; i++)
    {
        for(int j = 0 ; j<size && !placed ;j++)
        {
            if(currentGame->cells[i][j].fillCount == target)
            {
                placed = 1;
                if(target == 3) {flag = 1;}
                else { flag = 2;}
                if(currentGame->cells[i][j].up == 0)
                {
                   placeLine(currentGame,i,j,'u');
                }
                else if(currentGame->cells[i][j].bottom == 0)
                {
                   placeLine(currentGame,i,j,'b');
                }
                else if(currentGame->cells[i][j].left == 0)
                {
                    placeLine(currentGame,i,j,'l');    
                }
                else if(currentGame->cells[i][j].right == 0){
                    placeLine(currentGame,i,j,'r');  
                }
            }
        }
    }
    return flag;
}

int chainChecker(gameState*currentGame , int i , int j , char k)
{
    int **visited;
    visited = (int**)malloc(currentGame->size * sizeof(int*));
    for (int i = 0; i < currentGame->size; i++)
    {
        visited[i] = (int *)calloc(currentGame->size, sizeof(int));
    }
    //                        up      down    left     right
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int stop  = 0 ;

    dfs(currentGame,i,j,visited,-1,&stop,directions);
    for(int w = 0 ; w<currentGame->size ; w++)
    {
        for(int r = 0 ; r<currentGame->size ; r++ )
        {
            printf("%d",visited[w][r]);
        }
        printf("\n");
    }
    printf("%d",stop);
    
    if(stop != 1)
    {
         for(int x = 0 ; x<currentGame->size ; x++)
         {
            for(int y = 0 ; y<currentGame->size ; y++)
            {
                if(visited[x][y] == 1)
                {
                    if(currentGame->cells[x][y].up == 0)
                    {
                    placeLine(currentGame,x,y,'u');
                    }
                    else if(currentGame->cells[x][y].bottom == 0)
                    {
                    placeLine(currentGame,x,y,'b');
                    }
                    else if(currentGame->cells[x][y].left == 0)
                    {
                        placeLine(currentGame,x,y,'l');    
                    }
                    else if(currentGame->cells[x][y].right == 0){
                        placeLine(currentGame,x,y,'r');  
                    }
                    
                }
            }
         }
    }
   
    for (int i = 0; i < currentGame->size; i++)
        {
        free(visited[i]);
        }
    free(visited);
    return stop;
}
void dfs(gameState*currentGame , int i , int j , int **visited , int cameFrom , int *stop , int directions[4][2])
{

    if (*stop == 1)
    {
        return;
    }
    visited[i][j] = 1 ;
    for(int d = 0 ; d<4 ; d++)
    {
        if(d == cameFrom)
            continue;
        if(d == 0 && currentGame->cells[i][j].up != 0)
            continue;
        if(d == 1 && currentGame->cells[i][j].bottom != 0)
            continue;
        if(d == 2 && currentGame->cells[i][j].left != 0)
            continue;
        if(d == 3 && currentGame->cells[i][j].right != 0)
            continue;
        int newI = i+directions[d][0];
        int newJ = j+directions[d][1];
        if((newI >= 0 && newI<=(currentGame->size)-1) && (newJ >= 0 && newJ<=(currentGame->size)-1) && !(visited[newI][newJ]))
        {
            int newCameFrom = -1 ;

            if(d == 0) newCameFrom = 1 ;
            else if(d == 1) newCameFrom = 0 ;
            else if(d == 2) newCameFrom = 3 ;
            else if(d == 3) newCameFrom = 2 ;
            dfs(currentGame,newI,newJ,visited,newCameFrom,stop,directions);
            
        }
        else 
        {
            printf("%d %d",newI , newJ);
            *stop = 1 ;
            return ;
        }     
    }

}    
    