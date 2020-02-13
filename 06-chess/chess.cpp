#include <vector>
#include <codecvt>

#include "../04-matrix/matrix.hpp"
#include "chess.hpp"
#include "chesspieces.hpp"

ChessPiece::ChessPiece(){};

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

ChessBoard::ChessBoard() {
    // std::stringstream s;
    // s << "rnbqkbnr" << std::endl;
    // s << "pppppppp" << std::endl;
    // s << "........" << std::endl;
    // s << "........" << std::endl;
    // s << "........" << std::endl;
    // s << "........" << std::endl;
    // s << "PPPPPPPP" << std::endl;
    // s << "RNBQKBNR";
    // s >> *this;
};

ChessBoard::~ChessBoard()
{
    for (auto piece : white_pieces)
        delete piece;

    for (auto piece : black_pieces)
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

        // if (to_remove->isWhite)
        //     white_pieces.erase(to_remove);
        // else
        //     black_pieces.erase(to_remove);
        delete to_remove;

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

std::vector<ChessMove> ChessBoard::capturingMoves(bool isWhite) const
{
    std::vector<ChessMove> possible_moves;

    if (isWhite)
        for (auto piece : white_pieces)
        {
            std::vector<ChessMove> moves = piece->capturingMoves();
            possible_moves.insert(possible_moves.begin(), moves.begin(), moves.end());
        }
    else
        for (auto piece : black_pieces)
        {
            std::vector<ChessMove> moves = piece->capturingMoves();
            possible_moves.insert(possible_moves.begin(), moves.begin(), moves.end());
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
            possible_moves.insert(possible_moves.begin(), moves.begin(), moves.end());
        }
    else
        for (auto piece : black_pieces)
        {
            std::vector<ChessMove> moves = piece->nonCapturingMoves();
            possible_moves.insert(possible_moves.begin(), moves.begin(), moves.end());
        }
    return possible_moves;
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

std::ostream & operator<<(std::ostream& ostream, ChessPiece * chesspiece) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv32;
    return ostream << conv32.to_bytes(chesspiece->utfRepresentation());
}

std::wostream & operator<<(std::wostream& ostream, ChessPiece * chesspiece) {
    return ostream << chesspiece->utfRepresentation();
}