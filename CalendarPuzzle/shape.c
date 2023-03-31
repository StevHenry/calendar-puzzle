#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "shape.h"

// ----- INITIALIZATION -----

/* Initializes the 10 pieces of the problem, oriented as in the subject presentation */
void initPieces(Piece* pieces) {
	pieces[0] = (Piece){ malloc(4 * sizeof(char)), 4, 2, false };
	pieces[1] = (Piece){ malloc(3 * sizeof(char)), 3, 3, false };
	pieces[2] = (Piece){ malloc(3 * sizeof(char)), 3, 3, false };
	pieces[3] = (Piece){ malloc(3 * sizeof(char)), 3, 3, true }; // this piece is symetric 
	pieces[4] = (Piece){ malloc(4 * sizeof(char)), 4, 2, false };
	pieces[5] = (Piece){ malloc(3 * sizeof(char)), 2, 3, false };
	pieces[6] = (Piece){ malloc(3 * sizeof(char)), 3, 2, false };
	pieces[7] = (Piece){ malloc(3 * sizeof(char)), 3, 2, false };
	pieces[8] = (Piece){ malloc(3 * sizeof(char)), 3, 2, true };
	pieces[9] = (Piece){ malloc(4 * sizeof(char)), 1, 4, true };

	for (char i = 0; i < PIECES_COUNT; i++) {
		if (pieces[i].pieceRows == NULL) {
			perror("Error while trying to allocate memory for pieces!");
			return;
		}
	}
	
	memcpy(pieces[0].pieceRows, (char[]) { 0b01, 0b01, 0b01, 0b11 }, pieces[0].height);
	memcpy(pieces[1].pieceRows, (char[]) { 0b010, 0b010, 0b111 }, pieces[1].height);
	memcpy(pieces[2].pieceRows, (char[]) { 0b111, 0b100, 0b100 }, pieces[2].height);
	memcpy(pieces[3].pieceRows, (char[]) { 0b110, 0b010, 0b011 }, pieces[3].height);
	memcpy(pieces[4].pieceRows, (char[]) { 0b01, 0b01, 0b11, 0b10 }, pieces[4].height);
	memcpy(pieces[5].pieceRows, (char[]) { 0b101, 0b111 }, pieces[5].height);
	memcpy(pieces[6].pieceRows, (char[]) { 0b10, 0b11, 0b11 }, pieces[6].height);
	memcpy(pieces[7].pieceRows, (char[]) { 0b01, 0b01, 0b11 }, pieces[7].height);
	memcpy(pieces[8].pieceRows, (char[]) { 0b10, 0b11, 0b01 }, pieces[8].height);
	memcpy(pieces[9].pieceRows, (char[]) { 0b1111 }, pieces[9].height);
}

// we defined 6 "stopping patterns" in order not to waste time by quickly detecting when a configuration is impossible
void initStopingPatterns(StopingPattern* patterns) {
	patterns[0] = (StopingPattern){ malloc(3 * sizeof(char)), malloc(3 * sizeof(char)), 3, 3 };
	patterns[1] = (StopingPattern){ malloc(3 * sizeof(char)), malloc(3 * sizeof(char)), 3, 4 };
	patterns[2] = (StopingPattern){ malloc(3 * sizeof(char)), malloc(3 * sizeof(char)), 3, 5 };
	patterns[3] = (StopingPattern){ malloc(4 * sizeof(char)), malloc(4 * sizeof(char)), 4, 3 };
	patterns[4] = (StopingPattern){ malloc(5 * sizeof(char)), malloc(5 * sizeof(char)), 5, 3 };
	patterns[5] = (StopingPattern){ malloc(4 * sizeof(char)), malloc(4 * sizeof(char)), 4, 4 };
	//patterns[6] = (StopingPattern){ malloc(4 * sizeof(char)), malloc(4 * sizeof(char)), 4, 5 };
	//patterns[7] = (StopingPattern){ malloc(5 * sizeof(char)), malloc(5 * sizeof(char)), 5, 4 };
	//patterns[8] = (StopingPattern){ malloc(4 * sizeof(char)), malloc(4 * sizeof(char)), 4, 5 };
	//patterns[9] = (StopingPattern){ malloc(5 * sizeof(char)), malloc(5 * sizeof(char)), 5, 4 };
	patterns[6] = (StopingPattern){ malloc(4 * sizeof(char)), malloc(4 * sizeof(char)), 4, 4 };
	patterns[7] = (StopingPattern){ malloc(4 * sizeof(char)), malloc(4 * sizeof(char)), 4, 4 };
	patterns[8] = (StopingPattern){ malloc(4 * sizeof(char)), malloc(4 * sizeof(char)), 4, 4 };
	patterns[9] = (StopingPattern){ malloc(4 * sizeof(char)), malloc(4 * sizeof(char)), 4, 4 };
	//patterns[14] = (StopingPattern){ malloc(5 * sizeof(char)), malloc(5 * sizeof(char)), 5, 5 };

	for (char i = 0; i < STOPPING_PATTERNS_COUNT; i++) {
		if (patterns[i].patternRows == NULL) {
			perror("Error while trying to allocate memory for pieces!");
			return;
		}
	}
	memcpy(patterns[0].patternRows, (char[]) { 0b010, 0b101, 0b010 }, patterns[0].height);
	memcpy(patterns[1].patternRows, (char[]) { 0b0110, 0b1001, 0b0110 }, patterns[1].height);
	memcpy(patterns[2].patternRows, (char[]) { 0b01110, 0b10001, 0b01110 }, patterns[2].height);
	memcpy(patterns[3].patternRows, (char[]) { 0b010, 0b101, 0b101, 0b010 }, patterns[3].height);
	memcpy(patterns[4].patternRows, (char[]) { 0b010, 0b101, 0b101, 0b101, 0b010 }, patterns[4].height);
	memcpy(patterns[5].patternRows, (char[]) { 0b0110, 0b1001, 0b1001, 0b0110 }, patterns[5].height);
	//memcpy(patterns[6].patternRows, (char[]) { 0b01110, 0b10001, 0b01010, 0b00100 }, patterns[6].height);
	//memcpy(patterns[7].patternRows, (char[]) { 0b0010, 0b0101, 0b1001, 0b0101, 0b0010 }, patterns[7].height);
	//memcpy(patterns[8].patternRows, (char[]) { 0b00100, 0b01010, 0b10001, 0b01110 }, patterns[8].height);
	//memcpy(patterns[9].patternRows, (char[]) { 0b0100, 0b1010, 0b1001, 0b1010, 0b0100 }, patterns[9].height);
	memcpy(patterns[6].patternRows, (char[]) { 0b0110, 0b1001, 0b1010, 0b0100 }, patterns[6].height);
	memcpy(patterns[7].patternRows, (char[]) { 0b0110, 0b1001, 0b0101, 0b0010 }, patterns[8].height);
	memcpy(patterns[8].patternRows, (char[]) { 0b0010, 0b0101, 0b1001, 0b0110 }, patterns[8].height);
	memcpy(patterns[9].patternRows, (char[]) { 0b0100, 0b1010, 0b1001, 0b0110 }, patterns[9].height);
	//memcpy(patterns[14].patternRows, (char[]) { 0b00100, 0b01010, 0b10001, 0b01010, 0b00100 }, patterns[14].height);

	memcpy(patterns[0].patternMask, (char[]) { 0b010, 0b111, 0b010 }, patterns[0].height);
	memcpy(patterns[1].patternMask, (char[]) { 0b0110, 0b1111, 0b0110 }, patterns[1].height);
	memcpy(patterns[2].patternMask, (char[]) { 0b01110, 0b11111, 0b01110 }, patterns[2].height);
	memcpy(patterns[3].patternMask, (char[]) { 0b010, 0b111, 0b111, 0b010 }, patterns[3].height);
	memcpy(patterns[4].patternMask, (char[]) { 0b010, 0b111, 0b111, 0b111, 0b010 }, patterns[4].height);
	memcpy(patterns[5].patternMask, (char[]) { 0b0110, 0b1111, 0b1111, 0b0110 }, patterns[5].height);
	//memcpy(patterns[6].patternMask, (char[]) { 0b01110, 0b11111, 0b01110, 0b00100 }, patterns[6].height);
	//memcpy(patterns[7].patternMask, (char[]) { 0b0010, 0b0111, 0b1111, 0b0111, 0b0010 }, patterns[7].height);
	//memcpy(patterns[8].patternMask, (char[]) { 0b00100, 0b01110, 0b11111, 0b01110 }, patterns[8].height);
	//memcpy(patterns[9].patternMask, (char[]) { 0b0100, 0b1110, 0b1111, 0b1110, 0b0100 }, patterns[9].height);
	memcpy(patterns[6].patternMask, (char[]) { 0b0110, 0b1111, 0b1110, 0b0100 }, patterns[6].height);
	memcpy(patterns[7].patternMask, (char[]) { 0b0110, 0b1111, 0b0111, 0b0010 }, patterns[7].height);
	memcpy(patterns[8].patternMask, (char[]) { 0b0010, 0b0111, 0b1111, 0b0110 }, patterns[8].height);
	memcpy(patterns[9].patternMask, (char[]) { 0b0100, 0b1110, 0b1111, 0b0110 }, patterns[9].height);
	//memcpy(patterns[14].patternMask, (char[]) { 0b00100, 0b01110, 0b1111, 0b01110,0b00100 }, patterns[14].height);
}

// ----- UTIL -----

/* this function rotates a piece by 90° clockwise. Also saves the new orientation in the piece directly */
void rotatePiece(Piece* piece) {
	// Allocate memory for the rotated piece
	char* rotatedPieceRows = calloc(4, sizeof(short));

	// Rotate the piece
	for (char row = 0; row < piece->height; row++) {
		for (char col = 0; col < piece->width; col++) {
			char rotatedRow = col;
			char rotatedCol = piece->height - 1 - row;
			char value = (piece->pieceRows[row] >> (piece->width - 1 - col)) & 1;
			rotatedPieceRows[rotatedRow] |= value << (piece->height - 1 - rotatedCol);
		}
	}
	// Swap the height and width
	char temp = piece->width;  
	piece->width = piece->height;
	piece->height = temp;

	memcpy(piece->pieceRows, rotatedPieceRows, 4 * sizeof(char));
	free(rotatedPieceRows);
}

// ----- DEBUG -----

/* Prints a piece in the console (for debug only) */
void printPiece(Piece piece) {
	printf("<- Piece ->\n");
	for (char row = 0; row < piece.height; row++) {
		for (char column = piece.width - 1; column >= 0; column--) {
			printf("%d", (piece.pieceRows[row] >> column) & 1);
		}
		printf("\n");
	}
	printf("<- Piece end ->\n");
}


/* Prints a pattern in the console (for debug only) */
void printStopingPattern(StopingPattern pattern) {
	printf("<- Pattern (Mask|Shape)->\n");
	for (char row = 0; row < pattern.height; row++) {
		for (char column = pattern.width - 1; column >= 0; column--) {
			printf("%d", (pattern.patternMask[row] >> column) & 1);
		}
		printf(" | ");
		for (char column = pattern.width - 1; column >= 0; column--) {
			printf("%d", (pattern.patternRows[row] >> column) & 1);
		}
		printf("\n");
	}
	printf("<- Pattern end ->\n");
}
