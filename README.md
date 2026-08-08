```mermaid
classDiagram
    direction LR

    %% Core Controller
    class Game {
        -Board board
        -bool isWhiteTurn
        -vector~Move~ moveHistory
        -vector~Piece*~ removedPieces
        -bool handlePlayerInput()
        -void switchTurn()
        -void drawBoard(const string& message) const
        -bool hasLegalMove(bool whiteSide)
        +Game()
        +~Game()
        +void initializeNewGame()
        +void run()
    }

    %% Board Management
    class Board {
        -Piece* grid[8][8]
        -optional~Move~ lastMove
        +Board()
        +~Board()
        +Piece* getPiece(int row, int col) const
        +void setPiece(int row, int col, Piece* piece)
        +const Move* getLastMove() const
        +void setLastMove(const Move& move)
        +void clearLastMove()
        +void executeMove(const Move& move)
        +void undoMove(const Move& move)
        +bool isPositionUnderAttack(int row, int col, bool attackerIsWhite) const
        +bool isInCheck(bool attackerIsWhite) const
        +bool isCheckMate(bool attackerIsWhite)
    }

    %% Complex Move Descriptor (The "Receipt")
    class Move {
        +int startRow
        +int startCol
        +int endRow
        +int endCol
        +Piece* movedPiece
        +Piece* capturedPiece
        +bool movedPieceHadMoved
        +bool castlingRookHadMoved
        +bool isCastling
        +bool isEnPassant
        +bool isPromotion
        +PieceType promotionType
        +Move(int sRow, int sCol, int eRow, int eCol, Piece* moved, Piece* captured, PieceType promotionType)
        +string toAlgebricNotation() const
    }

class PieceType {
<<enumeration>>
King
Queen
Rook
Bishop
Knight
Pawn
}

class Piece {
#bool isWhite
#bool hasMoved
+Piece(bool isWhite)
+virtual ~Piece()
+bool getIsWhite() const
+bool getHasMoved() const
+void setHasMoved(bool moved)
+virtual PieceType getType() const = 0
+virtual vector~Move~ getValidMoves(const Board& board, int row, int col) const = 0
+virtual char getSymbol() const = 0
}

class Pawn {
+Pawn(bool isWhite)
-void addPromotionMoves(vector~Move~& moves, int startRow, int startCol, int endRow, int endCol, Piece* movedPiece, Piece* capturedPiece) const
+getType() const PieceType
+getValidMoves(const Board& board, int row, int col) const vector~Move~
+getSymbol() const char
}

class Knight {
+Knight(bool isWhite)
+getType() const PieceType
+getValidMoves(const Board& board, int row, int col) const vector~Move~
+getSymbol() const char
}

class Bishop {
+Bishop(bool isWhite)
+getType() const PieceType
+getValidMoves(const Board& board, int row, int col) const vector~Move~
+getSymbol() const char
}

class Rook {
+Rook(bool isWhite)
+getType() const PieceType
+getValidMoves(const Board& board, int row, int col) const vector~Move~
+getSymbol() const char
}

class Queen {
+Queen(bool isWhite)
+getType() const PieceType
+getValidMoves(const Board& board, int row, int col) const vector~Move~
+getSymbol() const char
}

class King {
+King(bool isWhite)
+getType() const PieceType
+getValidMoves(const Board& board, int row, int col) const vector~Move~
+getSymbol() const char
}

Piece --> PieceType : returns
Move --> PieceType : promotion choice
Move --> Piece : references moved/captured pieces
Piece <|-- Pawn
Piece <|-- Knight
Piece <|-- Bishop
Piece <|-- Rook
Piece <|-- Queen
Piece <|-- King

    %% Relationships and Cardinalities
    Game "1" *-- "1" Board : contains
    Game "1" *-- "many" Move : tracks history
    Board "1" o-- "0..32" Piece : dynamically stores
    
```
