#ifndef BOARD_H
#define BOARD_H

#include "util.h"

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 7

typedef struct {
	//Each bit represent the position in the board
	char* rows;
} Board;

void configureBoard(Board *board, Day day, int number, Month month);

void fillRow(Board* board, char rowNumber, char mask);

void freeRow(Board* board, char rowNumber, char mask);

void printBoard(Board board);

void setBordure(Board *board);

void fillDateCells(Board *board, Day day, int number, Month month);

#endif