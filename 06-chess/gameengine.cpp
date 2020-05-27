#include <vector>

#include "gameengine.hpp"
#include "chesspiece.hpp"
#include "chessboard.hpp"
// #include "chess.hpp"
#include "ai.hpp"
#include <set>

GameEngine::GameEngine() {
    board = new ChessBoard();

    player1 = new AI1(true);
    player2 = new AI1(false);
    current_player = 0;
}

GameEngine::~GameEngine() {
    delete board;
    delete player1;
    delete player2;
}

GameEngine::GameEngine(std::string player1_type, std::string player2_type) {
    std::string player_types[2] = {player1_type, player2_type};
    AI* players[2] = {player1, player2};

    for (int i = 0; i < 2; i++) {
        if (player_types[i] == "random")
            players[i] = new AI1(i == 0);
        else if (player_types[i] == "random1step")
            players[i] = new AI2(i == 0);
        else if (player_types[i] == "minimax")
            players[i] = new minimaxAI(i == 0);
        else
            throw std::runtime_error("AI type not recognised: " + player_types[i]);
    }

    (void) players;
    board = new ChessBoard();
}

GameEngine::GameEngine(std::string player1_type, std::string player2_type, ChessBoard * board) : GameEngine(player1_type, player2_type) {
    delete this->board;
    this->board = board;
}

int GameEngine::getNextPlayer() const {
    return current_player;
}

void GameEngine::play() {
    AI* player[2] = {player1, player2};

    while (!board->isEOG()) {
        ChessMove move = player[current_player]->play(*this);
        /* Need to check if a piece is promoted */
        board->move_piece(move);
        current_player = !current_player;
    }
}

std::vector<ChessBoard> GameEngine::find_possible_moves() const {
    std::vector<ChessMove> possible_moves = board->capturingMoves(current_player == 0);
    std::vector<ChessMove> more_moves = board->nonCapturingMoves(current_player == 0);
    
    possible_moves.insert(possible_moves.end(), more_moves.begin(), more_moves.end());

    std::vector<ChessBoard> possible_boards;
    possible_boards.reserve(possible_moves.size());

    for (ChessMove move : possible_moves) {
        possible_boards.push_back(board->apply_move(move));
    }

    return possible_boards;
}

std::vector<ChessMove> GameEngine::find_capturing_moves() const  {
    return board->capturingMoves(current_player == 0);
}

std::vector<ChessMove> GameEngine::find_noncapturing_moves() const {
    return board->nonCapturingMoves(current_player == 0);
}

std::vector<ChessMove> GameEngine::find_promotion_moves() const {
    return board->promotablePieces(current_player == 0);
}

bool GameEngine::forces_capturing_move(const ChessMove & move) const {
    int current_player = getNextPlayer();

    auto opponent_capturing_moves = board->capturingMoves(!current_player);

    return forces_capturing_move(move, opponent_capturing_moves);
}

bool GameEngine::forces_capturing_move(const ChessMove &move, const std::vector<ChessMove> &current_capturing_moves) const {
    ChessBoard new_board = board->apply_move(move);

    auto new_opponent_moves = new_board.capturingMoves(!getNextPlayer());

    std::set<ChessMove> current_moves(current_capturing_moves.begin(), current_capturing_moves.end());
    std::set<ChessMove> new_moves(new_opponent_moves.begin(), new_opponent_moves.end());

    if (current_moves == new_moves)
        return false;

    return new_moves.size() > current_moves.size();

}

ChessBoard GameEngine::get_board() const {
    return ChessBoard(*board);
}

bool GameEngine::isEOG() const {
    return board->isEOG();
}

bool GameEngine::is_white_win() const {
    return board->is_white_win();
}

bool GameEngine::is_black_win() const {
    return board->is_black_win();
} 

bool GameEngine::is_draw() const {
    return board->is_draw();
}

bool GameEngine::is_white_turn() const {
    return current_player == 0;
}

bool GameEngine::is_black_turn() const {
    return current_player == 1;
}

