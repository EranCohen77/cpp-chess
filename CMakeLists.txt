cmake_minimum_required(VERSION 4.0)
project(cpp_chess)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_chess
        src/app/main.cpp
        src/core/Board.cpp
        src/core/Board.h
        src/core/Move.cpp
        src/core/Move.h
        src/core/Piece.cpp
        src/core/Piece.h
        src/core/PieceType.h
        src/game/Game.cpp
        src/game/Game.h
        src/pieces/Bishop.cpp
        src/pieces/Bishop.h
        src/pieces/King.cpp
        src/pieces/King.h
        src/pieces/Knight.cpp
        src/pieces/Knight.h
        src/pieces/Pawn.cpp
        src/pieces/Pawn.h
        src/pieces/Queen.cpp
        src/pieces/Queen.h
        src/pieces/Rook.cpp
        src/pieces/Rook.h)

target_include_directories(cpp_chess PRIVATE
        src/core
        src/game
        src/pieces)
