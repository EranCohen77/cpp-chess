//
// Created by eranc on 6/19/2026.
//

#include "Move.h"

Move::Move(int sRow, int sCol, int eRow, int eCol, Piece *moved, Piece *captured):
startRow(sRow), startCol(sCol),
endRow(eRow), endCol(eCol),
movedPiece(moved), capturedPiece(captured),
isCastling(false), isEnPassant(false), isPromotion(false){
}
