#include <random>
#include <string>

#include "chesspiece.hpp"
#include "chessboard.hpp"
#include "ai.hpp"
#include "gameengine.hpp"
#include "chessmove.hpp"


AI::AI() : rng((std::random_device())()) {
}

AI::~AI() = default;;

ChessMove AI::select_random(const std::vector<ChessMove> &moves) {

    if (moves.size() == 1)
        return moves[0];

    std::uniform_int_distribution<int> dist(0, (int) moves.size() - 1);

    int move = dist(rng);

//    std::cout << "selected move " << move << std::endl;

    return moves[move];
}

char AI::select_random_promotion() {
    std::uniform_int_distribution<int> choice_dist(0, 3);
    return promotions[choice_dist(rng)];
}

AI1::AI1() = default;

ChessMove AI1::play(const GameEngine &state) {

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
        ChessMove to_promote = select_random(promotion_moves);

        to_promote.promotion = select_random_promotion();

        return to_promote;
    }

    throw std::logic_error("No moves could be found.");
}

ChessMove AI2::play(const GameEngine &state) {
    ChessBoard * board = state.get_board();
    int current_player = state.getNextPlayer();

    auto find_moves = [this, &state](const std::vector<ChessMove> &possible_moves,
                                     const std::vector<ChessMove> &opponent_capturing_moves) -> ChessMove {
        std::vector<ChessMove> bad_moves;

        for (ChessMove move: possible_moves)
            if (state.forces_capturing_move(move, opponent_capturing_moves))
                bad_moves.push_back(move);

        if (!bad_moves.empty())
            return select_random(bad_moves);
        else
        {
            ChessMove ret = select_random(possible_moves);
            return ret;
        }
    };

    auto opponent_capturing_moves = board->capturingMoves(current_player != 0);

    /* First check for capturing moves */
    std::vector<ChessMove> capturing_moves = board->capturingMoves(current_player == 0);
    if (!capturing_moves.empty())
        return find_moves(capturing_moves, opponent_capturing_moves);

    /* Get noncapturing moves and see if they force a move */
    auto non_capturing_moves = board->nonCapturingMoves(current_player == 0);
    if (!non_capturing_moves.empty()) {
        return find_moves(non_capturing_moves, opponent_capturing_moves);
    }

    /* Check for possible promotions */
    auto promotion_moves = board->promotionalMoves(current_player == 0);
    if (!promotion_moves.empty()) {
        // TODO: Check if a promoted piece has a capturing move

        std::vector<ChessMove> possible_promotions;
        for (ChessMove move: promotion_moves)
            for (char p: promotions) {
                move.promotion = p;
                possible_promotions.push_back(move);
            }
        return find_moves(possible_promotions, opponent_capturing_moves);
    }

    throw std::logic_error("No more valid moves!");
}

AI2::AI2() = default;

//minimaxAI::minimaxAI(bool is_white) {
//
//}
//
//minimaxAI::~minimaxAI() {};
//
//ChessMove minimaxAI::play(const GameEngine &state) {
//    throw std::logic_error("Not yet implemented.");
//}