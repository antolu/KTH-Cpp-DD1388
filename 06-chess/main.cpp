#include "chess.hpp"
#include "chesspieces.hpp"
#include "chessmove.hpp"


#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "gtest/gtest.h"


TEST(CapturingMoves, 1) {
    ChessBoard chess;
    std::stringstream s;
    s << ".....Q.." << std::endl;
    s << "...q...." << std::endl;
    s << "......Q." << std::endl;
    s << "q......." << std::endl;
    s << ".......Q" << std::endl;
    s << ".q......" << std::endl;
    s << "....Q..." << std::endl;
    s << "..q.....";
    s >> chess;
    std::vector<ChessMove> v = chess.capturingMoves(true);

    std::cout << chess << std::endl;

    EXPECT_EQ( v.size(), 0);
}

TEST(CapturingMoves, 2) {
    ChessBoard chess;
    std::stringstream s;
    s << "Q..n...r" << std::endl;
    s << "........" << std::endl;
    s << "n.r....." << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........";
    s >> chess;

    EXPECT_EQ( chess.capturingMoves(true).size(), 3);
    EXPECT_EQ( chess.capturingMoves(false).size(), 0);

    std::cout << chess << std::endl;
}

TEST(CapturingMoves, 3) {
    ChessBoard chess;
    std::stringstream s;
    s << "Kb......" << std::endl;
    s << "nn......" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........";
    s >> chess;
    
    EXPECT_EQ( chess.capturingMoves(true).size(), 3);
    EXPECT_EQ( chess.capturingMoves(false).size(), 0);

    std::cout << chess << std::endl;
}

TEST(CapturingMoves, 4) {
    ChessBoard chess;
    std::stringstream s;
    s << "R..n...." << std::endl;
    s << "bn......" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........";
    s >> chess;
    
    EXPECT_EQ( chess.capturingMoves(true).size(), 2);
    EXPECT_EQ( chess.capturingMoves(false).size(), 0);

    std::cout << chess << std::endl;
}

TEST(CapturingMoves, 5) {
    ChessBoard chess;
    std::stringstream s;
    s << "B..n...." << std::endl;
    s << "bn......" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........";
    s >> chess;

    EXPECT_EQ( chess.capturingMoves(true).size(), 1);
    EXPECT_EQ( chess.capturingMoves(false).size(), 0);

    std::cout << chess << std::endl;
}

TEST(CapturingMoves, 6) {
    ChessBoard chess;
    std::stringstream s;
    s << "N..n...." << std::endl;
    s << "bnp....." << std::endl;
    s << ".p......" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........";
    s >> chess;

    EXPECT_EQ( chess.capturingMoves(true).size(), 2);
    EXPECT_EQ( chess.capturingMoves(false).size(), 0);

    std::cout << chess << std::endl;
}

TEST(CapturingMoves, 7) {
    ChessBoard chess;
    std::stringstream s;
    s << "........" << std::endl;
    s << "......p." << std::endl;
    s << ".......R" << std::endl;
    s << "..npn..." << std::endl;
    s << "...P...." << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........";
    s >> chess;

    EXPECT_EQ( chess.capturingMoves(true).size(), 2);
    EXPECT_EQ( chess.capturingMoves(false).size(), 1);
        
    std::cout << chess << std::endl;
}

TEST(CapturingMoves, 8) {
    ChessBoard chess;
    std::stringstream s;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << ".r......" << std::endl;
    s << ".p......" << std::endl;
    s << "...P...n" << std::endl;
    s << "......P." << std::endl;
    s << ".N...B..";
    s >> chess;

    EXPECT_EQ( chess.capturingMoves(true).size(), 1);
    EXPECT_EQ( chess.capturingMoves(false).size(), 0);
        
    std::cout << chess << std::endl;
}

TEST(CapturingMoves, 9) {
    ChessBoard chess;
    std::stringstream s;
    s << "rnbqkbnr" << std::endl;
    s << "pppppppp" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "PPPPPPPP" << std::endl;
    s << "RNBQKBNR";
    s >> chess;

    EXPECT_EQ( chess.capturingMoves(true).size(), 0);
    EXPECT_EQ( chess.capturingMoves(false).size(), 0);
        
    std::cout << chess << std::endl;
}

TEST(CapturingMoves, 10) {
    ChessBoard chess;
    std::stringstream s;
    s << "rnbqkbnr" << std::endl;
    s << "pppppppp" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "....P..." << std::endl;
    s << "........" << std::endl;
    s << "PPPP.PPP" << std::endl;
    s << "RNBQKBNR";
    s >> chess;

    EXPECT_EQ( chess.capturingMoves(true).size(), 0);
    EXPECT_EQ( chess.capturingMoves(false).size(), 0);
        
    std::cout << chess << std::endl;
}

TEST(CapturingMoves, 11) {
    ChessBoard chess;
    std::stringstream s;
    s << "rnbqkbnr" << std::endl;
    s << "p.pppppp" << std::endl;
    s << "........" << std::endl;
    s << ".p......" << std::endl;
    s << "....P..." << std::endl;
    s << "........" << std::endl;
    s << "PPPP.PPP" << std::endl;
    s << "RNBQKBNR";
    s >> chess;

    EXPECT_EQ( chess.capturingMoves(true).size(), 1);
    EXPECT_EQ( chess.capturingMoves(false).size(), 0);
        
    std::cout << chess << std::endl;
}

TEST(CapturingMoves, 12) {
    ChessBoard chess;
    std::stringstream s;
    s << "........" << std::endl;
    s << "......p." << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "........" << std::endl;
    s << "Q.P..pp." << std::endl;
    s << ".....PPP" << std::endl;
    s << "......NR";
    s >> chess;

    EXPECT_EQ( chess.capturingMoves(true).size(), 4);
    EXPECT_EQ( chess.capturingMoves(false).size(), 3);
        
    std::cout << chess << std::endl;
}

// TEST(Play,1) {
//     ChessBoard chess;
//     std::stringstream s;
//     s << "rnbqkbnr" << std::endl;
//     s << "pppppppp" << std::endl;
//     s << "........" << std::endl;
//     s << "........" << std::endl;
//     s << "........" << std::endl;
//     s << "........" << std::endl;
//     s << "PPPPPPPP" << std::endl;
//     s << "RNBQKBNR";
//     s >> chess;
// }


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
