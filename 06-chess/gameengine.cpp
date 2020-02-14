#include <vector>

#include "gameengine.hpp"
#include "chesspiece.hpp"
#include "chessboard.hpp"
// #include "chess.hpp"
#include "ai.hpp"

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
        player[current_player]->play(*this);
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

std::vector<ChessBoard> GameEngine::find_promotional_moves() const {
    std::vector<ChessPiece *> promotional_pieces = board->promotablePieces(current_player == 0);
    std::vector<ChessBoard> moves;
    return moves;
}

std::vector<ChessPiece *> GameEngine::find_promotable_pieces() const {
    return board->promotablePieces(current_player == 0);
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