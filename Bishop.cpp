//
// Created by eranc on 6/19/2026.
//

#include "Bishop.h"
Bishop::Bishop(bool isWhite) : Piece(isWhite) {}

PieceType Bishop::getType() const{
    return PieceType::Bishop;
}
char Bishop::getSymbol() const {
    return isWhite? 'b' : 'B';
}
std::vector<Move> Bishop::getValidMoves(const Board &board, int row, int col) const {
    //temporary!
    return {};
}