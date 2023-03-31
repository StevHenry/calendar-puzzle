#ifndef PIECE_H
#define PIECE_H

typedef struct {
    char* pieceRows;
    char height;
    char width;
} Piece;

//--- Initialization

void initPieces(Piece* pieces);

// --- Util

void rotatePiece(Piece *piece);

void mirrorPiece(Piece *piece);

// --- Debug

void printPiece(Piece piece);

#endif