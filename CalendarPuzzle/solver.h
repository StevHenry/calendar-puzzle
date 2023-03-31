#include <stdbool.h>

#ifndef SOLVER_H
#define SOLVER_H

bool canPlacePiece(Board* board, Piece* piece, char xPos, char yPos);

void placePiece(Board* board, Piece* piece, char xPos, char yPos);

void removePiece(Board* board, Piece* piece, char xPos, char yPos);

bool findBlocage(Board* board, Piece* piece, int row, int col);

//int solve(Board board, Piece* pieces, Day day, int number, Month month);
 
int solve(Board* board, Piece* pieces);

int solvePiece(Board* board, Piece* pieces, int pieceIndex);

#endif