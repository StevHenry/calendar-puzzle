#include "board.h"
#include "piece.h"
#include "solver.h"
#include <stdbool.h>

bool placePiece(Board* board, Piece* piece, int row, int col, int rotation) {
	// Rotate the piece according to the specified rotation
	for (int i = 0; i < rotation; i++) {
		rotatePiece(piece);
	}

	// Check if the piece fits on the board
	if (row + piece->height > BOARD_HEIGHT || col + piece->width > BOARD_WIDTH) {
		return false;
	}

	// Check if any of the squares where the piece would be placed are already occupied
	for (int i = 0; i < piece->height; i++) {
		for (int j = 0; j < piece->width; j++) {
			if (piece->pieceRows[i] & (1 << (piece->width - j - 1))) {
				if (board->rows[row + i] & (1 << (BOARD_WIDTH - col - j - 1))) {
					return false;
				}
			}
		}
	}

	// Assign the piece to the board
	for (int i = 0; i < piece->height; i++) {
		char mask = 0;
		for (int j = 0; j < piece->width; j++) {
			if (piece->pieceRows[i] & (1 << (piece->width - j - 1))) {
				mask |= (1 << (BOARD_WIDTH - col - j - 1));
			}
		}
		fillRow(board, row + i, mask);
	}

	return true;
}



