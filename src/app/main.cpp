//
// Created by eranc on 6/19/2026.
//
#include <iostream>

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Move.h"
#include "Pawn.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
using std::cout, std::endl;
int main() {
    King king(false);
    Queen queen(false);
    Rook rook(true);
    Bishop bishop(false);
    Knight knight(false);
    Pawn pawn(false);
    cout << king.getSymbol() << endl;
    cout << queen.getSymbol() << endl;
    cout << rook.getSymbol() << endl;
    cout << bishop.getSymbol() << endl;
    cout << knight.getSymbol() << endl;
    cout << pawn.getSymbol() << endl;
    return 0;
}
