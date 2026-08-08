//
// Created by eranc on 6/19/2026.
//
#ifndef CPP_CHESS_GAME_H
#define CPP_CHESS_GAME_H
#include <string>

#include "Board.h"


class Game {
private:
    Board board;
    bool isWhiteTurn;
    std::vector<Move> moveHistory;
    std::vector<Piece*> removedPieces;
    bool handlePlayerInput();
    void switchTurn();
    void drawBoard(const std::string& message = "") const;
    bool hasLegalMove(bool whiteSide);
public:
    Game();
    ~Game();
    void initializeNewGame();
    void run();
};


#endif //CPP_CHESS_GAME_H
