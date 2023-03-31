#include <stdbool.h>

#ifndef PIECE_H
#define PIECE_H

typedef struct {
    char* pieceRows;
    char height;
    char width;
    bool symetric;

} Piece;

//--- Initialization

void initPieces(Piece* pieces);

// --- Util

void rotatePiece(Piece *piece);

// --- Debug

void printPiece(Piece piece);

#endif