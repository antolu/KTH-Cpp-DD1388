#ifndef DD1388_CHESSMOVE_HPP
#define DD1388_CHESSMOVE_HPP

// #include "chess.hpp"
// #include "chesspiece.hpp"

class ChessPiece;

struct ChessMove {
    int from_x;
    int from_y;
    int to_x;
    int to_y;

    ChessPiece* piece; // you can change the position of the chess piece with this pointer.

    char promotion = 0;

    ChessMove(int from_x, int from_y, int to_x, int to_y, ChessPiece * piece){
        this->from_x = from_x;
        this->from_y = from_y;
        this->to_x = to_x;
        this->to_y = to_y;
        this->piece = piece;
    }
};

bool operator==(const ChessMove & lhs, const ChessMove & rhs) {
    return lhs.from_x == rhs.from_x && lhs.from_y == rhs.from_y && lhs.to_x == rhs.to_x && lhs.to_y == rhs.to_y && lhs.piece == rhs.piece;
}

#endif