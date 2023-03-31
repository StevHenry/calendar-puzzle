#pragma once
#include "board.h"
#include "shape.h"
#include "solver.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
# include<time.h>

ComputationResult compute(char dayNumber, Day day, Month month) {
	//- Initialization
	Board board;
	Piece* pieces = calloc(PIECES_COUNT, sizeof(Piece));
	StopingPattern* stopingPatterns = calloc(STOPPING_PATTERNS_COUNT, sizeof(StopingPattern));

	configureBoard(&board, day, dayNumber, month);
	initPieces(pieces);
	initStopingPatterns(stopingPatterns);

	//- Solver
	clock_t start, end;

	start = clock();
	int resultCount = solve(&board, pieces, stopingPatterns);
	end = clock();

	double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("%d solutions were found in %.2f seconds for day %d/%d (day %d of week)\n",
		resultCount, execution_time, dayNumber, month, day + 1);

	//- Memory freeing
	free(board.rows);
	for (char pieceIndex = 0; pieceIndex < PIECES_COUNT; pieceIndex++) {
		free(pieces[pieceIndex].pieceRows);
	}
	free(pieces);
	for (char patternIndex = 0; patternIndex < STOPPING_PATTERNS_COUNT; patternIndex++) {
		free(stopingPatterns[patternIndex].patternRows);
		free(stopingPatterns[patternIndex].patternMask);
	}
	free(stopingPatterns);

	return (ComputationResult) { dayNumber, day, month, resultCount, execution_time };
}


int main(void) {
	// 31 dates aléatoires
	srand(time(NULL));

	ComputationResult *results = calloc(31, sizeof(ComputationResult));
	if (results == NULL) {
		perror("Cannot allocate enough memory to save the computation results.");
		return;
	}
	for (char i = 0; i < 31; i++) {
		//results[i] = compute((rand() % 31) + 1, rand() % 7, (rand() % 12) + 1);
	}
	compute(1, SATURDAY, JANUARY);
	compute(1, SATURDAY, JANUARY);
	compute(1, SATURDAY, JANUARY);
	compute(1, SATURDAY, JANUARY);
	compute(1, SATURDAY, JANUARY);
	compute(1, SATURDAY, JANUARY);
	compute(1, SATURDAY, JANUARY);

	writeResults(".\\results.csv", results);
	free(results);
	
	return 0;
}
