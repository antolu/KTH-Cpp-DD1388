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
    static char promotions[4] = {'q', 'r', 'b', 'n'};

    ChessMove select_random(const std::vector<ChessMove> & moves) const;
public:
    AI();
    AI(bool is_white);
    virtual ~AI();

    virtual ChessMove play(const GameEngine & state);
};

class AI1 : public AI {
    
    public:
    AI1();
    AI1(bool is_white);

    ChessMove play(const GameEngine & state);
};

class AI2 : public AI {
    public:
    AI2(bool is_white);

    ChessMove play(const GameEngine & state);
};

class minimaxAI : public AI {
    public:
    minimaxAI();
    minimaxAI(bool is_white);
    ~minimaxAI();

    ChessMove play(const GameEngine & state);
};


#endif