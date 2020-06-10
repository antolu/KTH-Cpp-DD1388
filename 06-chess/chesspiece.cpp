#include <iostream>
#include <codecvt>

#include "chessmove.hpp"
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

//int ChessPiece::validMove(const int to_x, const int to_y) const
//{
//    return 0;
//}

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

bool ChessPiece::capturingMove(const int to_x, const int to_y)
{
    return validMove(to_x, to_y) == 2;
}

bool ChessPiece::nonCapturingMove(const int to_x, const int to_y)
{
    return validMove(to_x, to_y) == 1;
}

bool ChessPiece::promotionMove(const int to_x, const int to_y) const {
    return false;
}

std::vector<ChessMove> ChessPiece::capturingMoves()
{
    std::vector<ChessMove> ret;
    return ret;
}

std::vector<ChessMove> ChessPiece::nonCapturingMoves()
{
    std::vector<ChessMove> ret;
    return ret;
}

std::vector<ChessMove> ChessPiece::promotionMoves() {
    return std::vector<ChessMove>();
}

std::ostream & operator<<(std::ostream& ostream, const ChessPiece * chesspiece) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv32;
    return ostream << conv32.to_bytes(chesspiece->utfRepresentation());
}

std::wostream & operator<<(std::wostream& ostream, const ChessPiece * chesspiece) {
    return ostream << chesspiece->utfRepresentation();
}

void ChessPiece::set_board(ChessBoard *board) {
    this->board = board;
}

//bool operator==(const ChessMove & lhs, const ChessMove & rhs) {
//    if (lhs.from_x != rhs.from_x || lhs.from_y != rhs.from_y || lhs.to_x != rhs.to_x || lhs.to_y != rhs.to_y )
//        return false;
//
//    if (lhs.piece->isWhite != rhs.piece->isWhite)
//        return false;
//
//    if (!std::is_same<decltype(lhs.piece), decltype(rhs.piece)>::value)
//        return false;
//
//    return true;
//}