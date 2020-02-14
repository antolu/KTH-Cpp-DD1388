#include <random>
#include <string>

#include "ai.hpp"
#include "gameengine.hpp"
#include "chessmove.hpp"


AI::AI() {}

AI::~AI() {};

ChessMove AI::play(const GameEngine & state) {
    return ChessMove({0, 0, 0, 0, nullptr});
}

AI1::AI1() {
    std::random_device dev;
    rng = std::mt19937(dev());
}

AI1::AI1(bool is_white) {

}

ChessMove AI1::play(const GameEngine & state) {
    /* Promotion */
    std::vector<ChessPiece *> promotable_pieces = state.find_promotable_pieces();
    if (promotable_pieces.size() > 0) {
        std::string promotions[4] = {"q", "r", "b", "n"};
        std::uniform_int_distribution<int> dist(0, promotable_pieces.size());
        ChessPiece * to_promote = promotable_pieces[dist(rng)];

        std::uniform_int_distribution<int> choice_dist(0, 4);
        state.board->promote_piece(to_promote, promotions[choice_dist(rng)]);
    }

    std::vector<ChessMove> capturing_moves = state.find_capturing_moves();

    /* Capturing moves */
    if (capturing_moves.size() > 0) {
        std::uniform_int_distribution<int> dist(0, capturing_moves.size());
        return capturing_moves[dist(rng)];
    }

    /* Non-capturing moves */
    std::vector noncapturing_moves = state.find_noncapturing_moves();
    if (noncapturing_moves.size() > 0) {
        std::uniform_int_distribution<int> dist(0, noncapturing_moves.size());
        return noncapturing_moves[dist(rng)];
    }

    return ChessMove({0, 0, 0, 0, nullptr});
}

AI2::AI2(bool is_white) {
    
}

ChessMove AI2::play(const GameEngine & state) {
    return ChessMove({0, 0, 0, 0, nullptr});
}

minimaxAI::minimaxAI(bool is_white) {
    
}

minimaxAI::~minimaxAI() {};

ChessMove minimaxAI::play(const GameEngine & state) {
    return ChessMove({0, 0, 0, 0, nullptr});
}