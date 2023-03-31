#include "board.h"
#include "shape.h"
#include "solver.h"
#include <stdbool.h>
#include <stdio.h>
#include <windows.h>

/* Returns whether a piece is placeable at the specified coordintates */
bool isPiecePlaceable(Board* board, Piece* piece, char xPos, char yPos) {
    for (char row = 0; row < piece->height; row++) {
        if (((~(board->rows[row + yPos - piece->height+2]) >> (BOARD_WIDTH - xPos - piece->width + 1)) & piece->pieceRows[row]) != piece->pieceRows[row]) {
            return false;
        }
    }
    return true;
}

/*
0,0|   |   | 
---------------
   |   |   |
---------------
   |   |   |8,9

Returns whether the specified stoping pattern is detected in the specified board
*/
bool containsStopingPattern(Board board, StopingPattern stoppingPattern, char xPos, char yPos) {
    for (char row = 0; row < stoppingPattern.height; row++) {
        if ((((board.rows[row + yPos - stoppingPattern.height + 1]) >> (8 - xPos - stoppingPattern.width + 1)) & stoppingPattern.patternMask[row]) != stoppingPattern.patternRows[row]) {
            return false;
        }
    }
    return true;
}

/* Returns whether any of the stopping patterns are detected in the specified board */
bool isSolvable(Board* board, StopingPattern* stoppingPatterns) {
    for (char i = 0; i < STOPPING_PATTERNS_COUNT; i++) {
        for (char xPos = 0; xPos <= 9 - stoppingPatterns[i].width; xPos++) {
            for (char yPos = stoppingPatterns[i].height - 1; yPos < 10; yPos++) {
                if (containsStopingPattern(board[0], stoppingPatterns[i], xPos, yPos)) {
                    return false;
                }
            }
        }
    }
    return true;
}

/* Tries to solve the board puzzle */
int solve(Board* board, Piece* pieces, StopingPattern* stoppingPatterns) {
    return solvePiece(board, pieces, stoppingPatterns, 0);
}

/* Tries to place a piece on the board at any position possible. Calls itself when a place is found to place the next piece */
int solvePiece(Board* board, Piece* pieces, StopingPattern* stoppingPatterns, int pieceIndex) {
    int nbSolution = 0;
    if (pieceIndex == 10) {
        return 1;
    }
    //For each rotation
    for (char rotation = 0; rotation < (pieces[pieceIndex].symetric ? 2 : 4); rotation++) {
        //For each column
        for (char xPos = 0; xPos <= BOARD_WIDTH - pieces[pieceIndex].width; xPos++) {
            //For each row
            for (char yPos = pieces[pieceIndex].height - 1; yPos < BOARD_HEIGHT; yPos++) {
                // Check if the piece is placeable
                if (isPiecePlaceable(board, &pieces[pieceIndex], xPos, yPos)) {
                    placePiece(board, &pieces[pieceIndex], xPos, yPos);
                    //Check if the new configuration is still solvable
                    if (isSolvable(board, stoppingPatterns)) {
                        nbSolution += solvePiece(board, pieces, stoppingPatterns, pieceIndex + 1);
                    }
                    //Removes the piece from the board to place it somewhere else (to count all the solutions)
                    removePiece(board, &pieces[pieceIndex], xPos, yPos);
                }
            }
        }
        //Rotates the piece in order to count all the solutions
        rotatePiece(&pieces[pieceIndex]);
    }
    return nbSolution;
}


/* Assign the piece to the board */
void placePiece(Board* board, Piece* piece, char xPos, char yPos) {
    for (char row = 0; row < piece->height; row++) {
        fillRow(board, yPos - piece->height + 1 + row, piece->pieceRows[row] << (BOARD_WIDTH - xPos - piece->width + 1));
    }
}

/* Removes the piece from the board */
void removePiece(Board* board, Piece* piece, char xPos, char yPos) {
    for (char row = 0; row < piece->height; row++) {
        freeRow(board, yPos - piece->height + 1 + row, piece->pieceRows[row] << (BOARD_WIDTH - xPos - piece->width + 1));
    }
}
