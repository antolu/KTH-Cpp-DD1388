#ifndef DD1388_CHESSPIECES_HPP
#define DD1388_CHESSPIECES_HPP

#include <vector>

#include "chessboard.hpp"
#include "chesspiece.hpp"
#include "chessmove.hpp"

class ChessBoard;
class ChessPiece;
struct ChessMove;

class King : public ChessPiece
{
protected:
    int validMove(const int to_x, const int to_y) const;
    char32_t utfRepresentation() const;
    char latin1Representation() const;

    std::vector<ChessMove> generate_moves(const int sign);

public:
    King(int x, int y, bool is_white, ChessBoard * board);
    King(const ChessPiece & piece);
    ~King();

    std::vector<ChessMove> capturingMoves();
    std::vector<ChessMove> nonCapturingMoves();
};



class Bishop : virtual public ChessPiece
{
protected:
    virtual int validMove(const int to_x, const int to_y) const;
    virtual char32_t utfRepresentation() const;
    virtual char latin1Representation() const;

    std::vector<ChessMove> generate_moves(const int sign);

public:
    Bishop();
    Bishop(const ChessPiece & piece);
    ~Bishop();
    Bishop(int x, int y, bool is_white, ChessBoard * board);
    virtual std::vector<ChessMove> capturingMoves();
    virtual std::vector<ChessMove> nonCapturingMoves();
};



class Rook : virtual public ChessPiece
{
protected:
    virtual int validMove(const int to_x, const int to_y) const;
    virtual char32_t utfRepresentation() const;
    virtual char latin1Representation() const;

    std::vector<ChessMove> generate_moves(const int sign);

public:
    Rook();
    Rook(const ChessPiece & piece);
    ~Rook();
    Rook(int x, int y, bool is_white, ChessBoard * board);
    std::vector<ChessMove> capturingMoves();
    std::vector<ChessMove> nonCapturingMoves();
};



class Queen : public Rook, public Bishop
{
protected:
    int validMove(const int to_x, const int to_y) const;
    char32_t utfRepresentation() const;
    char latin1Representation() const;

    std::vector<ChessMove> generate_moves(const int sign);

public:
    Queen(int x, int y, bool is_white, ChessBoard * board);
    Queen(const ChessPiece & piece);
    ~Queen();
    std::vector<ChessMove> capturingMoves();
    std::vector<ChessMove> nonCapturingMoves();
};



struct MoveOffset {
    int x;
    int y;
};



class Knight : public ChessPiece
{
    MoveOffset move_candidates[8] = {MoveOffset({1, 2}), MoveOffset({1, -2}), MoveOffset({-1, -2}), MoveOffset({-1, 2}), MoveOffset({2, 1}), MoveOffset({2, -1}), MoveOffset({-2, -1}), MoveOffset({-2, 1})};
protected:
    int validMove(const int to_x, const int to_y) const;
    char32_t utfRepresentation() const;
    char latin1Representation() const;

    std::vector<ChessMove> generate_moves(const int sign);

public:
    Knight(int x, int y, bool is_white, ChessBoard * board);
    Knight(const ChessPiece & piece);
    ~Knight();
    std::vector<ChessMove> capturingMoves();
    std::vector<ChessMove> nonCapturingMoves();
};



class Pawn : public ChessPiece
{
protected:
    int validMove(const int to_x, const int to_y) const;
    char32_t utfRepresentation() const;
    char latin1Representation() const;

    std::vector<ChessMove> generate_moves(const int sign);

public:
    Pawn(int x, int y, bool is_white, ChessBoard * board);
    Pawn(const ChessPiece & piece);
    ~Pawn();
    std::vector<ChessMove> capturingMoves();
    std::vector<ChessMove> nonCapturingMoves();
};

#endif