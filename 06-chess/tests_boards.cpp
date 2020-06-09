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

	EXPECT_EQ( white_capturing_moves.size(), 5 );
	EXPECT_EQ( black_capturing_moves.size(), 5 );
}

TEST( pawns, 3) {
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

	EXPECT_EQ( white_capturing_moves.size(), 8 );
}

