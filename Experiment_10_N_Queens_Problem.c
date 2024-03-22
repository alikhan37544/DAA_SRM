#include <stdio.h>
#include <stdbool.h>

#define N 8 // Change N to desired board size

// Function to print the chessboard
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
}

// Function to check if a queen can be placed in a given position
bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    // Check this row on the left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on the left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on the left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

// Function to solve the N-Queens problem using backtracking
bool solveNQueensUtil(int board[N][N], int col) {
    // Base case: If all queens are placed, return true
    if (col >= N)
        return true;

    // Try placing queens in all rows of the current column
    for (int i = 0; i < N; i++) {
        // Check if the queen can be placed in board[i][col]
        if (isSafe(board, i, col)) {
            // Place the queen
            board[i][col] = 1;

            // Recur to place the rest of the queens
            if (solveNQueensUtil(board, col + 1))
                return true;

            // If placing queen in board[i][col] doesn't lead to a solution, backtrack
            board[i][col] = 0; // Remove the queen
        }
    }

    // If the queen cannot be placed in any row of this column, return false
    return false;
}

// Function to solve the N-Queens problem and print the solution
void solveNQueens() {
    int board[N][N] = {0}; // Initialize board with all zeros

    if (solveNQueensUtil(board, 0) == false) {
        printf("Solution does not exist");
        return;
    }

    // Print the solution
    printBoard(board);
}

// Main function
int main() {
    solveNQueens();
    return 0;
}