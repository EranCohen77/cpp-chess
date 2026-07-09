//
// Created by eranc on 6/19/2026.
//

#include "Rook.h"

#include "Board.h"
Rook::Rook(bool isWhite) : Piece(isWhite) {}

PieceType Rook::getType() const{
    return PieceType::Rook;
}
char Rook::getSymbol() const {
    return isWhite? 'r' : 'R';
}
std::vector<Move> Rook::getValidMoves(const Board &board, int row, int col) const {
    std::vector<Move> moves;

    int directions[4][2] = {
                            {1,0},
                            {0,1},
                            {-1,0},
                            {0,-1}
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