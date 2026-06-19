//
// Created by eranc on 6/19/2026.
//

#include "Pawn.h"
Pawn::Pawn(bool isWhite) : Piece(isWhite) {}

PieceType Pawn::getType() const{
    return PieceType::Pawn;
}
char Pawn::getSymbol() const {
    return isWhite? 'p' : 'P';
}
std::vector<Move> Pawn::getValidMoves(const Board &board, int row, int col) const {
    //temporary!
    return {};
}