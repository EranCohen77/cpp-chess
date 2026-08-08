//
// Created by eranc on 6/19/2026.
//

#include "Pawn.h"

#include <cstdlib>

#include "Board.h"
Pawn::Pawn(bool isWhite) : Piece(isWhite) {}

PieceType Pawn::getType() const{
    return PieceType::Pawn;
}
char Pawn::getSymbol() const {
    return isWhite? 'p' : 'P';
}
void Pawn::addPromotionMoves(
    std::vector<Move>& moves,
    int startRow,
    int startCol,
    int endRow,
    int endCol,
    Piece* movedPiece,
    Piece* capturedPiece
) const {
    const PieceType promotionTypes[4] = {
        PieceType::Queen,
        PieceType::Rook,
        PieceType::Bishop,
        PieceType::Knight
    };

    for (PieceType promotionType : promotionTypes) {
        Move move(startRow, startCol, endRow, endCol, movedPiece, capturedPiece);
        move.isPromotion = true;
        move.promotionType = promotionType;
        moves.push_back(move);
    }
}
std::vector<Move> Pawn::getValidMoves(const Board &board, int row, int col) const {
    std::vector<Move> moves;
    int direction = isWhite ? -1 : 1;
    int targetRow = row + direction;
    int targetCol = col;
    bool blocked = false;
    bool isPromotionRow = (isWhite && row == 1) || (!isWhite && row == 6);
    Piece* movedPiece = board.getPiece(row, col);

    //check normal advancement moves
    if (board.getPiece(targetRow, col) != nullptr)
        blocked = true;
    else {
        if (isPromotionRow) {
            addPromotionMoves(moves, row, col, targetRow, targetCol, movedPiece, nullptr);
        } else {
            moves.emplace_back(row, col, targetRow, targetCol, movedPiece, nullptr);
        }
    }
    if (!blocked && !isPromotionRow && !hasMoved
        && board.getPiece(targetRow + direction, col) == nullptr) {
        moves.emplace_back(row, col, targetRow + direction, targetCol,
            movedPiece, nullptr);
    }

    //check normal capture
    //right
    if (col < 7) {
        Piece* right_captured = board.getPiece(targetRow, col + 1);
        if (right_captured != nullptr && right_captured->getIsWhite() != isWhite) {
            targetCol = col + 1;
            if (isPromotionRow) {
                addPromotionMoves(moves, row, col, targetRow, targetCol,
                    movedPiece, right_captured);
            } else {
                moves.emplace_back(row, col, targetRow, targetCol,
                    movedPiece, right_captured);
            }
        }
    }

    //left
    if (col > 0) {
        Piece* left_captured = board.getPiece(targetRow, col - 1);
        if (left_captured != nullptr && left_captured->getIsWhite() != isWhite) {
            targetCol = col - 1;
            if (isPromotionRow) {
                addPromotionMoves(moves, row, col, targetRow, targetCol,
                    movedPiece, left_captured);
            } else {
                moves.emplace_back(row, col, targetRow, targetCol,
                    movedPiece, left_captured);
            }
        }
    }

    //check en passant
    if ((isWhite && row == 3) || (!isWhite && row == 4)) {
        const Move* lastMove = board.getLastMove();
        if (lastMove != nullptr
            && lastMove->endRow == row
            && lastMove->movedPiece != nullptr
            && lastMove->movedPiece->getType() == PieceType::Pawn
            && std::abs(lastMove->endRow - lastMove->startRow) == 2
            && lastMove->movedPiece->getIsWhite() != isWhite)
        {
            //check right
            if (lastMove->endCol == col + 1) {
                targetCol = col + 1;
                Move move(row, col, targetRow, targetCol,
                    movedPiece, lastMove->movedPiece);
                move.isEnPassant = true;
                moves.push_back(move);
            }
            //check left
            if (lastMove->endCol == col - 1) {
                targetCol = col - 1;
                Move move(row, col, targetRow, targetCol,
                    movedPiece, lastMove->movedPiece);
                move.isEnPassant = true;
                moves.push_back(move);
            }
        }
    }

    return moves;
}
