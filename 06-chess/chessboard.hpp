#ifndef DD1388_CHESSBOARD_HPP
#define DD1388_CHESSBOARD_HPP

#include <iostream>
#include <vector>

#include "../04-matrix/matrix.hpp"

struct ChessMove;
class ChessPiece;

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

    void copy(const ChessBoard& other);

public:
    void move_piece(const ChessMove & chessMove);
    ChessPiece * promote_piece(const ChessMove & chessMove);
    std::vector<ChessMove> capturingMoves(const bool isWhite) const;
    std::vector<ChessMove> nonCapturingMoves(const bool isWhite) const;
    std::vector<ChessMove> promotablePieces(const bool is_white) const;

    ChessBoard& operator=(const ChessBoard& other);

    friend ChessBoard &operator>>(std::istream &, ChessBoard &);
    friend std::ostream &operator<<(std::ostream &, ChessBoard &);
    friend std::wostream &operator<<(std::wostream &, ChessBoard &);

    const ChessPiece *at(const int x, const int y) const;
    const bool is_free(const int x, const int y) const;

    ChessBoard * apply_move(const ChessMove move) const;
    // const bool is_white(Chesspiece* chesspiece) const;

    bool isEOG() const;
    bool is_white_win() const;
    bool is_black_win() const;
    bool is_draw() const;
};

#endif