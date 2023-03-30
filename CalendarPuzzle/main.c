#pragma once
#include "board.h"
#include "piece.h"
#include "solver.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(void) {
	Board board;
	configureBoard(&board, SUNDAY, 12, OCTOBER);

	displayBoard(board);

	Piece *pieces = NULL;
	initPieces(pieces);

	bool placed = placePiece(&board, &pieces[0], 3, 3, 1);
	printPiece(pieces[0]);

	printf("Is placed? %d", placed);

	displayBoard(board);

	free(pieces);
	free(board.rows);
	//TODO: Free pieces array
	return 0;
}