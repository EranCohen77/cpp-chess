//
// Created by eranc on 6/19/2026.
//
#ifndef CPP_CHESS_PAWN_H
#define CPP_CHESS_PAWN_H
#include <Piece.h>

class Pawn : public Piece {
public:
    explicit Pawn(bool isWhite);

    PieceType getType() const override;
    char getSymbol() const override;
    std::vector<Move> getValidMoves(
        const Board &board,
        int row,
        int col
        ) const override;
};


#endif //CPP_CHESS_PAWN_H