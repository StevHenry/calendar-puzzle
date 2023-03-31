#include "board.h"
#include "piece.h"
#include "solver.h"
#include <stdbool.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

bool canPlacePiece(Board* board, Piece* piece, char xPos, char yPos) {
    if (xPos + piece->width > BOARD_WIDTH || yPos - piece->height +1 < 0) {
        printf("Piece \n");
        return false;
    }

    for (char row = 0; row < piece->height; row++) {
        /*
        printf("INVERTED ROW %d : " BYTE_TO_BINARY_PATTERN "\n", row + yPos - piece->height + 1, BYTE_TO_BINARY(~(board->rows[row + yPos - piece->height + 1])));
        printf("INVERTED SHIFTED BY %d " BYTE_TO_BINARY_PATTERN "\n", 7 - xPos - piece->width + 1, BYTE_TO_BINARY(~(board->rows[row + yPos - piece->height + 1]) >> (7 - xPos - piece->width + 1)));
        printf("PIECE ROW " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(piece->pieceRows[row]));
        printf("MASK " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY((~(board->rows[row + yPos - piece->height+1]) >> (7 - xPos - piece->width + 1)) & piece->pieceRows[row]));
        printf("IS DIFFERENT %d\n", ((~(board->rows[row + yPos - piece->height + 1]) >> (7 - xPos - piece->width + 1)) & piece->pieceRows[row]) != piece->pieceRows[row]);*/

        if (((~(board->rows[row + yPos - piece->height+1]) >> (7 - xPos - piece->width + 1)) & piece->pieceRows[row]) != piece->pieceRows[row]) {
            return false;
        }
    }
    return true;
}


bool placePiece(Board* board, Piece* piece, char xPos, char yPos) {

    // Check if the piece can be placed on the board
    if (!canPlacePiece(board, piece, xPos, yPos)) {
        return false;
    }

    // Assign the piece to the board
    for (int row = 0; row < piece->height; row++) {
        fillRow(board, yPos - piece->height + 1 + row, piece->pieceRows[row] << (BOARD_WIDTH - xPos - piece->width + 1));
    }

    return true;
}


/*int solve(Board board, Pieces* pieces, Day day, int number, Month month) {
    int nbSolutions = 0;
    
    if (*pieces == {}) {
        nbSolutions++;
    } else {
        // iterate over all the pieces
        for (Piece* piece : *pieces) {
            // try placing the piece on the board in all possible positions
            for (int i = 0; i < board.width - piece.width; i++) {
                for (int j = 0; j < BOARD_HEIGHT - piece.height; j++) {
                    if (canPlacePiece(board, piece, i, j)) {
                        // place the piece on the board
                        placePiece(&board, &piece, i, j);
                        
                        // remove the piece from the pieces list
                        Pieces* remainingPieces = new Pieces(*pieces);
                        remainingPieces->remove(piece);
                        
                        // recursively call solve() with the new board and pieces list
                        nbSolutions += solve(board, remainingPieces, day, number, month);
                        
                        // remove the piece from the board and place it back in the pieces list
                        board.removePiece(piece, i, j);
                        remainingPieces->add(piece);
                        
                        // free memory allocated for remainingPieces
                        delete remainingPieces;
                    }
                }
            }
        }
    }
    
    return nbSolutions;
}



*/






