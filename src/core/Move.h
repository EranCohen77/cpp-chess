//
// Created by eranc on 6/19/2026.
//
#pragma once

#ifndef CPP_CHESS_MOVE_H
#define CPP_CHESS_MOVE_H
#include <string>
#include "PieceType.h"

class Piece;

class Move {
public:
    int startRow;
    int startCol;
    int endRow;
    int endCol;

    Piece* movedPiece;
    Piece* capturedPiece;
    bool movedPieceHadMoved;
    mutable bool castlingRookHadMoved;

    bool isCastling;
    bool isEnPassant;
    bool isPromotion;
    PieceType promotionType;

    Move(int sRow, int sCol, int eRow, int eCol,
        Piece* moved, Piece* captured,
        PieceType promotionType = PieceType::Queen);

    std::string toAlgebricNotation() const;
};


#endif //CPP_CHESS_MOVE_H
