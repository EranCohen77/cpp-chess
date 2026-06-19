//
// Created by eranc on 6/19/2026.
//
#ifndef CPP_CHESS_PIECE_H
#define CPP_CHESS_PIECE_H
#include <vector>
#include "Move.h"
#include "PieceType.h"

class Board; class Move;

class Piece{
protected:
    //attributes
    bool isWhite;
    bool hasMoved;
public:
    //constructor and destructor
    explicit Piece(bool isWhite);
    virtual ~Piece() = default;

    //getters and setters
    bool getIsWhite() const;
    bool getHasMoved() const;
    void setHasMoved(bool moved);

    virtual PieceType getType() const = 0;
    virtual std::vector<Move> getValidMoves(const Board& board, int row, int col) const = 0;
    virtual char getSymbol() const = 0;
};


#endif //CPP_CHESS_PIECE_H