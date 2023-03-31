#include <stdbool.h>

#ifndef SOLVER_H
#define SOLVER_H

// -- Conditions
bool isPiecePlaceable(Board* board, Piece* piece, char xPos, char yPos);

bool containsStopingPattern(Board board, StopingPattern stoppingPattern, char xPos, char yPos);

bool isSolvable(Board* board, StopingPattern* stoppingPatterns);

// -- Solving functions

int solve(Board* board, Piece* pieces, StopingPattern* stoppingPatterns);

int solvePiece(Board* board, Piece* pieces, StopingPattern* stoppingPatterns, int pieceIndex);

// Utile functions

void placePiece(Board* board, Piece* piece, char xPos, char yPos);

void removePiece(Board* board, Piece* piece, char xPos, char yPos);

#endif