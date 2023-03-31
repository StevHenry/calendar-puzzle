#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "board.h"

// ----- INITIALIZATION -----

void configureBoard(Board* board, Day day, char number, Month month) {
	board->rows = calloc(10, sizeof(short));
	setBordure(board);
	fillDateCells(board, day, number, month);
}

/* Fills the cells that set the boundaries of the Board */
void setBordure(Board* board) {
	for (char row = 0; row < BOARD_HEIGHT; row++) {
		fillRow(board, row, 0b100000001);
	}

	fillRow(board, -1, 0b111111111);
	fillRow(board, 0, 0b00000010);
	fillRow(board, 1, 0b00000010);
	fillRow(board, 7, 0b11110000);
	fillRow(board, 8, 0b111111111);
}

/* Fills the cells associated to the provided day */
void fillDateCells(Board* board, Day day, char number, Month month) {
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
	fillRow(board, (month - 1) / 6, 0b10000000 >> (month - 1) % 6);
	// Figure
	fillRow(board, 2 + ((number - 1) / 7), 0b10000000 >> (number - 1) % 7);
}

// ----- UTIL -----

/* Fills a row of the specified board */
void fillRow(Board* board, char rowNumber, short mask) {
	board->rows[rowNumber + 1] |= mask;
}

/* Free a row of the specified board */
void freeRow(Board* board, char rowNumber, short mask) {
	board->rows[rowNumber + 1] &= ~mask;
}

// ----- DEBUGGING -----

/* Shows the full board on console */
void printBoard(Board board) {
	printf("<- Board ->\n");
	for (char row = 0; row < BOARD_HEIGHT; row++) {
		for (char column = 7; column >= 1; column--) {
			printf("%d", (board.rows[row] >> column) & 1);
		}
		printf("\n");
	}
	printf("<- Board end ->\n");
}