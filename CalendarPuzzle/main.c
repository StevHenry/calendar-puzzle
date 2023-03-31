#pragma once
#include "board.h"
#include "piece.h"
#include "solver.h"
#include <stdlib.h>
#include <stdio.h>
# include<time.h>

int main(void) {
	//- Initialization
	Board board;
	Piece* pieces = calloc(10, sizeof(Piece));
	
	configureBoard(&board, SATURDAY, 1, JANUARY);
	initPieces(pieces);
	printf("Board configured to the specified date is: \n");
	printBoard(board);

	//- Solver
	clock_t start, end;

	start = clock();
	int result = solve(&board, pieces);
	end = clock();
	
	if (result) {
		double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("%d solutions were found in %.2f seconds\n", result, execution_time);
		printBoard(board);
	}
	else {
		printf("No solution found...\n");
	}
	
	//- Memory freeing
	free(board.rows);

	for (char pieceIndex = 0; pieceIndex < 10; pieceIndex++) {
		free(pieces[pieceIndex].pieceRows);
	}
	free(pieces);

	return 0;
}