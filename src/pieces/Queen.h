//
// Created by eranc on 6/19/2026.
//
#ifndef CPP_CHESS_QUEEN_H
#define CPP_CHESS_QUEEN_H
#include<Piece.h>

class Queen : public Piece {
public:
    explicit Queen(bool isWhite);

    PieceType getType() const override;
    char getSymbol() const override;
    std::vector<Move> getValidMoves(
        const Board &board,
        int row,
        int col
        ) const override;
};


#endif //CPP_CHESS_QUEEN_H