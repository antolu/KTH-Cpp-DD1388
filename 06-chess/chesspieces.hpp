#ifndef DD1388_CHESSPIECES_HPP
#define DD1388_CHESSPIECES_HPP

#include "chess.hpp"

class ChessPiece;

class King : public ChessPiece
{
protected:
    int validMove(const int to_x, const int to_y) const;
    char32_t utfRepresentation() const;
    char latin1Representation() const;

    std::vector<ChessMove> generate_moves(const int sign) const;

public:
    King(int x, int y, bool is_white, ChessBoard * board);
    ~King();

    std::vector<ChessMove> capturingMoves() const;
    std::vector<ChessMove> nonCapturingMoves() const;
};



class Bishop : virtual public ChessPiece
{
protected:
    virtual int validMove(const int to_x, const int to_y) const;
    virtual char32_t utfRepresentation() const;
    virtual char latin1Representation() const;

    std::vector<ChessMove> generate_moves(const int sign) const;

public:
    Bishop();
    ~Bishop();
    Bishop(int x, int y, bool is_white, ChessBoard * board);
    virtual std::vector<ChessMove> capturingMoves() const;
    virtual std::vector<ChessMove> nonCapturingMoves() const;
};



class Rook : virtual public ChessPiece
{
protected:
    virtual int validMove(const int to_x, const int to_y) const;
    virtual char32_t utfRepresentation() const;
    virtual char latin1Representation() const;

    std::vector<ChessMove> generate_moves(const int sign) const;

public:
    Rook();
    ~Rook();
    Rook(int x, int y, bool is_white, ChessBoard * board);
    std::vector<ChessMove> capturingMoves() const;
    std::vector<ChessMove> nonCapturingMoves() const;
};



class Queen : public Rook, public Bishop
{
protected:
    int validMove(const int to_x, const int to_y) const;
    char32_t utfRepresentation() const;
    char latin1Representation() const;

    std::vector<ChessMove> generate_moves(const int sign) const;

public:
    Queen(int x, int y, bool is_white, ChessBoard * board);
    ~Queen();
    std::vector<ChessMove> capturingMoves() const;
    std::vector<ChessMove> nonCapturingMoves() const;
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

    std::vector<ChessMove> generate_moves(const int sign) const;

public:
    Knight(int x, int y, bool is_white, ChessBoard * board);
    ~Knight();
    std::vector<ChessMove> capturingMoves() const;
    std::vector<ChessMove> nonCapturingMoves() const;
};



class Pawn : public ChessPiece
{
protected:
    int validMove(const int to_x, const int to_y) const;
    char32_t utfRepresentation() const;
    char latin1Representation() const;

    std::vector<ChessMove> generate_moves(const int sign) const;

public:
    Pawn(int x, int y, bool is_white, ChessBoard * board);
    ~Pawn();
    std::vector<ChessMove> capturingMoves() const;
    std::vector<ChessMove> nonCapturingMoves() const;
};

#endif