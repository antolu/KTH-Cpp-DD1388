#ifndef DD1388_CHESSPIECE_HPP
#define DD1388_CHESSPIECE_HPP

#include <iostream>
#include <vector>
#include "chessmove.hpp"
#include "chessboard.hpp"

struct ChessMove;

class ChessPiece
{
    friend void ChessBoard::move_piece(const ChessMove & p);
    friend ChessPiece * ChessBoard::promote_piece(const ChessMove& move);
    friend bool operator==(const ChessMove &, const ChessMove &);

public:
    ChessPiece();
    ChessPiece(const ChessPiece & piece);
    virtual ~ChessPiece();

protected:
    int x, y;
    bool isWhite;
    ChessBoard *board;
    
    ChessPiece(int x, int y, bool is_white, ChessBoard *board);
    /**
         * Returns 0 if target square is unreachable.
         * Returns 1 if target square is reachable and empty.
         * Returns 2 if move captures a piece.
         * Returns 3 if the move is a promotional move (pawns only)
         */
    virtual int validMove(const int to_x, const int to_y) const = 0;
    virtual char32_t utfRepresentation() const;
    virtual char latin1Representation() const;

    bool out_of_bounds(const int to_x, const int to_y) const;

    bool same_color(const ChessPiece * other) const;
    virtual bool promotionMove(const int to_x, const int to_y) const;
    virtual std::vector<ChessMove> promotionMoves();
    virtual ChessPiece* clone() = 0;
    void set_board(ChessBoard * board);

    virtual std::vector<ChessMove> generate_moves(const int sign) = 0;

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
    virtual std::vector<ChessMove> capturingMoves();
    virtual std::vector<ChessMove> nonCapturingMoves();

    /**
		* For testing multiple inheritance
		*/
    int unnecessaryInt;

    friend std::ostream& operator<<(std::ostream & ostream, const ChessPiece * chesspiece);
    friend std::wostream& operator<<(std::wostream & ostream, const ChessPiece * chesspiece);
};

#endif