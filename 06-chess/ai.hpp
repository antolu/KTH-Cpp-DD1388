#ifndef DD1388_AI_HPP
#define DD1388_AI_HPP

// #include "chess.hpp"
#include "gameengine.hpp"
// #include "chessmove.hpp"
#include <random>

class GameEngine;
class ChessMove;

class AI
{
    bool is_white;
protected:
    std::mt19937 rng;
    static constexpr char promotions[4] = {'q', 'r', 'b', 'n'};

    ChessMove select_random(const std::vector<ChessMove> & moves);
    char select_random_promotion();
public:
    AI();
    virtual ~AI();

    virtual ChessMove play(const GameEngine & state) = 0;
};

class AI1 : public AI {
    
    public:
    AI1();

    ChessMove play(const GameEngine & state);
};

class AI2 : public AI {
    public:
    AI2();

    ChessMove play(const GameEngine & state);
};

//class minimaxAI : public AI {
//    public:
//    minimaxAI();
//    minimaxAI(bool is_white);
//    ~minimaxAI();
//
//    ChessMove play(const GameEngine & state);
//};


#endif