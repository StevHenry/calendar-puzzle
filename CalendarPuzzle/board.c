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
void displayBoard(Board board) {
	printf("<- Board ->\n");
	for (int row = 7; row >= 0; row--) {
		for (int column = 0; column < 8; column++) {
			printf("%d", (board.rows[row] >> column) & 1);
		}
		printf("\n");
	}
	printf("<- Board end ->\n");
}

/* Fills the cells that set the boundaries of the Board */
void setBordure(Board *board) {
	for (int row = 0; row < BOARD_HEIGHT; row++) {
		fillRow(board, row, 0b1 << BOARD_WIDTH);
	}
	fillRow(board, 0, 0b1111);
	fillRow(board, 7, 0b01000000);
	fillRow(board, 6, 0b01000000);
}

/* Fills the cells associated to the provided day */
void fillDateCells(Board *board, Day day, int number, Month month) {
	// Day
	if (day <= WEDNESDAY) {
		// SUNDAY to WEDNESDAY (Line 1 position 3 + day (0 to 3))
		fillRow(board, 1, 0b1 << 3 + day);
	}
	else {
		//THURSDAY to SUNDAY (Line 0 position day (4 to 6))
		fillRow(board, 0, 0b1 << day);
	}
	// Month
	fillRow(board, 0b1 << month - 1, BOARD_HEIGHT - 1 - ((month-1) / 6));
	// Figure
	fillRow(board, 5 - ((number - 1) / 7), 0b1 << BOARD_HEIGHT - 1 - (number-1)%7);
}
