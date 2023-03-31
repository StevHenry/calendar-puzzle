#pragma once
#include "board.h"
#include "piece.h"
#include "solver.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(void) {
	Board board;
	Piece* pieces = calloc(10, sizeof(Piece));
	
	configureBoard(&board, SUNDAY, 4, OCTOBER);
	initPieces(pieces);
	//----

	printBoard(board);
	printPiece(pieces[0]);

	//placePiece(&board, &pieces[9], 2, 5);
	printf("Piece 9 placed? %d\n", placePiece(&board, &pieces[9], 1, 4));

	printf("Piece 6 placed? %d\n", placePiece(&board, &pieces[6], 2, 3));
	printf("Piece 8 placed? %d\n", placePiece(&board, &pieces[8], 4, 4));

	printf("Piece 5 placed? %d\n", placePiece(&board, &pieces[5], 4, 7));
	rotatePiece(&pieces[4]);
	rotatePiece(&pieces[4]);
	rotatePiece(&pieces[4]);
	printPiece(pieces[4]);
	printf("Piece 4 placed? %d\n", placePiece(&board, &pieces[4], 1, 1));
	printf("Piece 7 placed? %d\n", placePiece(&board, &pieces[7], 6, 6));

	printBoard(board);

	//----

	free(board.rows);
	for (char i=0; i<10; i++) {
		free(pieces[i].pieceRows);
	}
	free(pieces);
	return 0;
}