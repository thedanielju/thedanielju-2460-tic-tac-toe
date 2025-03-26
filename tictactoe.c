#include <stdio.h>

//global variables
char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
int PLAYER = 1; //1 for X, 0 for O
char IN;        //input character
int OUT = 0;    //outcome of the game

//fnction models
void getValidInput();
void updateBoard();
void drawBoard();
int evalBoard();
void printOutcome();

void getValidInput() {
    char input;
    int valid = 0;
    int position;
    
    while (!valid) {
        //prompt for each player
        if (PLAYER == 1) {
            printf("X - Which square? [1-9] ");
        } else {
            printf("O - Which square? [1-9] ");
        }
        
        //get user input
        scanf(" %c", &input);
        
        //if q, quit
        if (input == 'q' || input == 'Q') {
            IN = 'q';
            return;
        }
        
        //check input, 1-9
        if (input >= '1' && input <= '9') {
            position = input - '1'; //convert num to position on board
            
            //check for occupied board position
            if (board[position] == ' ') {
                valid = 1;
                IN = input;
            } else {
                printf("Space occupied\n");
            }
        } else {
            printf("Invalid input\n");
        }
    }
}

void updateBoard() {
    int position = IN - '1'; //convert character 1-9 to board position
    
    //update position to player selection
    if (PLAYER == 1) {
        board[position] = 'X';
    } else {
        board[position] = 'O';
    }
    
    //switch player
    PLAYER = 1 - PLAYER; //switch by going from 1 to 0, vice versa
}

void drawBoard() {
    printf("\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[0], board[1], board[2]);
    printf("     |     |     \n");
    printf("-----------------\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[3], board[4], board[5]);
    printf("     |     |     \n");
    printf("-----------------\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[6], board[7], board[8]);
    printf("     |     |     \n\n");
}

int evalBoard() {
    //win con
    for (int i = 0; i < 9; i += 3) {
        if (board[i] != ' ' && board[i] == board[i+1] && board[i] == board[i+2]) {
            return (board[i] == 'X') ? 1 : 2;
        }
    }
    
    //3 in column
    for (int i = 0; i < 3; i++) {
        if (board[i] != ' ' && board[i] == board[i+3] && board[i] == board[i+6]) {
            return (board[i] == 'X') ? 1 : 2;
        }
    }
    
    //3 in diagonal
    if (board[0] != ' ' && board[0] == board[4] && board[0] == board[8]) {
        return (board[0] == 'X') ? 1 : 2;
    }
    
    if (board[2] != ' ' && board[2] == board[4] && board[2] == board[6]) {
        return (board[2] == 'X') ? 1 : 2;
    }
    
    //check if draw
    int boardFull = 1;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            boardFull = 0;
            break;
        }
    }
    
    if (boardFull) {
        return 3;
    }
    
    return 0; //continue the game, not over
}

void printOutcome() {
    switch (OUT) {
        case 1:
            printf("X wins!\n");
            break;
        case 2:
            printf("O wins!\n");
            break;
        case 3:
            printf("Cat Game!\n");
            break;
    }
}

int main() {
    printf("Welcome to Daniel's Tic Tac Toe!\n");
    //initialize board
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }
    
    //main gameplay loop
    while (1) {
        drawBoard();
        getValidInput();
        
        if (IN == 'q' || IN == 'Q') {
            printf("Game terminated by user.\n");
            break;
        }
        
        updateBoard();
        OUT = evalBoard();
        
        if (OUT != 0) {
            drawBoard();
            printOutcome();
            break;
        }
    }
    printf("Thanks for playing, goodbye!\n");
    return 0;
}

