//
// Created by eranc on 6/19/2026.
//

#include "Move.h"
#include "Piece.h"

Move::Move(int sRow, int sCol, int eRow, int eCol,
    Piece *moved, Piece *captured, PieceType promotionType):
startRow(sRow), startCol(sCol),
endRow(eRow), endCol(eCol),
movedPiece(moved), capturedPiece(captured),
movedPieceHadMoved(moved != nullptr && moved->getHasMoved()),
castlingRookHadMoved(false),
isCastling(false), isEnPassant(false), isPromotion(false),
promotionType(promotionType){}

std::string Move::toAlgebricNotation() const {
    if (isCastling) {
        return endCol > startCol? "O-O" : "O-O-O";
    }
    std::string res = "";
    if (movedPiece->getType() != PieceType::Pawn) {
        res += movedPiece->getSymbol();
    }
    if (capturedPiece != nullptr) {
        res += 'x';
    }
    res += (endCol + 'a');
    res += (endRow - 1);
    return res;
    //TODO finish implementation.
}
