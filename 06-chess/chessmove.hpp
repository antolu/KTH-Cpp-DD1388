#ifndef DD1388_CHESSMOVE_HPP
#define DD1388_CHESSMOVE_HPP

class ChessPiece;

struct ChessMove {
    int from_x;
    int from_y;
    int to_x;
    int to_y;

    ChessPiece* piece; // you can change the position of the chess piece with this pointer.

    char promotion = 0;

    ChessMove(int from_x, int from_y, int to_x, int to_y, ChessPiece * piece) : promotion(0){
        this->from_x = from_x;
        this->from_y = from_y;
        this->to_x = to_x;
        this->to_y = to_y;
        this->piece = piece;
    }

//    ChessMove(const ChessMove& other) {
//        copy(other);
//    }
//
//    ChessMove& operator=(const ChessMove& other) {
//        copy(other);
//        return *this;
//    }
//
//private:
//    void copy(const ChessMove& other) {
//        this->from_x = other.from_x;
//        this->from_y = other.from_y;
//        this->to_x = other.to_x;
//        this->to_y = other.to_y;
//        this->promotion = other.promotion;
//        this->piece = other.piece->clone();
//    }
};

inline bool operator==(const ChessMove & lhs, const ChessMove & rhs) {
    return lhs.from_x == rhs.from_x && lhs.from_y == rhs.from_y && lhs.to_x == rhs.to_x && lhs.to_y == rhs.to_y && lhs.piece == rhs.piece;
}

inline bool operator<(const ChessMove& lhs, const ChessMove& rhs) {
    return false;
}

#endif