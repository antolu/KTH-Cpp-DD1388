#include <vector>

#include "chessboard.hpp"
#include "chesspiece.hpp"
#include "gameengine.hpp"
#include "ai.hpp"
#include <set>
#include <thread>


GameEngine::GameEngine() {
    board = new ChessBoard();

    player1 = new AI1();
    player2 = new AI1();
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
            players[i] = new AI1();
        else if (player_types[i] == "random1step")
            players[i] = new AI2();
//        else if (player_types[i] == "minimax")
//            players[i] = new minimaxAI(i == 0);
        else
            throw std::runtime_error("AI type not recognised: " + player_types[i]);
    }

    player1 = players[0];
    player2 = players[1];
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

    int turn = 0;
    std::string plyr;
    std::cout << "Starting game, initial board state: \n" << *board << "\n" << std::endl;

    while (not(board->isEOG() or board->is_draw())) {
        plyr = current_player ? "black" :"white";
        ChessMove move = player[current_player]->play(*this);
        /* Need to check if a piece is promoted */
        board->move_piece(move);
        std::cout << "Player " << plyr << " finished turn " << ++turn << ". Current board state:\n" << *board << std::endl;
        current_player = !current_player;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    if (board->is_draw() and not board->isEOG())
        std::cout << "Game ended in a draw." << std::endl;
    else
        std::cout << "Player " << (is_black_win() ? "black" : "white") << " won!" << std::endl;
}

std::vector<ChessBoard*> GameEngine::find_possible_boards() const {
    std::vector<ChessMove> possible_moves = board->capturingMoves(current_player == 0);
    std::vector<ChessMove> more_moves = board->nonCapturingMoves(current_player == 0);
    
    possible_moves.insert(possible_moves.end(), more_moves.begin(), more_moves.end());

    std::vector<ChessBoard*> possible_boards;
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
    return board->promotionalMoves(current_player == 0);
}

bool GameEngine::forces_capturing_move(const ChessMove & move) const {
    int current_player = getNextPlayer();

    auto opponent_capturing_moves = board->capturingMoves(!current_player);

    return forces_capturing_move(move, opponent_capturing_moves);
}

bool GameEngine::forces_capturing_move(const ChessMove &move, const std::vector<ChessMove> &current_capturing_moves) const {
    ChessBoard * new_board = board->apply_move(move);

    auto new_opponent_moves = new_board->capturingMoves(getNextPlayer());

    if (new_opponent_moves.empty())
        return false;

    auto contains_same = [](const std::vector<ChessMove> & first, const std::vector<ChessMove> & second) -> bool {
        int count = 0;

        if (first.size() != second.size())
            return false;

        std::set<int> checked;

        for (ChessMove move: first) {
            for (int i = 0; i < second.size(); i++) {
                if (checked.count(i))
                    break;
                else {
                    ChessMove other = second[i];
                    if (move.to_y == other.to_y and move.to_x == other.to_x and
                        move.from_x == other.from_x and move.from_y == other.from_y) {
                        checked.insert(i);
                        count++;
                    }
                }

            }
        }
        return count == first.size();
    };

    return not contains_same(current_capturing_moves, new_opponent_moves) and new_opponent_moves.size() > current_capturing_moves.size();
}

ChessBoard * GameEngine::get_board() const {
    return board;
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

