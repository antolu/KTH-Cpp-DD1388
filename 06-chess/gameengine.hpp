#ifndef DD1388_GAMEENGINE_HPP
#define DD1388_GAMEENGINE_HPP

#include <vector> 

#include "ai.hpp"

class ChessBoard;
struct ChessMove;
class ChessPiece;

class AI;

class GameEngine
{
    AI *player1;
    AI *player2;
    ChessBoard *board;
    int current_player = 0;

    friend class AI1;
    friend class AI2;

public:
    GameEngine();
    ~GameEngine();
    GameEngine(std::string player1_type, std::string player2_type);
    GameEngine(std::string player1_type, std::string player2_type, ChessBoard *board);

    int getNextPlayer() const;

    void play();
    std::vector<ChessBoard> find_possible_moves() const;
    std::vector<ChessMove> find_capturing_moves() const;
    std::vector<ChessMove> find_noncapturing_moves() const;
    std::vector<ChessBoard> find_promotional_moves() const;
    std::vector<ChessPiece *> find_promotable_pieces() const;
    ChessBoard get_board() const; // Returns a gopy of the board
    bool isEOG() const;
    bool is_white_win() const;
    bool is_black_win() const;
    bool is_draw() const;
    bool is_white_turn() const;
    bool is_black_turn() const;
};

#endif