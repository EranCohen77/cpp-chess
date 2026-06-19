//
// Created by eranc on 6/19/2026.
//

#include "Queen.h"
Queen::Queen(bool isWhite) : Piece(isWhite) {}

PieceType Queen::getType() const{
    return PieceType::Queen;
}
char Queen::getSymbol() const {
    return isWhite? 'q' : 'Q';
}
std::vector<Move> Queen::getValidMoves(const Board &board, int row, int col) const {
    //temporary!
    return {};
}