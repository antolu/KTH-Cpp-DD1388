#include <gtest/gtest.h>

#include <iostream>
#include "string"

#include "chesspiece.hpp"
#include "chessboard.hpp"
#include "chessmove.hpp"

TEST( pawns, 1) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "..ppp..." << std::endl;
	s << "...P...." << std::endl;
	s << "...P...." << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);
	std::vector<ChessMove> black_capturing_moves = chess.capturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 2 );
	EXPECT_EQ( black_capturing_moves.size(), 2 );
}

TEST( pawns, 2) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "...ppp.." << std::endl;
	s << ".PPPPP.." << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);
	std::vector<ChessMove> black_capturing_moves = chess.capturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 5 );
	EXPECT_EQ( black_capturing_moves.size(), 5 );
}

TEST( pawns, 3) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "....p.p." << std::endl;
	s << "........" << std::endl;
	s << ".....P.." << std::endl;
	s << "........" << std::endl;
	s >> chess;

	std::cout << chess << std::endl;

}

TEST( pawns, 4) {
	ChessBoard chess;
	std::stringstream s;
	s << "Q..n...r" << std::endl;
	s << "........" << std::endl;
	s << "n.r....." << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 3 );
}

TEST( king, 1) {
	ChessBoard chess;
	std::stringstream s;
	s << "......bK" << std::endl;
	s << "......nn" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 3 );
}

TEST( king, 2) {
	ChessBoard chess;
	std::stringstream s;
	s << "Kb......" << std::endl;
	s << "nn......" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 3 );
}

TEST( king, 3) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "nn......" << std::endl;
	s << "Kn......" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 3 );
}

TEST( king, 4) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "......nn" << std::endl;
	s << "......bK" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 3 );
}

TEST( king, 5) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "..nnn..." << std::endl;
	s << "..nKn..." << std::endl;
	s << "..nnn..." << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 8 );
}

TEST( knight, 1) {
	ChessBoard chess;
	std::stringstream s;
	s << "n......n" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "n......n" << std::endl;
	s >> chess;
	std::vector<ChessMove> black_noncapturing_moves = chess.nonCapturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( black_noncapturing_moves.size(), 8 );
}

TEST( knight, 2) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "..n.n..." << std::endl;
	s << ".n...n.." << std::endl;
	s << "...K...." << std::endl;
	s << ".n...n.." << std::endl;
	s << "..n.n..." << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> black_capturing_moves = chess.capturingMoves(false);
	std::vector<ChessMove> white_noncapturing_moves = chess.nonCapturingMoves(true);
	std::vector<ChessMove> black_noncapturing_moves = chess.nonCapturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( black_capturing_moves.size(), 8 );
	EXPECT_EQ( white_noncapturing_moves.size(), 8 );
	EXPECT_EQ( black_noncapturing_moves.size(), 48 );
}

TEST( rook, 1) {
	ChessBoard chess;
	std::stringstream s;
	s << "R......R" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "R......R" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_noncapturing_moves = chess.nonCapturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_noncapturing_moves.size(), 48 );
}

TEST( rook, 2) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "...p...." << std::endl;
	s << "........" << std::endl;
	s << ".b.R..b." << std::endl;
	s << "........" << std::endl;
	s << "...k...." << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;

	std::cout << chess << std::endl;

}

TEST( rook, 3) {
	ChessBoard chess;
	std::stringstream s;
	s << "...p...." << std::endl;
	s << "...p...." << std::endl;
	s << "........" << std::endl;
	s << "bb.R..bb" << std::endl;
	s << "........" << std::endl;
	s << "...k...." << std::endl;
	s << "...p...." << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 4 );
}

TEST( rook, 4) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "...R...." << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_noncapturing_moves = chess.nonCapturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_noncapturing_moves.size(), 14 );
}

TEST( bishop, 1) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "...b...." << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> black_noncapturing_moves = chess.nonCapturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( black_noncapturing_moves.size(), 13 );
}

TEST( bishop, 2) {
	ChessBoard chess;
	std::stringstream s;
	s << "b......b" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "b......b" << std::endl;
	s >> chess;
	std::vector<ChessMove> black_noncapturing_moves = chess.nonCapturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( black_noncapturing_moves.size(), 24 );
}

TEST( bishop, 3) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << ".K...K.." << std::endl;
	s << "........" << std::endl;
	s << "...b...." << std::endl;
	s << "........" << std::endl;
	s << ".K...K.." << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> black_capturing_moves = chess.capturingMoves(false);
	std::vector<ChessMove> black_noncapturing_moves = chess.nonCapturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( black_capturing_moves.size(), 4 );
	EXPECT_EQ( black_noncapturing_moves.size(), 4 );
}

TEST( bishop, 4) {
	ChessBoard chess;
	std::stringstream s;
	s << "K.....K." << std::endl;
	s << ".K...K.." << std::endl;
	s << "........" << std::endl;
	s << "...b...." << std::endl;
	s << "........" << std::endl;
	s << ".K...K.." << std::endl;
	s << "K.....K." << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> black_capturing_moves = chess.capturingMoves(false);
	std::vector<ChessMove> black_noncapturing_moves = chess.nonCapturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( black_capturing_moves.size(), 4 );
	EXPECT_EQ( black_noncapturing_moves.size(), 4 );
}

TEST( queen, 1) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << ".kkkkk.." << std::endl;
	s << ".k...k.." << std::endl;
	s << ".k.Q.k.." << std::endl;
	s << ".k...k.." << std::endl;
	s << ".kkkkk.." << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);
	std::vector<ChessMove> white_noncapturing_moves = chess.nonCapturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 8 );
	EXPECT_EQ( white_noncapturing_moves.size(), 8 );
}

TEST( queen, 2) {
	ChessBoard chess;
	std::stringstream s;
	s << "Q......q" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "q......Q" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);
	std::vector<ChessMove> black_capturing_moves = chess.capturingMoves(false);
	std::vector<ChessMove> white_noncapturing_moves = chess.nonCapturingMoves(true);
	std::vector<ChessMove> black_noncapturing_moves = chess.nonCapturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 4 );
	EXPECT_EQ( black_capturing_moves.size(), 4 );
	EXPECT_EQ( white_noncapturing_moves.size(), 36 );
	EXPECT_EQ( black_noncapturing_moves.size(), 36 );
}

TEST( pawn, 1) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "PPPPPPPP" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "pppppppp" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_promotional_moves = chess.promotionalMoves(true);
	std::vector<ChessMove> black_promotional_moves = chess.promotionalMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_promotional_moves.size(), 8 );
	EXPECT_EQ( black_promotional_moves.size(), 8 );
}

TEST( pawn, 2) {
	ChessBoard chess;
	std::stringstream s;
	s << "PPPPPPPP" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "pppppppp" << std::endl;
	s >> chess;

	std::cout << chess << std::endl;

}

TEST( pawn, 3) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "pppppppp" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "PPPPPPPP" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_noncapturing_moves = chess.nonCapturingMoves(true);
	std::vector<ChessMove> black_noncapturing_moves = chess.nonCapturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_noncapturing_moves.size(), 16 );
	EXPECT_EQ( black_noncapturing_moves.size(), 16 );
}

TEST( canvas, 1) {
	ChessBoard chess;
	std::stringstream s;
	s << "R..n...." << std::endl;
	s << "bn......" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 2 );
}

TEST( canvas, 2) {
	ChessBoard chess;
	std::stringstream s;
	s << "B..n...." << std::endl;
	s << "bn......" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 1 );
}

TEST( canvas, 3) {
	ChessBoard chess;
	std::stringstream s;
	s << "N..n...." << std::endl;
	s << "bnp....." << std::endl;
	s << ".p......" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 2 );
}

TEST( canvas, 4) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "......p." << std::endl;
	s << ".......R" << std::endl;
	s << "..npn..." << std::endl;
	s << "...P...." << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);
	std::vector<ChessMove> black_capturing_moves = chess.capturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 2 );
	EXPECT_EQ( black_capturing_moves.size(), 1 );
}

TEST( canvas, 5) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << ".r......" << std::endl;
	s << ".p......" << std::endl;
	s << "...P...n" << std::endl;
	s << "......P." << std::endl;
	s << ".N...B.." << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 1 );
}

TEST( canvas, 6) {
	ChessBoard chess;
	std::stringstream s;
	s << ".....Q.." << std::endl;
	s << "...q...." << std::endl;
	s << "......Q." << std::endl;
	s << "q......." << std::endl;
	s << ".......Q" << std::endl;
	s << ".q......" << std::endl;
	s << "....Q..." << std::endl;
	s << "..q....." << std::endl;
	s >> chess;

	std::cout << chess << std::endl;

}

TEST( canvas, 7) {
	ChessBoard chess;
	std::stringstream s;
	s << "rnbqkbnr" << std::endl;
	s << "pppppppp" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "PPPPPPPP" << std::endl;
	s << "RNBQKBNR" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_noncapturing_moves = chess.nonCapturingMoves(true);
	std::vector<ChessMove> black_noncapturing_moves = chess.nonCapturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_noncapturing_moves.size(), 20 );
	EXPECT_EQ( black_noncapturing_moves.size(), 20 );
}

TEST( canvas, 8) {
	ChessBoard chess;
	std::stringstream s;
	s << "rnbqkbnr" << std::endl;
	s << "pppppppp" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "....P..." << std::endl;
	s << "........" << std::endl;
	s << "PPPP.PPP" << std::endl;
	s << "RNBQKBNR" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_noncapturing_moves = chess.nonCapturingMoves(true);
	std::vector<ChessMove> black_noncapturing_moves = chess.nonCapturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_noncapturing_moves.size(), 30 );
	EXPECT_EQ( black_noncapturing_moves.size(), 20 );
}

TEST( canvas, 9) {
	ChessBoard chess;
	std::stringstream s;
	s << "rnbqkbnr" << std::endl;
	s << "p.pppppp" << std::endl;
	s << "........" << std::endl;
	s << ".p......" << std::endl;
	s << "....P..." << std::endl;
	s << "........" << std::endl;
	s << "PPPP.PPP" << std::endl;
	s << "RNBQKBNR" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 1 );
}

TEST( canvas, 10) {
	ChessBoard chess;
	std::stringstream s;
	s << "........" << std::endl;
	s << ".......p" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "........" << std::endl;
	s << "Q.P..pp." << std::endl;
	s << ".....PPP" << std::endl;
	s << "......NR" << std::endl;
	s >> chess;
	std::vector<ChessMove> white_capturing_moves = chess.capturingMoves(true);
	std::vector<ChessMove> black_capturing_moves = chess.capturingMoves(false);

	std::cout << chess << std::endl;

	EXPECT_EQ( white_capturing_moves.size(), 4 );
	EXPECT_EQ( black_capturing_moves.size(), 3 );
}

