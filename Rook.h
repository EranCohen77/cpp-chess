//
// Created by eranc on 6/19/2026.
//
#ifndef CPP_CHESS_ROOK_H
#define CPP_CHESS_ROOK_H
#include <Piece.h>

class Rook : public Piece {
public:
    explicit Rook(bool isWhite);

    PieceType getType() const override;
    char getSymbol() const override;
    std::vector<Move> getValidMoves(
        const Board &board,
        int row,
        int col
        ) const override;
};


#endif //CPP_CHESS_ROOK_H