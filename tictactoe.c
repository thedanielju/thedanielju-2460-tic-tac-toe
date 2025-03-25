#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Global variables
char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
int PLAYER = 1; // 1 for X, 0 for O
char IN;        // Input character
int OUT = 0;    // Outcome of the game

// Function prototypes
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
        // Prompt based on current player
        if (PLAYER == 1) {
            printf("X - Which square? [1-9] ");
        } else {
            printf("O - Which square? [1-9] ");
        }
        
        // Get input
        scanf(" %c", &input);
        
        // Check if input is 'q' for quit
        if (input == 'q' || input == 'Q') {
            IN = 'q';
            return;
        }
        
        // Check if input is a number between 1 and 9
        if (input >= '1' && input <= '9') {
            position = input - '1'; // Convert to 0-8 index
            
            // Check if the position is already occupied
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
    int position = IN - '1'; // Convert character '1'-'9' to index 0-8
    
    // Update the board based on the current player
    if (PLAYER == 1) {
        board[position] = 'X';
    } else {
        board[position] = 'O';
    }
    
    // Switch player
    PLAYER = 1 - PLAYER; // Toggle between 0 and 1
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
    // Check rows for a win
    for (int i = 0; i < 9; i += 3) {
        if (board[i] != ' ' && board[i] == board[i+1] && board[i] == board[i+2]) {
            return (board[i] == 'X') ? 1 : 2;
        }
    }
    
    // Check columns for a win
    for (int i = 0; i < 3; i++) {
        if (board[i] != ' ' && board[i] == board[i+3] && board[i] == board[i+6]) {
            return (board[i] == 'X') ? 1 : 2;
        }
    }
    
    // Check diagonals for a win
    if (board[0] != ' ' && board[0] == board[4] && board[0] == board[8]) {
        return (board[0] == 'X') ? 1 : 2;
    }
    
    if (board[2] != ' ' && board[2] == board[4] && board[2] == board[6]) {
        return (board[2] == 'X') ? 1 : 2;
    }
    
    // Check for a draw (cat game)
    int boardFull = 1;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            boardFull = 0;
            break;
        }
    }
    
    if (boardFull) {
        return 3; // Cat game
    }
    
    return 0; // Game still in progress
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
    // Initialize the board with numbers 1-9
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }
    
    // Main game loop
    while (1) {
        drawBoard();
        getValidInput();
        
        // Check if user wants to quit
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
    
    return 0;
}

