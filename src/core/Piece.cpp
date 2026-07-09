//
// Created by eranc on 6/19/2026.
//
#include "Piece.h"

Piece::Piece(bool isWhite):
isWhite(isWhite), hasMoved(false){
}
bool Piece::getIsWhite() const {
    return isWhite;
}
bool Piece::getHasMoved() const {
    return hasMoved;
}
void Piece::setHasMoved(bool moved) {
    hasMoved = moved;
}


