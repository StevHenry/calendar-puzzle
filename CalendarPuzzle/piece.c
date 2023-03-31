#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "piece.h"

/* Shows a piece in the console (for debug only)*/
void printPiece(Piece piece) {
	printf("<- Piece ->\n");
	for (char row = 0; row < piece.height; row++) {
        for (char column = piece.width-1; column >= 0; column--) {
            printf("%d", (piece.pieceRows[row] >> column) & 1);
        }
        printf("\n");
    }
	printf("<- Piece end ->\n");
}

void initPieces(Piece* pieces) {
	pieces[0] = (Piece){ malloc(4 * sizeof(char)), 4, 2, false };
	pieces[1] = (Piece){ malloc(4 * sizeof(char)), 3, 3, false };
	pieces[2] = (Piece){ malloc(4 * sizeof(char)), 3, 3, false };
	pieces[3] = (Piece){ malloc(4 * sizeof(char)), 3, 3, true };
	pieces[4] = (Piece){ malloc(4 * sizeof(char)), 4, 2, false };
	pieces[5] = (Piece){ malloc(4 * sizeof(char)), 2, 3, false };
	pieces[6] = (Piece){ malloc(4 * sizeof(char)), 3, 2, false };
	pieces[7] = (Piece){ malloc(4 * sizeof(char)), 3, 2, false };
	pieces[8] = (Piece){ malloc(4 * sizeof(char)), 3, 2, true };
	pieces[9] = (Piece){ malloc(4 * sizeof(char)), 1, 4, true };

	for (char i = 0; i < 10; i++) {
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

void rotatePiece(Piece* piece) {
	// Allocate memory for the rotated piece
	char* rotatedPieceRows = calloc(4, sizeof(char));

	// Rotate the piece
	for (int row = 0; row < piece->height; row++) {
		for (int col = 0; col < piece->width; col++) {
			int rotatedRow = col;
			int rotatedCol = piece->height - 1 - row;
			char value = (piece->pieceRows[row] >> (piece->width - 1 - col)) & 1;
			rotatedPieceRows[rotatedRow] |= value << (piece->height - 1 - rotatedCol);
		}
	}
	int temp = piece->width;  // Swap the height and width
	piece->width = piece->height;
	piece->height = temp;

	// Copy the rotated piece back into the original piece
	memcpy(piece->pieceRows, rotatedPieceRows, 4 * sizeof(char));

	// Free the memory used by the rotated piece
	free(rotatedPieceRows);
}


/*void mirrorPiece(Piece* piece) {
	// Flip the piece horizontally
	for (int row = 0; row < piece->height; row++) {
		for (int col = 0; col < piece->width / 2; col++) {
			char temp = (piece->pieceRows[row] >> col) & 1;
			piece->pieceRows[row] &= ~(1 << col);
			piece->pieceRows[row] |= ((piece->pieceRows[row] >> (piece->width - 1 - col)) & 1) << col;
			piece->pieceRows[row] &= ~(1 << (piece->width - 1 - col));
			piece->pieceRows[row] |= temp << (piece->width - 1 - col);
		}
	}
}*/
