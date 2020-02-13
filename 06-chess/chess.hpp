#ifndef DD1388_CHESSPIECE_HPP
#define DD1388_CHESSPIECE_HPP

#include "../04-matrix/matrix.hpp"
#include "chessmove.hpp"
#include <vector>


struct ChessMove;

#include <unordered_set>

class ChessBoard
{
    // add additional members or functions of your choice
public:
    ChessBoard();
    ~ChessBoard();
    ChessBoard(const ChessBoard & board);

private:
    Matrix<ChessPiece *> state = Matrix<ChessPiece *>(8); // Matris from lab 4  Matrix

    std::vector<ChessPiece *> white_pieces;
    std::vector<ChessPiece *> black_pieces;

public:
    void move_piece(const ChessMove chessMove);
    std::vector<ChessMove> capturingMoves(bool isWhite) const;
    std::vector<ChessMove> nonCapturingMoves(bool isWhite) const;

    friend ChessBoard &operator>>(std::istream &, ChessBoard &);
    friend std::ostream &operator<<(std::ostream &, ChessBoard &);
    friend std::wostream &operator<<(std::wostream &, ChessBoard &);

    const ChessPiece *at(const int x, const int y) const;
    const bool is_free(const int x, const int y) const;

    const ChessBoard apply_move(const ChessMove move) const;
    // const bool is_white(Chesspiece* chesspiece) const;
};

class ChessPiece
{
    friend void ChessBoard::move_piece(ChessMove p);

public:
    ChessPiece();
    virtual ~ChessPiece();

protected:
    int x, y;
    bool isWhite;
    ChessBoard *board;
    bool captured = false;

    ChessPiece(int x, int y, bool is_white, ChessBoard *board);
    /**
         * Returns 0 if target square is unreachable.
         * Returns 1 if target square is reachable and empty.
         * Returns 2 if move captures a piece.
         */
    virtual int validMove(const int to_x, const int to_y) const;
    virtual char32_t utfRepresentation() const;
    virtual char latin1Representation() const;

    bool out_of_bounds(const int to_x, const int to_y) const;

    bool same_color(const ChessPiece * other) const;

    virtual std::vector<ChessMove> generate_moves(const int sign) const;

public:
    /**
         * Checks if this move is valid for this piece and captures
         * a piece of the opposite color.
         */
    bool capturingMove(const int to_x, const int to_y);
    /**
         * Checks if this move is valid but does not capture a piece.
         */
    bool nonCapturingMove(const int to_x, const int to_y);
    virtual std::vector<ChessMove> capturingMoves() const;
    virtual std::vector<ChessMove> nonCapturingMoves() const;

    /**
		* For testing multiple inheritance
		*/
    int unnecessaryInt;

    friend std::ostream& operator<<(std::ostream & ostream, ChessPiece * chesspiece);
    friend std::wostream& operator<<(std::wostream & ostream, ChessPiece * chesspiece);
};

#endif