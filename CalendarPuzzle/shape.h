#include <stdbool.h>

#ifndef PIECE_H
#define PIECE_H

#define STOPPING_PATTERNS_COUNT 10
#define PIECES_COUNT 10

typedef struct {
    char* pieceRows;
    char height;
    char width;
    bool symetric;
} Piece;

typedef struct {
    char* patternRows;
    char* patternMask;
    char height;
    char width;
} StopingPattern;


//--- Initialization

void initPieces(Piece* pieces);

void initStopingPatterns(StopingPattern* patterns);

// --- Util

void rotatePiece(Piece *piece);

// --- Debug

void printPiece(Piece piece);

void printStopingPattern(StopingPattern pattern);

#endif