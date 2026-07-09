//
// Created by eranc on 6/19/2026.
//

#include "Knight.h"
#include "Board.h"
Knight::Knight(bool isWhite) : Piece(isWhite) {}

PieceType Knight::getType() const{
    return PieceType::Knight;
}
char Knight::getSymbol() const {
    return isWhite? 'n' : 'N';
}
std::vector<Move> Knight::getValidMoves(const Board &board, int row, int col) const {
    std::vector<Move> moves;
    const int offsets[8][2] = {
        {-2, -1}, {-2, 1},
        {-1, -2}, {-1, 2},
        {1, -2}, {1, 2},
        {2, -1}, {2, 1}
    };

    for (const auto& offset : offsets) {
        int targetRow = row + offset[0];
        int targetCol = col + offset[1];

        if (targetRow < 0 || targetRow >= 8 || targetCol < 0 || targetCol >= 8) {
            continue;
        }

        Piece* target = board.getPiece(targetRow, targetCol);
        if (target == nullptr || target->getIsWhite() != isWhite) {
            moves.emplace_back(row, col, targetRow, targetCol,
                board.getPiece(row, col), target);
        }
    }

    return moves;
}
