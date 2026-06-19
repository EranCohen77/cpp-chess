//
// Created by eranc on 6/19/2026.
//

#include "King.h"
King::King(bool isWhite) : Piece(isWhite) {}

PieceType King::getType() const{
    return PieceType::King;
}
char King::getSymbol() const {
    return isWhite? 'k' : 'K';
}
std::vector<Move> King::getValidMoves(const Board &board, int row, int col) const {
    //temporary!
    return {};
}
