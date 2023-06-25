#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 5
// Prototypes for functions
void shuffle(int puzzle[SIZE][SIZE], int* blankRow, int* blankCol, int moves);
void printPuzzle(int puzzle[SIZE][SIZE]);
int isSolved(int puzzle[SIZE][SIZE]);
void movement(int puzzle[SIZE][SIZE], int* blankRow, int* blankCol, int row, int col);

int main()
{
    // Initialize the puzzle to the solved state
    int puzzle[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {                                                    
        for (int j = 0; j < SIZE; j++) {
            puzzle[i][j] = i * SIZE + j + 1;
        }
    }
    // The last Row and Col is the blank space
    puzzle[SIZE-1][SIZE-1] = 0;
    int blankRow = SIZE - 1;
    int blankCol = SIZE - 1;

    // The random number generator
    srand(time(NULL));

    // Mix the puzzle
    shuffle(puzzle, &blankRow, &blankCol, 100);
//   X  0 1 2 =Column
//   00 1 2 3
//   01 4 5 6
//   02 7 8 9
    // Loop until the puzzle is solved
    while (isSolved(puzzle) != SIZE*SIZE-1) {
        printPuzzle(puzzle);
        printf("Enter a move (up(w), down(s), left(a), right(d)): ");
        char move [5];
        scanf("%s", move);
        if (move[0] == 'w') {                                                                 
            if (blankRow > 0) {
                movement(puzzle, &blankRow, &blankCol, blankRow - 1, blankCol);
            }
        }
        else if (move[0] == 's') {
            if (blankRow < SIZE - 1) {
                movement(puzzle, &blankRow, &blankCol, blankRow + 1, blankCol);
            }
        }
        else if (move[0] == 'a') {
            if (blankCol > 0) {
                movement(puzzle, &blankRow, &blankCol, blankRow, blankCol - 1);
            }
        }
        else if (move[0] == 'd') {
            if (blankCol < SIZE - 1) {
                movement(puzzle, &blankRow, &blankCol, blankRow, blankCol + 1);
            }
        }
    }

    printf("You solved the puzzle!\n");
    printPuzzle(puzzle);

    return 0;
}

// Shuffle the puzzle by making a series of random moves
void shuffle(int puzzle[SIZE][SIZE], int* blankRow, int* blankCol, int moves)
{
    for (int i = 0; i < moves; i++) {
        // Choose a random direction
        int row = *blankRow;
        int col = *blankCol;
        int direction = rand() % 4;
        if (direction == 0) {
            row--; // move up
        }
        else if (direction == 1) {
            row++; // move down
        }
        else if (direction == 2) {
            col--; // move left
        }
        else {
            col++; // move right
        }
        // Make the move if it's legal
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
            movement(puzzle, blankRow, blankCol, row, col);
        }
    }
}

// Check if the puzzle is in the solved state
int isSolved(int puzzle[SIZE][SIZE])
{
	int solved = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (puzzle[i][j] == i * SIZE + j + 1) {
                solved++;
            }
        }
    }
    return solved;
}

// Print the puzzle
void printPuzzle(int puzzle[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (puzzle[i][j] == 0) {
                printf("   ");
            }
            else {
                printf("%2d ", puzzle[i][j]);
            }
        }
        printf("\n");
    }
}

// Move a tile to the blank space
void movement(int puzzle[SIZE][SIZE], int* blankRow, int* blankCol, int row, int col)
{
    puzzle[*blankRow][*blankCol] = puzzle[row][col];
    puzzle[row][col] = 0;
    *blankRow = row;
    *blankCol = col;
}

