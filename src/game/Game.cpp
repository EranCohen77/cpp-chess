//
// Created by eranc on 6/19/2026.
//

#include "Game.h"

#include <algorithm>
#include <cctype>
#include <iostream>

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

namespace {
    char displaySymbol(const Piece* piece) {
        char symbol = piece->getSymbol();
        return piece->getIsWhite()
            ? static_cast<char>(std::toupper(static_cast<unsigned char>(symbol)))
            : static_cast<char>(std::tolower(static_cast<unsigned char>(symbol)));
    }

    PieceType promotionType(char value) {
        switch (static_cast<char>(std::tolower(static_cast<unsigned char>(value)))) {
            case 'r': return PieceType::Rook;
            case 'b': return PieceType::Bishop;
            case 'n': return PieceType::Knight;
            default: return PieceType::Queen;
        }
    }

}

Game::Game(): board(), isWhiteTurn(true), moveHistory{}, removedPieces{} {}
Game::~Game() {
    for (Piece* piece : removedPieces) {
        delete piece;
    }
}
void Game::initializeNewGame() {
    board.setPiece(0, 0, new Rook(false));
    board.setPiece(0, 1, new Knight(false));
    board.setPiece(0, 2, new Bishop(false));
    board.setPiece(0, 3, new Queen(false));
    board.setPiece(0, 4, new King(false));
    board.setPiece(0, 5, new Bishop(false));
    board.setPiece(0, 6, new Knight(false));
    board.setPiece(0, 7, new Rook(false));

    board.setPiece(7, 0, new Rook(true));
    board.setPiece(7, 1, new Knight(true));
    board.setPiece(7, 2, new Bishop(true));
    board.setPiece(7, 3, new Queen(true));
    board.setPiece(7, 4, new King(true));
    board.setPiece(7, 5, new Bishop(true));
    board.setPiece(7, 6, new Knight(true));
    board.setPiece(7, 7, new Rook(true));

    for (int col = 0; col < 8; ++col) {
        board.setPiece(1, col, new Pawn(false));
        board.setPiece(6, col, new Pawn(true));
    }
    isWhiteTurn = true;
    board.clearLastMove();
}
void Game::run() {
    initializeNewGame();
    while (true) {
        const bool opponentIsWhite = !isWhiteTurn;
        if (!hasLegalMove(isWhiteTurn)) {
            drawBoard();
            if (board.isInCheck(opponentIsWhite)) {
                std::cout << "Checkmate! " << (opponentIsWhite ? "White" : "Black")
                          << " wins.\n";
            } else {
                std::cout << "Stalemate.\n";
            }
            return;
        }
        std::string message;
        if (board.isInCheck(opponentIsWhite)) message = "Check!";
        else if (moveHistory.empty()) {
            message = "Enter algebraic moves such as e4, Nf3, exd5, O-O, or e8=Q.";
        }
        drawBoard(message);
        if (!handlePlayerInput()) return;
    }
}

bool Game::handlePlayerInput() {
    while (true) {
        std::cout << (isWhiteTurn ? "White" : "Black") << " to move: " << std::flush;
        std::string line;
        if (!std::getline(std::cin, line)) return false;
        std::string input;
        for (char character : line) {
            if (!std::isspace(static_cast<unsigned char>(character))) input += character;
        }
        std::string command = input;
        std::transform(command.begin(), command.end(), command.begin(), [](unsigned char value) {
            return static_cast<char>(std::tolower(value));
        });
        if (command == "quit" || command == "exit" || command == "q") return false;

        for (char& value : input) if (value == '0') value = 'O';
        while (!input.empty() && (input.back() == '+' || input.back() == '#')) input.pop_back();

        bool castleKingSide = false;
        bool castleQueenSide = false;
        if (input == "O-O" || input == "o-o") castleKingSide = true;
        else if (input == "O-O-O" || input == "o-o-o") castleQueenSide = true;

        PieceType requestedType = PieceType::Pawn;
        PieceType requestedPromotion = PieceType::Queen;
        bool promotionRequested = false;
        bool captureRequested = false;
        int endRow = -1;
        int endCol = -1;
        char sourceFile = '\0';
        char sourceRank = '\0';
        bool validNotation = castleKingSide || castleQueenSide;

        if (!validNotation) {
            const std::size_t equals = input.find('=');
            if (equals != std::string::npos && equals + 2 == input.size()) {
                const char promoted = static_cast<char>(std::tolower(
                    static_cast<unsigned char>(input.back())));
                if (promoted == 'q' || promoted == 'r' || promoted == 'b' || promoted == 'n') {
                    promotionRequested = true;
                    requestedPromotion = promotionType(promoted);
                    input.erase(equals);
                }
            }

            if (input.size() >= 2) {
                const char file = static_cast<char>(std::tolower(
                    static_cast<unsigned char>(input[input.size() - 2])));
                const char rank = input.back();
                if (file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8') {
                    endCol = file - 'a';
                    endRow = '8' - rank;
                    std::string prefix = input.substr(0, input.size() - 2);
                    if (!prefix.empty() && std::string("KQRBN").find(prefix[0]) != std::string::npos) {
                        switch (prefix[0]) {
                            case 'K': requestedType = PieceType::King; break;
                            case 'Q': requestedType = PieceType::Queen; break;
                            case 'R': requestedType = PieceType::Rook; break;
                            case 'B': requestedType = PieceType::Bishop; break;
                            case 'N': requestedType = PieceType::Knight; break;
                        }
                        prefix.erase(0, 1);
                    }
                    const std::size_t capture = prefix.find('x');
                    if (capture != std::string::npos) {
                        captureRequested = true;
                        prefix.erase(capture, 1);
                    }
                    validNotation = prefix.size() <= 2;
                    for (char hint : prefix) {
                        const char lower = static_cast<char>(std::tolower(
                            static_cast<unsigned char>(hint)));
                        if (lower >= 'a' && lower <= 'h' && sourceFile == '\0') sourceFile = lower;
                        else if (hint >= '1' && hint <= '8' && sourceRank == '\0') sourceRank = hint;
                        else validNotation = false;
                    }
                    if (requestedType == PieceType::Pawn) {
                        if (captureRequested && sourceFile == '\0') validNotation = false;
                        if (!captureRequested && (sourceFile != '\0' || sourceRank != '\0')) validNotation = false;
                    }
                }
            }
        }

        if (!validNotation) {
            drawBoard("Invalid algebraic notation. Examples: e4, Nf3, exd5, O-O, e8=Q.");
            continue;
        }

        std::vector<Move> matches;
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                Piece* piece = board.getPiece(row, col);
                if (piece == nullptr || piece->getIsWhite() != isWhiteTurn) continue;
                for (const Move& move : piece->getValidMoves(board, row, col)) {
                    const bool isCapture = move.capturedPiece != nullptr || move.isEnPassant;
                    const bool notationMatches = castleKingSide
                        ? move.isCastling && move.endCol > move.startCol
                        : castleQueenSide
                            ? move.isCastling && move.endCol < move.startCol
                            : piece->getType() == requestedType && move.endRow == endRow &&
                                move.endCol == endCol && isCapture == captureRequested &&
                                move.isPromotion == promotionRequested &&
                                (!move.isPromotion || move.promotionType == requestedPromotion) &&
                                (sourceFile == '\0' || move.startCol == sourceFile - 'a') &&
                                (sourceRank == '\0' || move.startRow == '8' - sourceRank);
                    if (!notationMatches) continue;

                    const bool hadLastMove = board.getLastMove() != nullptr;
                    const Move previousLastMove = hadLastMove
                        ? *board.getLastMove() : Move(0, 0, 0, 0, nullptr, nullptr);
                    board.executeMove(move);
                    const bool legal = !board.isInCheck(!isWhiteTurn);
                    board.undoMove(move);
                    if (hadLastMove) board.setLastMove(previousLastMove);
                    if (legal) matches.push_back(move);
                }
            }
        }

        if (matches.empty()) {
            drawBoard("No legal move matches that algebraic notation.");
            continue;
        }
        if (matches.size() > 1) {
            drawBoard("That move is ambiguous; include the source file or rank (for example, Nbd2). ");
            continue;
        }
        const Move chosen = matches.front();

        const Move previousLastMove = board.getLastMove() != nullptr
            ? *board.getLastMove() : Move(0, 0, 0, 0, nullptr, nullptr);
        const bool hadLastMove = board.getLastMove() != nullptr;
        board.executeMove(chosen);
        if (board.isInCheck(!isWhiteTurn)) {
            board.undoMove(chosen);
            if (hadLastMove) board.setLastMove(previousLastMove);
            drawBoard("Illegal move: your king would be in check.");
            continue;
        }

        if (chosen.capturedPiece != nullptr) removedPieces.push_back(chosen.capturedPiece);
        if (chosen.isPromotion) removedPieces.push_back(chosen.movedPiece);
        moveHistory.push_back(chosen);
        switchTurn();
        return true;
    }
}

void Game::switchTurn() {
    isWhiteTurn = !isWhiteTurn;
}

void Game::drawBoard(const std::string& message) const {
    // Clear both the visible screen and scrollback, then redraw from the top-left.
    std::cout << "\x1b[2J\x1b[3J\x1b[H" << std::flush;
    std::cout << "    a   b   c   d   e   f   g   h\n";
    std::cout << "  +---+---+---+---+---+---+---+---+\n";
    for (int row = 0; row < 8; ++row) {
        std::cout << 8 - row << " |";
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board.getPiece(row, col);
            std::cout << ' ' << (piece == nullptr ? ' ' : displaySymbol(piece)) << " |";
        }
        std::cout << ' ' << 8 - row << "\n";
        std::cout << "  +---+---+---+---+---+---+---+---+\n";
    }
    std::cout << "    a   b   c   d   e   f   g   h\n";
    if (!message.empty()) std::cout << message << '\n';
    std::cout << std::flush;
}

bool Game::hasLegalMove(bool whiteSide) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board.getPiece(row, col);
            if (piece == nullptr || piece->getIsWhite() != whiteSide) continue;
            const std::vector<Move> moves = piece->getValidMoves(board, row, col);
            for (const Move& move : moves) {
                const bool hadLastMove = board.getLastMove() != nullptr;
                const Move previousLastMove = hadLastMove
                    ? *board.getLastMove() : Move(0, 0, 0, 0, nullptr, nullptr);
                board.executeMove(move);
                const bool legal = !board.isInCheck(!whiteSide);
                board.undoMove(move);
                if (hadLastMove) board.setLastMove(previousLastMove);
                if (legal) return true;
            }
        }
    }
    return false;
}
