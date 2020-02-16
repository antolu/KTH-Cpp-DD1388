#include <iostream>
#include <algorithm>

#include "chesspiece.hpp"
#include "chesspieces.hpp"

ChessBoard::ChessBoard() {
    std::stringstream s;
    s << "rnbqkbnr" << std::endl;
    s << "pppppppp" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "PPPPPPPP" << std::endl;
    s << "RNBQKBNR";
    s >> *this;
};

ChessBoard::~ChessBoard()
{
    for (auto piece : white_pieces)
        delete piece;

    for (auto piece : black_pieces)
        delete piece;

    for (auto piece : captured_white_pieces)
        delete piece;
    
    for (auto piece : captured_black_pieces)
        delete piece;
}

ChessBoard::ChessBoard(const ChessBoard &board)
{
    state = Matrix<ChessPiece *>(board.state);
    white_pieces = std::vector<ChessPiece *>(board.white_pieces);
    black_pieces = std::vector<ChessPiece *>(board.black_pieces);
}

void ChessBoard::move_piece(const ChessMove chessmove)
{
    ChessPiece *chesspiece = chessmove.piece;
    if (chesspiece->capturingMove(chessmove.to_x, chessmove.to_y))
    {
        ChessPiece *to_remove = state(chessmove.from_x, chessmove.from_y);

        if (to_remove->isWhite) {
            white_pieces.erase(std::remove(white_pieces.begin(), white_pieces.end(), to_remove), white_pieces.end());
            captured_white_pieces.push_back(to_remove);
        }
        else {
            black_pieces.erase(std::remove(black_pieces.begin(), black_pieces.end(), to_remove), black_pieces.end());
            captured_black_pieces.push_back(to_remove);
        }
        
        state(chessmove.to_x, chessmove.to_y) = chesspiece;
    }
    else if (chesspiece->nonCapturingMove(chessmove.to_x, chessmove.to_y))
    {
        state(chessmove.from_x, chessmove.from_y) = nullptr;
        state(chessmove.to_x, chessmove.to_y) = chesspiece;
    }
    else
    {
        throw std::runtime_error("Invalid move!");
    }
}

ChessPiece * ChessBoard::promote_piece(const ChessPiece * piece, const std::string promotion) {
    ChessPiece * promoted;
    if (promotion == "q")
        promoted = new Queen(*piece);
    else if (promotion == "r")
        promoted = new Rook(*piece);
    else if (promotion == "b")
        promoted = new Bishop(*piece);
    else if (promotion == "n")
        promoted = new Knight(*piece);
    else
        throw std::runtime_error("Promotion " + promotion + " not recognised!");
    
    state(piece->x, piece->y) = promoted;

    delete piece;

    return promoted;
}

std::vector<ChessMove> ChessBoard::capturingMoves(bool isWhite) const
{
    std::vector<ChessMove> possible_moves;

    if (isWhite)
        for (auto piece : white_pieces)
        {
            std::vector<ChessMove> moves = piece->capturingMoves();
            possible_moves.insert(possible_moves.end(), moves.begin(), moves.end());
        }
    else
        for (auto piece : black_pieces)
        {
            std::vector<ChessMove> moves = piece->capturingMoves();
            possible_moves.insert(possible_moves.end(), moves.begin(), moves.end());
        }
    return possible_moves;
}

std::vector<ChessMove> ChessBoard::nonCapturingMoves(bool isWhite) const
{
    std::vector<ChessMove> possible_moves;

    if (isWhite)
        for (auto piece : white_pieces)
        {
            std::vector<ChessMove> moves = piece->nonCapturingMoves();
            possible_moves.insert(possible_moves.end(), moves.begin(), moves.end());
        }
    else
        for (auto piece : black_pieces)
        {
            std::vector<ChessMove> moves = piece->nonCapturingMoves();
            possible_moves.insert(possible_moves.end(), moves.begin(), moves.end());
        }
    return possible_moves;
}

std::vector<ChessPiece *> ChessBoard::promotablePieces(const bool is_white) const {
    std::vector<ChessPiece *> promotable_pieces;
    
    int y = 0;
    std::vector<ChessPiece *> pieces;
    
    if (is_white) {
        y = 0;
        pieces = white_pieces;
    }
    else {
        y = 7;
        pieces = black_pieces;
    }

    for (int x = 0; x < 8; x++) {
        ChessPiece * piece = state(x, y);
        if (piece == nullptr) continue;
        if (typeid(piece).name() == "Pawn" && std::count(pieces.begin(), pieces.end(), piece))
            promotable_pieces.push_back(piece);
    } 

    return promotable_pieces;
}

bool ChessBoard::forces_capturing_move(const ChessMove & move, const bool is_white) const {
    std::vector<ChessMove> current_capturing_moves = capturingMoves(!is_white);

    throw std::logic_error("Not yet implemented");
}

const ChessBoard ChessBoard::apply_move(const ChessMove move) const
{
    ChessBoard new_board = ChessBoard(*this);

    new_board.move_piece(move);
    return new_board;
}

ChessBoard &
operator>>(std::istream &is, ChessBoard &board)
{
    /* Replace the current board */
    board.state.reset();
    board.white_pieces.clear();
    board.black_pieces.clear();
    board.captured_black_pieces.clear();
    board.captured_white_pieces.clear();

    char piece;
    ChessPiece *chesspiece = nullptr;
    bool is_white;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            if (!(is >> piece))
                throw std::runtime_error("Chess board not big enough");

            if (std::isupper(piece))
                is_white = true;
            else
                is_white = false;

            piece = std::toupper(piece);

            if (piece == 'K')
                chesspiece = new King(j, i, is_white, &board);
            else if (piece == 'Q')
                chesspiece = new Queen(j, i, is_white, &board);
            else if (piece == 'R')
                chesspiece = new Rook(j, i, is_white, &board);
            else if (piece == 'N')
                chesspiece = new Knight(j, i, is_white, &board);
            else if (piece == 'B')
                chesspiece = new Bishop(j, i, is_white, &board);
            else if (piece == 'P')
                chesspiece = new Pawn(j, i, is_white, &board);
            else if (piece == '.') {
                chesspiece = nullptr;
                continue;
            }
            else
                throw std::runtime_error("Character not recognised");

            board.state(j, i) = chesspiece;

            if (is_white)
                board.white_pieces.push_back(chesspiece);
            else
                board.black_pieces.push_back(chesspiece);
        }

    return board;
}

std::ostream &operator<<(std::ostream &ostream, ChessBoard &board)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board.is_free(j, i))
                ostream << "_";
            else
                ostream << board.state(j, i);
        }
        ostream << std::endl;
    }

    return ostream << std::endl;
}

std::wostream &operator<<(std::wostream &ostream, ChessBoard &board)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board.is_free(i, j))
                ostream << " ";
            else
                ostream << board.state(j, i);
        }
        ostream << std::endl;
    }

    return ostream << std::endl;
}

const bool ChessBoard::is_free(const int x, const int y) const
{
    return state(x, y) == nullptr;
}

const ChessPiece *ChessBoard::at(const int x, const int y) const
{
    return state(x, y);
}

bool ChessBoard::isEOG() const {
    return white_pieces.size() == 0 || black_pieces.size() == 0;
}

bool ChessBoard::is_white_win() const {
    return black_pieces.size() == 0;
}

bool ChessBoard::is_black_win() const {
    return white_pieces.size() == 0;
}

bool ChessBoard::is_draw() const {
    throw std::runtime_error("Not yet implemented.");
}