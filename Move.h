//
// Created by eranc on 6/19/2026.
//
#pragma once

#ifndef CPP_CHESS_MOVE_H
#define CPP_CHESS_MOVE_H
#include <string>

class Piece;

class Move {
public:
    int startRow;
    int startCol;
    int endRow;
    int endCol;

    Piece* movedPiece;
    Piece* capturedPiece;

    bool isCastling;
    bool isEnPassant;
    bool isPromotion;

    Move(int sRow, int sCol, int eRow, int eCol, Piece* moved, Piece* captured);

    std::string toAlgebricNotation() const;
};


#endif //CPP_CHESS_MOVE_H