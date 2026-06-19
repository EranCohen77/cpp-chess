//
// Created by eranc on 6/19/2026.
//

#include "Knight.h"
Knight::Knight(bool isWhite) : Piece(isWhite) {}

PieceType Knight::getType() const{
    return PieceType::Knight;
}
char Knight::getSymbol() const {
    return isWhite? 'n' : 'N';
}
std::vector<Move> Knight::getValidMoves(const Board &board, int row, int col) const {
    //temporary!
    return {};
}