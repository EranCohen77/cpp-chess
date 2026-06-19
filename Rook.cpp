//
// Created by eranc on 6/19/2026.
//

#include "Rook.h"
Rook::Rook(bool isWhite) : Piece(isWhite) {}

PieceType Rook::getType() const{
    return PieceType::Rook;
}
char Rook::getSymbol() const {
    return isWhite? 'r' : 'R';
}
std::vector<Move> Rook::getValidMoves(const Board &board, int row, int col) const {
    //temporary!
    return {};
}