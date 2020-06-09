// #include "chess.hpp"
#include "chesspiece.hpp"
#include "chesspieces.hpp"

#include <cmath>
#include <functional>

King::King(int x, int y, bool is_white, ChessBoard *board) : ChessPiece(x, y, is_white, board){};

King::King(const ChessPiece & piece) : ChessPiece(piece) {};

King::~King(){};

King* King::clone() {
    return new King(*this);
}

int King::validMove(const int to_x, const int to_y) const
{
    if (out_of_bounds(to_x, to_y))
        return 0;

    int dx = std::abs(x - to_x);
    int dy = std::abs(y - to_y);

    if (!(dx * dy == 1 || dx + dy == 1))
        return 0; // Invalid move

    if (board->is_free(to_x, to_y)) // location is free
        return 1;

    if (!same_color(board->at(to_x, to_y)))
        return 2;

    return 0;
}

char32_t King::utfRepresentation() const
{
    if (isWhite)
        return U'\u265A';
    else
        return U'\u2654';
};
char King::latin1Representation() const
{
    if (isWhite)
        return 'K';
    return 'k';
}

std::vector<ChessMove> King::generate_moves(const int sign) {
    std::vector<ChessMove> possibleMoves;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && i == j)
                continue;

            if (validMove(x + i, y + j) == sign)
                possibleMoves.push_back(ChessMove(x, y, x + i, y + j, this));
        }

    return possibleMoves;
}

std::vector<ChessMove> King::capturingMoves() {
    return generate_moves(2);
}

std::vector<ChessMove> King::nonCapturingMoves()
{
    return generate_moves(1);
}

Queen::Queen(int x, int y, bool is_white, ChessBoard *board) : ChessPiece(x, y, is_white, board){};

Queen::Queen(const ChessPiece & piece) : ChessPiece(piece) {};

Queen::~Queen(){};

Queen* Queen::clone() {
    return new Queen(*this);
}

int Queen::validMove(const int to_x, const int to_y) const
{
    if (out_of_bounds(to_x, to_y))
        return 0;

    int bishop = Bishop::validMove(to_x, to_y);
    int rook = Rook::validMove(to_x, to_y);

    auto check = [](int bishop, int rook) {
        if (bishop > rook)
            return bishop;
        else if (rook > bishop)
            return rook;
        else
            return 0;
    };

    return check(bishop, rook);
}

char32_t Queen::utfRepresentation() const
{
    if (isWhite)
        return U'\u265B';
    else
        return U'\u2655';
};
char Queen::latin1Representation() const
{
    if (isWhite)
        return 'Q';
    return 'q';
}

std::vector<ChessMove> Queen::generate_moves(const int sign)
{
    std::vector<ChessMove> rook_moves = Rook::generate_moves(sign);
    std::vector<ChessMove> bishop_moves = Bishop::generate_moves(sign);

    rook_moves.insert(rook_moves.end(), bishop_moves.begin(), bishop_moves.end());

    return rook_moves;
}

std::vector<ChessMove> Queen::capturingMoves() {
    return generate_moves(2);
}

std::vector<ChessMove> Queen::nonCapturingMoves()
{
    return generate_moves(1);
}

Bishop::Bishop(int x, int y, bool is_white, ChessBoard *board) : ChessPiece(x, y, is_white, board){};
Bishop::Bishop(const ChessPiece & piece) : ChessPiece(piece) {};
Bishop::Bishop(){};
Bishop::~Bishop(){};
Bishop* Bishop::clone() {
    return new Bishop(*this);
}

int Bishop::validMove(const int to_x, const int to_y) const
{
    if (out_of_bounds(to_x, to_y))
        return 0;

    /* dx needs to be dy for diagonal movement */
    if (!(std::abs(x - to_x) == std::abs(y - to_y)))
        return 0;

    /* Check intermediate squares for obstructions */
    int mid_x = x;
    int mid_y = y;

    auto north_east_condition = [&to_x, &to_y](int mid_x, int mid_y) { return mid_x < to_x && mid_y > to_y; };
    auto north_east_increment = [&mid_x, &mid_y]() {mid_x++; mid_y--; };

    auto south_east_condition = [&to_x, &to_y](int mid_x, int mid_y) { return mid_x < to_x && mid_y < to_y; };
    auto south_east_increment = [&mid_x, &mid_y]() {mid_x++; mid_y++; };

    auto south_west_condition = [&to_x, &to_y](int mid_x, int mid_y) { return mid_x > to_x && mid_y < to_y; };
    auto south_west_increment = [&mid_x, &mid_y]() {mid_x--; mid_y++; };

    auto north_west_condition = [&to_x, &to_y](int mid_x, int mid_y) { return mid_x > to_x && mid_y > to_y; };
    auto north_west_increment = [&mid_x, &mid_y]() {mid_x--; mid_y--; };

    auto loop = [&mid_x, &mid_y, &to_x, &to_y, this](auto condition, auto increment) {
        mid_x = x;
        mid_y = y;

        increment();
        while (condition(mid_x, mid_y))
        {
            if (!board->is_free(mid_x, mid_y))
                return 0;
            increment();
        }

        return 1;
    };

    int res;
    if (to_y < y)
    { // north
        if (to_x > x)
        { //north-east
            res = loop(north_east_condition, north_east_increment);
        }
        else
        { //north-west
            res = loop(north_west_condition, north_west_increment);
        }
    }
    else
    { //south
        if (to_x > x)
        { //south-east
            res = loop(south_east_condition, south_east_increment);
        }
        else
        { //south-west
            res = loop(south_west_condition, south_west_increment);
        }
    }

    if (res == 0)
        return 0;

    /* Check if spot is free */
    if (board->is_free(to_x, to_y))
        return 1;

    /* Check color of piece at destination location */
    if (!same_color(board->at(to_x, to_y)))
        return 2;

    return 0;
}

char32_t Bishop::utfRepresentation() const
{
    if (isWhite)
        return U'\u265D';
    else
        return U'\u2657';
};
char Bishop::latin1Representation() const
{
    if (isWhite)
        return 'B';
    return 'b';
}

std::vector<ChessMove> Bishop::generate_moves(const int sign) {
    std::vector<ChessMove> possible_moves;

    /* Generate diagonal moves */
    int to_x, to_y;
    to_x = x;
    to_y = y;

    auto north_east_condition = [](int to_x, int to_y) { return to_x < 8 && to_y > 0; };
    auto north_east_increment = [&to_x, &to_y]() {to_x++; to_y--; };

    auto south_east_condition = [](int to_x, int to_y) { return to_x < 8 && to_y < 8; };
    auto south_east_increment = [&to_x, &to_y]() {to_x++; to_y++; };

    auto south_west_condition = [](int to_x, int to_y) { return to_x > 0 && to_y < 8; };
    auto south_west_increment = [&to_x, &to_y]() {to_x--; to_y++; };

    auto north_west_condition = [](int to_x, int to_y) { return to_x > 0 && to_y > 0; };
    auto north_west_increment = [&to_x, &to_y]() {to_x--; to_y--; };

    auto loop = [&to_x, &to_y, &sign, &possible_moves, this](auto &condition, auto &increment) {
        auto add_move = [&possible_moves, this](int to_x, int to_y) { possible_moves.push_back(ChessMove(x, y, to_x, to_y, this)); };

        int move_res;
        while (condition(to_x, to_y))
        { // north east
            increment();

            move_res = Bishop::validMove(to_x, to_y);

            /* If move is as requested, add it */
            if (move_res == sign)
            {
                add_move(to_x, to_y);
                continue;
            }

            /* Break if path is obstructed */
            if (move_res == 0)
                break;
        }
    };

    loop(north_east_condition, north_east_increment);
    to_x = x;
    to_y = y;
    loop(south_east_condition, south_east_increment);
    to_x = x;
    to_y = y;
    loop(south_west_condition, south_west_increment);
    to_x = x;
    to_y = y;
    loop(north_west_condition, north_west_increment);
    to_x = x;
    to_y = y;

    return possible_moves;
}

std::vector<ChessMove> Bishop::capturingMoves() {
    return Bishop::generate_moves(2);
}

std::vector<ChessMove> Bishop::nonCapturingMoves()
{
    return Bishop::generate_moves(1);
}

Rook::Rook(int x, int y, bool is_white, ChessBoard *board) : ChessPiece(x, y, is_white, board){};
Rook::Rook(const ChessPiece & piece) : ChessPiece(piece) {};
Rook::Rook(){};
Rook::~Rook(){};
Rook* Rook::clone() {
    return new Rook(*this);
}

int Rook::validMove(const int to_x, const int to_y) const
{
    if (out_of_bounds(to_x, to_y))
        return 0;

    /* needs to move in a straight line */
    if (!(to_x == x || to_y == y))
        return 0;

    // /* check for pieces inbetween */
    int mid_x, mid_y;
    mid_x = x;
    mid_y = y;
    // TODO: might need to adjust for off by one to skip checking at destination

    auto loop = [&mid_x, &mid_y, this](auto &condition, auto &increment) {
        increment();
        while (condition(mid_x, mid_y))
        {
            if (!board->is_free(mid_x, mid_y))
                return 0;
            increment();
        }
        return 1;
    };

    int res;
    if (to_x > x)
    {
        auto east_condition = [&to_x](int mid_x, int mid_y) { return mid_x < to_x; };
        auto east_increment = [&mid_x]() { mid_x++; };
        res = loop(east_condition, east_increment);
    }
    else if (to_x < x)
    {
        auto west_condition = [&to_x](int mid_x, int mid_y) { return mid_x > to_x; };
        auto west_increment = [&mid_x]() { mid_x--; };
        res = loop(west_condition, west_increment);
    }
    else if (to_y > y)
    {
        auto north_condition = [&to_y](int mid_x, int mid_y) { return mid_y > to_y; };
        auto north_increment = [&mid_y]() { mid_y--; };
        res = loop(north_condition, north_increment);
    }
    else if (to_x < y)
    {
        auto south_condition = [&to_y](int mid_x, int mid_y) { return mid_y < to_y; };
        auto south_increment = [&mid_y]() { mid_y++; };
        res = loop(south_condition, south_increment);
    } else {
        res = 0;
    }

    if (res == 0)
        return 0;

    if (board->is_free(to_x, to_y))
        return 1;

    if (!same_color(board->at(to_x, to_y)))
        return 2;

    return 0;
}

char32_t Rook::utfRepresentation() const
{
    if (isWhite)
        return U'\u265C';
    else
        return U'\u2656';
};
char Rook::latin1Representation() const
{
    if (isWhite)
        return 'R';
    return 'r';
}

std::vector<ChessMove> Rook::generate_moves(const int sign) {
    std::vector<ChessMove> possible_moves;

    /* Generate diagonal moves */
    int to_x, to_y;
    to_x = x;
    to_y = y;

    auto north_condition = [](int to_x, int to_y) { return to_y > 0; };
    auto north_increment = [&to_y]() { to_y--; };

    auto east_condition = [](int to_x, int to_y) { return to_x < 8; };
    auto east_increment = [&to_x]() { to_x++; };

    auto south_condition = [](int to_x, int to_y) { return to_y < 8; };
    auto south_increment = [&to_y]() { to_y++; };

    auto west_condition = [](int to_x, int to_y) { return to_x > 0; };
    auto west_increment = [&to_x]() { to_x--; };

    auto loop = [&to_x, &to_y, &sign, &possible_moves, this](auto &condition, auto &increment) {
        auto add_move = [&possible_moves, this](int to_x, int to_y) { possible_moves.push_back(ChessMove(x, y, to_x, to_y, this)); };

        int move_res;
        while (condition(to_x, to_y))
        { // north east
            increment();

            move_res = Rook::validMove(to_x, to_y);

            /* If move is as requested, add it */
            if (move_res == sign)
            {
                add_move(to_x, to_y);
                continue;
            }

            /* Break if path is obstructed */
            if (move_res == 0)
                break;
        }
    };

    loop(north_condition, north_increment);
    to_x = x;
    to_y = y;
    loop(east_condition, east_increment);
    to_x = x;
    to_y = y;
    loop(south_condition, south_increment);
    to_x = x;
    to_y = y;
    loop(west_condition, west_increment);
    to_x = x;
    to_y = y;

    return possible_moves;
}

std::vector<ChessMove> Rook::capturingMoves() {
    return Rook::generate_moves(2);
}

std::vector<ChessMove> Rook::nonCapturingMoves()
{
    return Rook::generate_moves(1);
}

Knight::Knight(int x, int y, bool is_white, ChessBoard *board) : ChessPiece(x, y, is_white, board){};
Knight::Knight(const ChessPiece & piece) : ChessPiece(piece) {};
Knight::~Knight(){};
Knight* Knight::clone() {
    return new Knight(*this);
}

int Knight::validMove(const int to_x, const int to_y) const
{
    if (out_of_bounds(to_x, to_y))
        return 0;

    int dx = std::abs(x - to_x);
    int dy = std::abs(y - to_y);

    if (!(std::pow(dx, 2) + std::pow(dy, 2) == 5))
        return 0;

    if (board->is_free(to_x, to_y))
        return 1;

    if (!same_color(board->at(to_x, to_y)))
        return 2;

    return 0;
}

char32_t Knight::utfRepresentation() const
{
    if (isWhite)
        return U'\u265E';
    else
        return U'\u2658';
};
char Knight::latin1Representation() const
{
    if (isWhite)
        return 'N';
    return 'n';
}

std::vector<ChessMove> Knight::generate_moves(const int sign) {
    std::vector<ChessMove> possible_moves;

    int to_x, to_y;

    /* generate moves based off prewritten offset */
    for (auto move_offset : move_candidates)
    {
        to_x = x + move_offset.x;
        to_y = y + move_offset.y;

        if (validMove(to_x, to_y) == sign)
            possible_moves.push_back(ChessMove(x, y, to_x, to_y, this));
    }

    return possible_moves;
}

std::vector<ChessMove> Knight::capturingMoves() {
    return generate_moves(2);
}

std::vector<ChessMove> Knight::nonCapturingMoves()
{
    return generate_moves(1);
}

Pawn::Pawn(int x, int y, bool is_white, ChessBoard *board) : ChessPiece(x, y, is_white, board){};
Pawn::Pawn(const ChessPiece & piece) : ChessPiece(piece) {};
Pawn::~Pawn(){};
Pawn* Pawn::clone() {
    return new Pawn(*this);
}

int Pawn::validMove(const int to_x, const int to_y) const
{
    if (out_of_bounds(to_x, to_y))
        return 0;

    if (!isWhite)
    {
        if (not( to_y - y == 1 or (to_y - y == 2 and y == 1) )) // not a step forward
            return 0;

        if (std::abs(to_x - x) > 1)
            return 0; // more than one horizontal move

        /* Check the board if the space is vacant */
        if (board->is_free(to_x, to_y) && to_x == x)
            return 1;

        /* Check destination square for color */
        if (board->at(to_x, to_y) != nullptr && !same_color(board->at(to_x, to_y)) && std::abs(to_x - x) == 1)
            return 2;

        return 0;
    }
    else
    {
        if (not( to_y - y == -1 or (to_y - y == -2 and y == 6 ))) // not a step forward
            return 0;

        if (std::abs(to_x - x) > 1)
            return 0; // more than one horizontal move

        /* Check the board if the space is vacant */
        if (board->is_free(to_x, to_y) && to_x == x)
            return 1;

        /* Check destination square for color */
        if (board->at(to_x, to_y) != nullptr && !same_color(board->at(to_x, to_y)) && std::abs(to_x - x) == 1)
            return 2;

        return 0;
    }
}

char32_t Pawn::utfRepresentation() const
{
    if (isWhite)
        return U'\u265F';
    else
        return U'\u2659';
};
char Pawn::latin1Representation() const
{
    if (isWhite)
        return 'P';
    return 'p';
}

std::vector<ChessMove> Pawn::generate_moves(const int sign) {
    std::vector<ChessMove> possible_moves;

    /* forward or backward move depending on color */
    std::vector<int> to_y;
    if (!isWhite) {
        to_y.push_back(y + 1);
        if (y == 1)
            to_y.push_back(y + 2);
    }
    else {
        to_y.push_back(y - 1);
        if (y == 6)
            to_y.push_back(y - 2);
    }

    /* diagonal or straight move */
    for (int t_y: to_y)
        for (int to_x = x - 1; to_x <= x + 1; to_x++)
            if (validMove(to_x, t_y) == sign)
                possible_moves.push_back(ChessMove(x, y, to_x, t_y, this));

    return possible_moves;
}

bool Pawn::promotionMove(const int to_x, const int to_y) const {

    if (not validMove(to_x, to_y))
        return false;

    return (this->y == 6 and to_y == 7 and this->isWhite) or (this->y == 1 and to_y == 0 and not this->isWhite);

}

std::vector<ChessMove> Pawn::capturingMoves() {
    return generate_moves(2);
}

std::vector<ChessMove> Pawn::nonCapturingMoves()
{
    return generate_moves(1);
};