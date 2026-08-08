//
// Created by eranc on 6/19/2026.
//

#include "King.h"

#include "Board.h"
King::King(bool isWhite) : Piece(isWhite) {}

PieceType King::getType() const{
    return PieceType::King;
}
char King::getSymbol() const {
    return isWhite? 'k' : 'K';
}
std::vector<Move> King::getValidMoves(const Board &board, int row, int col) const {
    std::vector<Move> moves;
    const int offsets[8][2] = {
        {1,0},
        {0,1},
        {-1,0},
        {0,-1},
        {1,1},
        {-1,1},
        {-1,-1},
        {1,-1}
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

    //check for castling possibility
    if (!hasMoved && !board.isInCheck(!isWhite)) {
        const int short_castling_rook_row = row;
        const int short_castling_rook_col = 7;

        const int long_castling_rook_row = row;
        const int long_castling_rook_col = 0;

        const Piece* short_castling_rook = board.getPiece(short_castling_rook_row, short_castling_rook_col);
        const Piece* long_castling_rook = board.getPiece(long_castling_rook_row, long_castling_rook_col);

        //short castling check
        if (short_castling_rook != nullptr &&
            short_castling_rook->getType() == PieceType::Rook &&
            short_castling_rook->getIsWhite() == isWhite &&
            !short_castling_rook->getHasMoved() &&
            board.getPiece(row, col + 1) == nullptr &&
            board.getPiece(row, col + 2) == nullptr &&
            !board.isPositionUnderAttack(row, col + 1, !isWhite) &&
            !board.isPositionUnderAttack(row, col + 2, !isWhite))
            {
            int targetRow = row;
            int targetCol = col + 2;
            Move move(row, col, targetRow, targetCol,
                board.getPiece(row, col), nullptr);
            move.isCastling = true;
            moves.push_back(move);
            }

        //long castling check
        if (long_castling_rook != nullptr &&
            long_castling_rook->getType() == PieceType::Rook&&
            long_castling_rook->getIsWhite() == isWhite &&
            !long_castling_rook->getHasMoved() &&
            board.getPiece(row, col - 1) == nullptr &&
            board.getPiece(row, col - 2) == nullptr &&
            board.getPiece(row, col - 3) == nullptr &&
            !board.isPositionUnderAttack(row, col - 1, !isWhite) &&
            !board.isPositionUnderAttack(row, col - 2, !isWhite))
            {
            int targetRow = row;
            int targetCol = col - 2;
            Move move(row, col, targetRow, targetCol,
                board.getPiece(row, col), nullptr);
            move.isCastling = true;
            moves.push_back(move);
            }
    }

    return moves;
}
