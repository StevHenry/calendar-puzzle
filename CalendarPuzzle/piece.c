#include <stdio.h>
#include <stdlib.h>
#include "piece.h"

/* Shows a piece in the console (for debug only)*/
void displayPiece(Piece piece) {
	printf("<- Piece ->\n");
    for (int row = piece.height-1; row >= 0; row--) {
        for (int column = 0; column < piece.width; column++) {
            printf("%d", (piece.pieceRows[row] >> column) & 1);
        }
        printf("\n");
    }
	printf("<- Piece end ->\n");
}

void initPieces(Piece *pieces) {
	pieces = calloc(10, sizeof(Piece));
	if (pieces == NULL) {
		// Handle allocation error
		return NULL;
	}

	pieces[0] = (Piece){ (char[]) { 0b1, 0b1, 0b1, 0b11 }, 4, 2 };
	pieces[1] = (Piece){ (char[]) { 0b10, 0b10, 0b111 }, 3, 3 };
	pieces[2] = (Piece){ (char[]) { 0b111, 0b100, 0b100 }, 3, 3 };
	pieces[3] = (Piece){ (char[]) { 0b110, 0b010, 0b011 }, 3, 3 };
	pieces[4] = (Piece){ (char[]) { 0b1, 0b1, 0b11, 0b10 }, 3, 2 };
	pieces[5] = (Piece){ (char[]) { 0b101, 0b111 }, 2, 3 };
	pieces[6] = (Piece){ (char[]) { 0b10, 0b11, 0b11 }, 3, 2 };
	pieces[7] = (Piece){ (char[]) { 0b01, 0b01, 0b11 }, 3, 2 };
	pieces[8] = (Piece){ (char[]) { 0b10, 0b11, 0b01 }, 3, 2 };
	pieces[9] = (Piece){ (char[]) { 0b1111 }, 1, 4 };
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
