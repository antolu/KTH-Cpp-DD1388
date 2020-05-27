#include <random>
#include <string>

#include "chessboard.hpp"
#include "ai.hpp"
#include "gameengine.hpp"
#include "chessmove.hpp"


AI::AI() {
    std::random_device dev;
    rng = std::mt19937(dev());
}

AI::~AI() = default;;

ChessMove AI::play(const GameEngine & state) {
    return ChessMove({0, 0, 0, 0, nullptr});
}

ChessMove AI::select_random(const std::vector<ChessMove> &moves) const {
    std::uniform_int_distribution<int> dist(0, moves.size());
    return moves[dist(rng)];
}

AI1::AI1() = default;

AI1::AI1(bool is_white) {

}

ChessMove AI1::play(const GameEngine & state) {

    /* Capturing moves */
    auto capturing_moves = state.find_capturing_moves();
    if (!capturing_moves.empty()) {
        return select_random(capturing_moves);
    }

    /* Non-capturing moves */
    auto noncapturing_moves = state.find_noncapturing_moves();
    if (!noncapturing_moves.empty()) {
        return select_random(noncapturing_moves);
    }

    /* Promotion */
    std::vector<ChessMove> promotion_moves = state.find_promotion_moves();
    if (!promotion_moves.empty()) {
        std::uniform_int_distribution<int> dist(0, promotion_moves.size());
        ChessMove to_promote = promotion_moves[dist(rng)];

        std::uniform_int_distribution<int> choice_dist(0, 4);
        char promotion = promotions[choice_dist(rng)];

        to_promote.promotion = promotion;

        return to_promote;
    }

    return ChessMove(0, 0, 0, 0, nullptr);
}

AI2::AI2(bool is_white) {
    
}

ChessMove AI2::play(const GameEngine & state) {
    ChessBoard board = state.get_board();
    int current_player = state.getNextPlayer();

    auto find_good_moves = [this, &state] (const std::vector<ChessMove> & possible_moves, const std::vector<ChessMove> & opponent_capturing_moves) -> ChessMove {
        std::vector<ChessMove> good_moves;

        for (ChessMove move: possible_moves)
            if (state.forces_capturing_move(move, opponent_capturing_moves))
                good_moves.push_back(move);

        if (!good_moves.empty())
            return select_random(good_moves);
        else
            return select_random(possible_moves);
    };

    auto opponent_capturing_moves = board.capturingMoves(current_player != 0);

    /* Get noncapturing moves and see if they force a move */
    auto non_capturing_moves = board.nonCapturingMoves(current_player == 0);
    if (!non_capturing_moves.empty())
        return find_good_moves(non_capturing_moves, opponent_capturing_moves);

    std::vector<ChessMove> capturing_moves = board.capturingMoves(current_player == 0);
    if (!capturing_moves.empty())
        return find_good_moves(capturing_moves, opponent_capturing_moves);

    /* Check for possible promotions */
    auto promotion_moves = board.promotablePieces(current_player == 0);
    if (!promotion_moves.empty()) {
        // TODO: Check if a promoted piece has a capturing move
        std::uniform_int_distribution<int> dist(0, promotion_moves.size());
        ChessMove to_promote = promotion_moves[dist(rng)];

        std::uniform_int_distribution<int> choice_dist(0, 4);
        char promotion = promotions[choice_dist(rng)];

        to_promote.promotion = promotion;

        return to_promote;
    }

    return ChessMove({0, 0, 0, 0, nullptr});
}

minimaxAI::minimaxAI(bool is_white) {
    
}

minimaxAI::~minimaxAI() {};

ChessMove minimaxAI::play(const GameEngine & state) {
    return ChessMove({0, 0, 0, 0, nullptr});
}