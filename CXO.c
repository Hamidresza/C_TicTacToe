#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

void initializeBoard(int board[SIZE][SIZE]);
void displayBoard(int board[SIZE][SIZE]);
int getUserInput(int board[SIZE][SIZE], char player);
int isValidMove(int board[SIZE][SIZE], int row, int col);
int checkWin(int board[SIZE][SIZE], char player);
int checkDraw(int board[SIZE][SIZE]);
void clearScreen();

int main() {
    int board[SIZE][SIZE];
    char currentPlayer = 'X';
    int moves = 0;
    int gameStatus = 0; // 0: ongoing, 1: win, 2: draw

    clearScreen();
    initializeBoard(board);

    while (gameStatus == 0) {
        clearScreen();
        displayBoard(board);

        if (getUserInput(board, currentPlayer)) {
            moves++;
            if (checkWin(board, currentPlayer)) {
                gameStatus = 1;
            } else if (moves == SIZE * SIZE) {
                gameStatus = 2;
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }
    }
    clearScreen();
    displayBoard(board);

    if (gameStatus == 1) {
        printf("Player %c wins!\n", currentPlayer);
    } else if (gameStatus == 2) {
        printf("It's a draw!\n");
    }

    return 0;
}

void initializeBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void displayBoard(int board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                printf("   "); // Display a space for 0
            } else if (board[i][j] == 7) {
                printf(" O ");
            } else if (board[i][j] == 5) {
                printf(" X ");
            }
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---+---+---\n");
    }
    printf("\n");
}

int getUserInput(int board[SIZE][SIZE], char player) {
    int row, col;
    printf("Player %c, enter your move (row and column): ", player);
    if (scanf("%d, %d", &row, &col) != 2) {
        // Clear the input buffer if the input is invalid
        while (getchar() != '\n');
        printf("Invalid input format. Use 'row, column' format.\n");
        return 0;
    }
    if (player == 'X') {
        if (isValidMove(board, row, col)) {
            board[row][col] = 5;
            return 1;
        } else {
            printf("Invalid move. Try again.\n");
            return 0;
        }
    }
    if (player == 'O') {
        if (isValidMove(board, row, col)) {
            board[row][col] = 7;
            return 1;
        } else {
            printf("Invalid move. Try again.\n");
            return 0;
        }
    }

    return 0; // Added return statement to handle all control paths
}

int isValidMove(int board[SIZE][SIZE], int row, int col) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == 0) {
        return 1;
    } else {
        return 0;
    }
}

int checkWin(int board[SIZE][SIZE], char player) {
    int targetSum = (player == 'X') ? 15 : 21; // Assuming 'O' has a different target sum
    int primaryDiagSum = 0;
    int secondaryDiagSum = 0;

    for (int i = 0; i < SIZE; i++) {
        int rowSum = 0;
        int colSum = 0;
        for (int j = 0; j < SIZE; j++) {
            rowSum += board[i][j]; // Sum the elements of the row
            colSum += board[j][i]; // Sum the elements of the column
        }
        if (rowSum == targetSum || colSum == targetSum) {
            return 1; // Return 1 if either the row sum or column sum equals targetSum
        }
        primaryDiagSum += board[i][i]; // Sum the elements of the primary diagonal
        secondaryDiagSum += board[i][SIZE - 1 - i]; // Sum the elements of the secondary diagonal
    }
    if (primaryDiagSum == targetSum || secondaryDiagSum == targetSum) {
        return 1; // Return 1 if either diagonal sum equals targetSum
    }
    return 0; // Return 0 if no winning condition is met
}

int checkDraw(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#elif defined(__linux__) || defined(__APPLE__)
    system("clear");
#else
    printf("\033[H\033[J");
#endif
}
