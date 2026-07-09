//
// Created by eranc on 6/19/2026.
//

#ifndef CPP_CHESS_BOARD_H
#define CPP_CHESS_BOARD_H
#include <optional>

#include "Piece.h"

class Board {
private:
    Piece* grid[8][8];
    std::optional<Move> lastMove;
public:
    Board();
    ~Board();

    Piece* getPiece(int row, int col) const;
    void setPiece(int row, int col, Piece* piece);
    const Move* getLastMove() const;
    void setLastMove(const Move& move);
    void clearLastMove();

    void executeMove(const Move& move);
    void undoMove(const Move& move);

    bool isPositionUnderAttack(int row, int col, bool attackerIsWhite) const;
    bool isInCheck(bool attackerIsWhite) const;
    bool isCheckMate(bool attackerIsWhite);
};


#endif //CPP_CHESS_BOARD_H
