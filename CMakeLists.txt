cmake_minimum_required(VERSION 4.0)
project(cpp_chess)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(cpp_chess
        Move.cpp
        Move.h
        Game.cpp
        Game.h
        Board.cpp
        Board.h
        Piece.h
        Pawn.cpp
        Pawn.h
        Bishop.cpp
        Bishop.h
        Knight.cpp
        Knight.h
        Rook.cpp
        Rook.h
        Queen.cpp
        Queen.h
        King.cpp
        King.h
        PieceType.h
        Piece.cpp
        main.cpp)
