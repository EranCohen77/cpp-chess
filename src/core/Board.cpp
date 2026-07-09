//
// Created by eranc on 6/19/2026.
//

#include "Board.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"

namespace {
    Piece* createPromotionPiece(PieceType type, bool isWhite) {
        switch (type) {
            case PieceType::Queen:
                return new Queen(isWhite);
            case PieceType::Rook:
                return new Rook(isWhite);
            case PieceType::Bishop:
                return new Bishop(isWhite);
            case PieceType::Knight:
                return new Knight(isWhite);
            default:
                return new Queen(isWhite);
        }
    }
}

Board::Board(): grid{} {

}
Board::~Board() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            delete grid[r][c];
        }
    }
}
Piece* Board::getPiece(int row, int col) const {
    return grid[row][col];
}
void Board::setPiece(int row, int col, Piece* piece) {
    grid[row][col] = piece;
}
const Move* Board::getLastMove() const {
    if (!lastMove.has_value()) {
        return nullptr;
    }

    return &lastMove.value();
}
void Board::setLastMove(const Move& move) {
    lastMove = move;
}
void Board::clearLastMove() {
    lastMove.reset();
}
void Board::executeMove(const Move &move) {
    //assume move is valid.
    if (move.isCastling) {
        const bool kingSide = move.endCol > move.startCol;
        Piece* rook = kingSide ? grid[move.startRow][7] : grid[move.startRow][0];
        move.castlingRookHadMoved = rook->getHasMoved();

        grid[move.startRow][move.startCol] = nullptr;
        grid[move.endRow][move.endCol] = move.movedPiece;
        move.movedPiece->setHasMoved(true);

        //move the rook as well based on type of castling:
        if (kingSide) {
            grid[move.startRow][5] = rook;
            grid[move.startRow][7] = nullptr;
        } else {
            grid[move.startRow][3] = rook;
            grid[move.startRow][0] = nullptr;
        }
        rook->setHasMoved(true);
    } else if (move.isEnPassant) {
        int capturesPawnRow = move.startRow;
        int capturesPawnCol = move.endCol;
        grid[move.endRow][move.endCol] = move.movedPiece;
        grid[move.startRow][move.startCol] = nullptr;
        grid[capturesPawnRow][capturesPawnCol] = nullptr;
        move.movedPiece->setHasMoved(true);
    } else if (move.isPromotion) {
        grid[move.endRow][move.endCol] =
            createPromotionPiece(move.promotionType, move.movedPiece->getIsWhite());
        grid[move.startRow][move.startCol] = nullptr;
    } else {
        grid[move.endRow][move.endCol] = move.movedPiece;
        grid[move.startRow][move.startCol] = nullptr;
        move.movedPiece->setHasMoved(true);
    }
    setLastMove(move);
}
void Board::undoMove(const Move &move) {
    //assume move is valid.
    if (move.isCastling) {
        bool kingSide = move.endCol > move.startCol;
        Piece* rook = kingSide ? grid[move.startRow][5] : grid[move.startRow][3];

        grid[move.endRow][move.endCol] = nullptr;
        grid[move.startRow][move.startCol] = move.movedPiece;
        move.movedPiece->setHasMoved(move.movedPieceHadMoved);

        //move the rook as well based on type of castling:
        if (kingSide) {
            grid[move.startRow][7] = rook;
            grid[move.startRow][5] = nullptr;
        } else {
            grid[move.startRow][0] = rook;
            grid[move.startRow][3] = nullptr;
        }
        rook->setHasMoved(move.castlingRookHadMoved);
    } else if (move.isEnPassant) {
        int capturesPawnRow = move.startRow;
        int capturesPawnCol = move.endCol;
        grid[move.startRow][move.startCol] = move.movedPiece;
        grid[move.endRow][move.endCol] = nullptr;
        grid[capturesPawnRow][capturesPawnCol] = move.capturedPiece;
        move.movedPiece->setHasMoved(move.movedPieceHadMoved);
    } else if (move.isPromotion) {
        delete grid[move.endRow][move.endCol];
        grid[move.startRow][move.startCol] = move.movedPiece;
        grid[move.endRow][move.endCol] = move.capturedPiece;
        move.movedPiece->setHasMoved(move.movedPieceHadMoved);
    } else {
        grid[move.startRow][move.startCol] = move.movedPiece;
        grid[move.endRow][move.endCol] = move.capturedPiece;
        move.movedPiece->setHasMoved(move.movedPieceHadMoved);
    }
    clearLastMove();
}
bool Board::isPositionUnderAttack(int row, int col, bool attackerIsWhite) const {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = grid[r][c];
            if (p == nullptr) continue;
            if (p->getIsWhite() != attackerIsWhite) continue;

            std::vector<Move> moves = p->getValidMoves(*this, r, c);
            for (const Move& move : moves) {
                if (move.endRow == row && move.endCol == col) {
                    return true;
                }
            }
        }
    }

    return false;
}
bool Board::isInCheck(bool attackerIsWhite) const {
    // We want the king of the side being attacked.
    const char symbol = attackerIsWhite? 'K' : 'k';
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = grid[r][c];
            if (p == nullptr) continue;
            if (p->getSymbol() == symbol)
                return isPositionUnderAttack(r, c, attackerIsWhite);
        }
    }
    return false;
}
bool Board::isCheckMate(bool attackerIsWhite) {
    if (!isInCheck(attackerIsWhite)) return false;
    bool defenderIsWhite = !attackerIsWhite;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = grid[r][c];
            if (p == nullptr) continue;
            if (p->getIsWhite() != defenderIsWhite) continue;

            std::vector<Move> moves = p->getValidMoves(*this, r, c);
            for (const Move& move : moves) {
                executeMove(move);
                if (!isInCheck(attackerIsWhite)) {
                    undoMove(move);
                    return false;
                }
                undoMove(move);
            }
        }
    }
    return true;
}
