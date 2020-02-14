#include <iostream>
#include <codecvt>

#include "chesspiece.hpp"


ChessPiece::ChessPiece(){};

ChessPiece::ChessPiece(const ChessPiece & piece) {
    isWhite = piece.isWhite;
    x = piece.x;
    y = piece.y;
    board = piece.board;
}

ChessPiece::~ChessPiece(){};

ChessPiece::ChessPiece(int x, int y, bool is_white, ChessBoard *board)
{
    this->x = x;
    this->y = y;
    this->isWhite = is_white;
    this->board = board;
}

int ChessPiece::validMove(const int to_x, const int to_y) const
{
    return 0;
}

char32_t ChessPiece::utfRepresentation() const
{
    return ' ';
}

char ChessPiece::latin1Representation() const
{
    return ' ';
}

bool ChessPiece::out_of_bounds(const int to_x, const int to_y) const
{
    return to_x >= 8 || to_y >= 8 || to_x < 0 || to_y < 0;
}

bool ChessPiece::same_color(const ChessPiece *other) const
{
    // if (other == nullptr) return false;
    return isWhite == other->isWhite;
}

std::vector<ChessMove> ChessPiece::generate_moves(const int sign) const
{
    std::vector<ChessMove> ret;
    return ret;
}

bool ChessPiece::capturingMove(const int to_x, const int to_y)
{
    return validMove(to_x, to_y) == 2;
}

bool ChessPiece::nonCapturingMove(const int to_x, const int to_y)
{
    return validMove(to_x, to_y) == 1;
}

std::vector<ChessMove> ChessPiece::capturingMoves() const
{
    std::vector<ChessMove> ret;
    return ret;
}

std::vector<ChessMove> ChessPiece::nonCapturingMoves() const
{
    std::vector<ChessMove> ret;
    return ret;
}

std::ostream & operator<<(std::ostream& ostream, ChessPiece * chesspiece) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv32;
    return ostream << conv32.to_bytes(chesspiece->utfRepresentation());
}

std::wostream & operator<<(std::wostream& ostream, ChessPiece * chesspiece) {
    return ostream << chesspiece->utfRepresentation();
}