#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "board.h"

/* Fills a cell of the specified board */
void fillRow(Board* board, char rowNumber, char mask) {
	board->rows[rowNumber] |= mask;
}

/* Frees a cell of the specified board */
void freeRow(Board* board, char rowNumber, char mask) {
	board->rows[rowNumber] &= ~mask;
}

void configureBoard(Board* board, Day day, int number, Month month) {
	board->rows = calloc(8, sizeof(char));
	setBordure(board);
	fillDateCells(board, day, number, month);
}

/* Shows the full board on console */
void printBoard(Board board) {
	printf("<- Board ->\n");
	for (int row = 0; row < BOARD_HEIGHT; row++) {
		for (int column = 7; column >= 1; column--) {
			//TODO: REPLACE 7 BY BOARD_WIDTH-1
			printf("%d", (board.rows[row] >> column) & 1);
		}
		printf("\n");
	}
	printf("<- Board end ->\n");
}

/* Fills the cells that set the boundaries of the Board */
void setBordure(Board *board) {
	for (int row = 0; row < BOARD_HEIGHT; row++) {
		fillRow(board, row, 0b00000001);
	}
	fillRow(board, 0, 0b00000010);
	fillRow(board, 1, 0b00000010);
	fillRow(board, 7, 0b11110000);
}

/* Fills the cells associated to the provided day */
void fillDateCells(Board *board, Day day, int number, Month month) {
	// Day
	if (day <= WEDNESDAY) {
		// SUNDAY to WEDNESDAY (Line 6 position 3 + day (0 to 3))
		fillRow(board, 6, 0b00010000 >> day);
	}
	else {
		//THURSDAY to SUNDAY (Line 7 position day (4 to 6))
		fillRow(board, 7, 0b10000000 >> day);
	}
	// Month
	fillRow(board, (month - 1) / 6, 0b10000000 >> (month -1 ) % 6);
	// Figure
	fillRow(board, 2 + ((number - 1) / 7), 0b10000000 >> (number -1 ) % 7);
}
