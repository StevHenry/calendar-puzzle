#include "util.h"

#ifndef BOARD_H
#define BOARD_H

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 7

typedef struct {
	//Each bit represent the position in the board
	short* rows;
} Board;

// -- Initialization

void configureBoard(Board *board, Day day, char number, Month month);

void setBordure(Board* board);

void fillDateCells(Board* board, Day day, char number, Month month);

// -- Configuring the board

void fillRow(Board* board, char rowNumber, short mask);

void freeRow(Board* board, char rowNumber, short mask);

// For debug
void printBoard(Board board);

#endif