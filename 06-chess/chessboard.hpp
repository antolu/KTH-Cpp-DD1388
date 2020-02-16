#ifndef DD1388_CHESSBOARD_HPP
#define DD1388_CHESSBOARD_HPP

#include <iostream>
#include <vector>

#include "../04-matrix/matrix.hpp"
// #include "chesspiece.hpp"
#include "chessmove.hpp"

struct ChessMove;

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

    std::vector<ChessPiece *> captured_white_pieces;
    std::vector<ChessPiece *> captured_black_pieces;

public:
    void move_piece(const ChessMove chessMove);
    ChessPiece * promote_piece(const ChessPiece * piece, const std::string promotion);
    std::vector<ChessMove> capturingMoves(const bool isWhite) const;
    std::vector<ChessMove> nonCapturingMoves(const bool isWhite) const;
    std::vector<ChessPiece *> promotablePieces(const bool is_white) const; 

    /**
     * Returns whether the move `move` forces a capturing move for the opponent
     * 
     * @param move The ChessMove to try
     * @param is_white The color of the querying (current) player
     * @return Whether the move forces a capturing move for the opponent
     */
    bool forces_capturing_move(const ChessMove & move, const bool is_white) const;

    friend ChessBoard &operator>>(std::istream &, ChessBoard &);
    friend std::ostream &operator<<(std::ostream &, ChessBoard &);
    friend std::wostream &operator<<(std::wostream &, ChessBoard &);

    const ChessPiece *at(const int x, const int y) const;
    const bool is_free(const int x, const int y) const;

    const ChessBoard apply_move(const ChessMove move) const;
    // const bool is_white(Chesspiece* chesspiece) const;

    bool isEOG() const;
    bool is_white_win() const;
    bool is_black_win() const;
    bool is_draw() const;
};

#endif