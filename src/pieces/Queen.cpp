//
// Created by eranc on 6/19/2026.
//

#include "Queen.h"

#include "Board.h"
Queen::Queen(bool isWhite) : Piece(isWhite) {}

PieceType Queen::getType() const{
    return PieceType::Queen;
}
char Queen::getSymbol() const {
    return isWhite? 'q' : 'Q';
}
std::vector<Move> Queen::getValidMoves(const Board &board, int row, int col) const {
    std::vector<Move> moves;

    int directions[8][2] = {
        {1,0},
        {0,1},
        {-1,0},
        {0,-1},
        {1,1},
        {-1,1},
        {-1,-1},
        {1,-1}
    };
    for (const auto& direction : directions) {
        int targetRow = row;
        int targetCol = col;
        bool blocked = false;
        while (!blocked) {
            targetRow += direction[0];
            targetCol += direction[1];
            if (targetRow < 0 || targetRow >= 8 || targetCol < 0 || targetCol >= 8) {
                blocked = true;
            } else {
                Piece* target = board.getPiece(targetRow,targetCol);
                if (target == nullptr)
                    moves.emplace_back(row, col, targetRow, targetCol,
                        board.getPiece(row, col), target);
                else if (target->getIsWhite() != isWhite) {
                    moves.emplace_back(row, col, targetRow, targetCol,
                        board.getPiece(row, col), target);
                    blocked = true;
                } else {
                    blocked = true;
                }
            }
        }
    }
    return moves;
}