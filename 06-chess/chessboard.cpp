#include <iostream>
#include <algorithm>
#include <sstream>
#include <codecvt>

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

ChessBoard::~ChessBoard() {
    for (auto piece : white_pieces)
        delete piece;

    for (auto piece : black_pieces)
        delete piece;

//    for (auto piece : captured_white_pieces)
//        delete piece;
//
//    for (auto piece : captured_black_pieces)
//        delete piece;
}

void ChessBoard::copy(const ChessBoard &other) {
    auto exists_in = [](const std::vector<ChessPiece *> &vec, const ChessPiece *ptr) -> bool {
        return std::find(vec.begin(), vec.end(), ptr) != vec.end();
    };

    ChessPiece *piece;
    ChessPiece *copy;
    state = Matrix<ChessPiece *>(8, 8);
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++) {
            if (other.state(y, x) == nullptr)
                continue;
            else {
                piece = other.state(y, x);
                copy = piece->clone();
                copy->set_board(this);

                if (exists_in(other.white_pieces, piece))
                    white_pieces.push_back(copy);
                else if (exists_in(other.black_pieces, piece))
                    black_pieces.push_back(copy);
                else
                    throw std::logic_error(
                            "Piece is neither registered as white, nor black. Probably something is wrong.");

                state(y, x) = copy;
            }
        }
}

ChessBoard::ChessBoard(const ChessBoard &board) {
    copy(board);
}

ChessBoard &ChessBoard::operator=(const ChessBoard &other) {
    if (this == &other)
        return *this;

    copy(other);
    return *this;
}

void ChessBoard::move_piece(const ChessMove &chessmove) {
    auto erase = [](std::vector<ChessPiece *> &pieces, ChessPiece *piece) {
        pieces.erase(std::remove(pieces.begin(), pieces.end(), piece), pieces.end());
    };

    ChessPiece *chesspiece = chessmove.piece;
    if (chessmove.promotion != 0) {
        // TODO: Should check for valid promotion
        if (!chesspiece->promotionMove(chessmove.to_x, chessmove.to_y))
            throw std::logic_error("Not a valid promotional move!");

        ChessPiece *new_piece = promote_piece(chessmove);
        if (chessmove.piece->isWhite)
            erase(white_pieces, chesspiece);
        else
            erase(black_pieces, chesspiece);

        delete chesspiece;
        state(chessmove.from_y, chessmove.from_x) = nullptr;
        state(chessmove.to_y, chessmove.to_x) = new_piece;
        chesspiece = new_piece;
    } else if (chesspiece->capturingMove(chessmove.to_x, chessmove.to_y)) {
        ChessPiece *to_remove = state(chessmove.to_y, chessmove.to_x);

        if (to_remove->isWhite) {
            erase(white_pieces, to_remove);
//            captured_white_pieces.push_back(to_remove);
        } else {
            erase(black_pieces, to_remove);
//            captured_black_pieces.push_back(to_remove);
        }
        delete to_remove;
        state(chessmove.from_y, chessmove.from_x) = nullptr;
        state(chessmove.to_y, chessmove.to_x) = chesspiece;
    } else if (chesspiece->nonCapturingMove(chessmove.to_x, chessmove.to_y)) {
        state(chessmove.from_y, chessmove.from_x) = nullptr;
        state(chessmove.to_y, chessmove.to_x) = chesspiece;
    } else {
        throw std::runtime_error("Invalid move!");
    }
    chesspiece->x = chessmove.to_x; chesspiece->y = chessmove.to_y;
}

ChessPiece *ChessBoard::promote_piece(const ChessMove &move) {
    ChessPiece *promoted;

    if (move.promotion == 'q')
        promoted = new Queen(*move.piece);
    else if (move.promotion == 'r')
        promoted = new Rook(*move.piece);
    else if (move.promotion == 'b')
        promoted = new Bishop(*move.piece);
    else if (move.promotion == 'n')
        promoted = new Knight(*move.piece);
    else
        throw std::runtime_error("Promotion " + std::to_string(move.promotion) + " not recognised!");

    return promoted;
}

std::vector<ChessMove> ChessBoard::capturingMoves(bool isWhite) const {
    std::vector<ChessMove> possible_moves;

    if (isWhite)
        for (auto piece : white_pieces) {
            std::vector<ChessMove> moves = piece->capturingMoves();
            possible_moves.insert(possible_moves.end(), moves.begin(), moves.end());
        }
    else
        for (auto piece : black_pieces) {
            std::vector<ChessMove> moves = piece->capturingMoves();
            possible_moves.insert(possible_moves.end(), moves.begin(), moves.end());
        }
    return possible_moves;
}

std::vector<ChessMove> ChessBoard::nonCapturingMoves(bool isWhite) const {
    std::vector<ChessMove> possible_moves;

    if (isWhite)
        for (auto piece : white_pieces) {
            std::vector<ChessMove> moves = piece->nonCapturingMoves();
            possible_moves.insert(possible_moves.end(), moves.begin(), moves.end());
        }
    else
        for (auto piece : black_pieces) {
            std::vector<ChessMove> moves = piece->nonCapturingMoves();
            possible_moves.insert(possible_moves.end(), moves.begin(), moves.end());
        }
    return possible_moves;
}

std::vector<ChessMove> ChessBoard::promotionalMoves(const bool is_white) const {
    std::vector<ChessMove> possible_moves;
    if (is_white)
        for (auto piece : white_pieces) {
            std::vector<ChessMove> moves = piece->promotionMoves();
            possible_moves.insert(possible_moves.end(), moves.begin(), moves.end());
        }
    else
        for (auto piece : black_pieces) {
            std::vector<ChessMove> moves = piece->promotionMoves();
            possible_moves.insert(possible_moves.end(), moves.begin(), moves.end());
        }
    return possible_moves;


//    std::vector<ChessMove> promotion_moves;
//
//    int y = 0;
//    int to_y;
//    std::vector<ChessPiece *> pieces;
//
//    if (is_white) {
//        y = 1;
//        to_y = 0;
//        pieces = white_pieces;
//    }
//    else {
//        y = 6;
//        to_y = 7;
//        pieces = black_pieces;
//    }
//
//    for (int x = 0; x < 8; x++) {
//        ChessPiece * piece = state(x, y);
//        if (piece == nullptr) continue;
//        if (std::string(typeid(piece).name()) == "Pawn" && std::count(pieces.begin(), pieces.end(), piece))
//            promotion_moves.push_back(ChessMove(x, y, x, to_y, piece));
//    }
//
//    return promotion_moves;
}


ChessBoard *ChessBoard::apply_move(ChessMove move) const {
    ChessBoard *new_board = new ChessBoard(*this);

    move.piece = new_board->state(move.from_y, move.from_x);

    new_board->move_piece(move);
    return new_board;
}

ChessBoard &
operator>>(std::istream &is, ChessBoard &board) {
    /* Replace the current board */
    board.state.reset();
    board.white_pieces.clear();
    board.black_pieces.clear();
    board.captured_black_pieces.clear();
    board.captured_white_pieces.clear();

    char piece;
    ChessPiece *chesspiece = nullptr;
    bool is_white;
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++) {
            if (!(is >> piece))
                throw std::runtime_error("Chess board not big enough");

            if (std::isupper(piece))
                is_white = true;
            else
                is_white = false;

            piece = std::toupper(piece);

            if (piece == 'K')
                chesspiece = new King(x, y, is_white, &board);
            else if (piece == 'Q')
                chesspiece = new Queen(x, y, is_white, &board);
            else if (piece == 'R')
                chesspiece = new Rook(x, y, is_white, &board);
            else if (piece == 'N')
                chesspiece = new Knight(x, y, is_white, &board);
            else if (piece == 'B')
                chesspiece = new Bishop(x, y, is_white, &board);
            else if (piece == 'P')
                chesspiece = new Pawn(x, y, is_white, &board);
            else if (piece == '.') {
                chesspiece = nullptr;
                continue;
            } else
                throw std::runtime_error("Character not recognised");

            board.state(y, x) = chesspiece;

            if (is_white)
                board.white_pieces.push_back(chesspiece);
            else
                board.black_pieces.push_back(chesspiece);
        }

    return board;
}

std::ostream &operator<<(std::ostream &ostream, ChessBoard &board) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv32;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            ostream << " ";
            if (board.is_free(x, y)) {
//                if (not ((i + j) % 2))
//                    ostream << conv32.to_bytes(U'\u25A0');
//                else
//                    ostream << conv32.to_bytes(U'\u25A1');
                ostream << "_";
            } else
                ostream << board.at(x, y);
            ostream << " ";
        }
        ostream << std::endl;
    }

    return ostream;
}

std::wostream &operator<<(std::wostream &ostream, ChessBoard &board) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (board.is_free(x, y))
                ostream << " ";
            else
                ostream << board.at(x, y);
        }
        ostream << std::endl;
    }

    return ostream;
}

const bool ChessBoard::is_free(const int x, const int y) const {
    return at(x, y) == nullptr;
}

ChessPiece *ChessBoard::at(const int x, const int y) const {
    return state(y, x);
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
    std::vector<ChessMove> white_moves;
    std::vector<ChessMove> black_moves;

    for (auto piece : white_pieces) {
        std::vector<ChessMove> moves = piece->nonCapturingMoves();
        white_moves.insert(white_moves.end(), moves.begin(), moves.end());
    }
    for (auto piece : black_pieces) {
        std::vector<ChessMove> moves = piece->nonCapturingMoves();
        black_moves.insert(black_moves.end(), moves.begin(), moves.end());
    }

    if (white_moves.empty() or black_moves.empty())
        return true;
    else
        return false;
}