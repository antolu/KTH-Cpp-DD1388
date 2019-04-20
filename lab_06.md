# Lab 6 Chesspieces, AI and Losing chess

Implement classes for Knight, Pawn, Rook, Bishop, Queen and  King. Each of these classes should inherit from _class Chesspiece_

If you are unsure about the rules, please [read up on them on Wikipedia](https://en.wikipedia.org/wiki/Rules_of_chess). For the purposes of this lab, you can skip castling ("Rockad" in Swedish), en passant and moves that place the king in check.


## Chesspiece

```
  class ChessPiece {
	friend void ChessBoard::move_piece(ChessMove p);
    protected:
        int x,y;
        bool isWhite;
        ChessBoard* board;
        /**
         * Returns 0 if target square is unreachable.
         * Returns 1 if target square is reachable and empty.
         * Returns 2 if move captures a piece.
         */
        virtual int validMove(int to_x, int to_y);
        virtual char32_t utfRepresentation();
        virtual char latin1Representation();
    public:
        /**
         * Checks if this move is valid for this piece and captures
         * a piece of the opposite color.
         */
        bool capturingMove(int to_x, int to_y);
        /**
         * Checks if this move is valid but does not capture a piece.
         */
        bool nonCapturingMove(int to_x, int to_y);
        virtual vector<ChessMove> capturingMoves();
        virtual vector<ChessMove> nonCapturingMoves();

		/**
		* For testing multiple inheritance
		*/
		int unnecessaryInt;
    };
```

* _capturingMove_ and _nonCapturingMove_ call the protected function _validMove_  .

* _capturingMoves_  returns a _vector_ with _ChessMoves_ that captures a piece of the opposing color

* _nonCapturingMoves_ returns a _vector_ with _ChessMoves_ that moves to an empty space.

You may add private or protected functions to the design of _ChessPiece_ class

### King

Let Δx be abs(x1-x2) and Δy be abs(y1-y2)

Then either Δx * Δy is one or Δx + Δy is one


### Knight

The implementation to check valid moves for knights is to check if Δx² + Δy² is 5.

### Pawn

You may skip en passant move.

The implementation for capturingmove is to check y+1, x+1 and x-1 and for the other color; y-1, x+1 and x-1.

The noncapturing move needs to check if there is a blocking piece at y+1/y-1.

If the pawn is at starting position (second row) it may move 1 or 2 squares ahead

If the pawn is one row from last, the pawn till transform to another piece.

### Bishop and Rook

Implement two classes for Rook and Bishop that implements _ChessPiece_

### Queen

Implement a Queen class that inherits from both _Bishop_ and
_Rook_. This will create a diamond inheritance which is generally
considered dangerous and one of the reasons many programming languages
do not allow multiple inheritance.

Create a queen object and try to set the unnecessaryInt in
_ChessPiece_. What happens?  

Think about if it would be better if the quuen had a bishop and a rock
(as members) instead of inherited from them?


## Board encoding

Your test program will accept text input in the form of chessboard
states. The states will be encoded according to these rules.  <PRE> R
= Rook ("Torn" in Swedish) N = kNight [sic] ("Springare" or "Häst" in
Swedish) B = Bishop ("Löpare" in Swedish) Q = Queen K = King P = Pawn
. = Empty square White pieces are denoted with uppercase letters and
black pieces are denoted with lowercase letters.  Every line has 8
symbols and ends with a newline.  Every board consists of 8 lines.
</PRE>

Each class that inherits from ChessPiece should implement an utf8-representation that uses the [utf8-representation](https://en.wikipedia.org/wiki/Chess_symbols_in_Unicode) of chess pieces AND a latin1-representation according to the table above (R,n,Q... etc.)

* _utfRepresentation_

* _latin1Representation_


## Chess move

A chess move is defined as

```c++
struct ChessMove {
    int from_x;
    int from_y;
    int to_x;
    int to_y;

    ChessPiece* piece;   // you can change the position of the chess piece with this pointer.
};
```

## Chess board

Implement a chess board class that contains your chess pieces. You
must use your Matris class from lab4 to represent the chess
board. You may add additional functions or members (public
constructors or vectors with white and black pieces) to the
_ChessBoard_ class.


```c++
   using std::vector;
   using std::istream;
   using std::string;
    class ChessBoard {
   // add additional members or functions of your choice

    private:
        Matris<ChessPiece* > state; // Matris from lab 4  Matrix

    public:
        void move_piece(ChessMove chessMove);
        vector<ChessMove> capturingMoves(bool isWhite);
        vector<ChessMove> nonCapturingMoves(bool isWhite);

    };
	Chessboard & operator>>(istream & , ChessBoard &):
```



## Sample program

```c++
using std::vector; using std::stringstream; using std::cout; using std::endl;
//...
    ChessBoard chess;
    stringstream s;
    s << ".....Q.." << endl;
    s << "...q...." << endl;
    s << "......Q." << endl;
    s << "q......." << endl;
    s << ".......Q" << endl;
    s << ".q......" << endl;
    s << "....Q..." << endl;
    s << "..q.....";
    s >> chess;
    vector<ChessMove> v = chess.capturingMoves(true);

    if (v.size() != 0) {
        cout << "capturingMoves FAILED, expected 0 moves but got " << v.size() << " moves" << endl;
    } else {
        cout << "capturingMoves PASSED, expected 0 moves and got " << v.size() << " moves" << endl;
    }
```

## Tests

For this assignement, do _not_ write unit tests for each function.

There are some (simple testboards here that only tests the
number of valid capturing
moves)[https://kth.instructure.com/courses/4722/pages/tester-slagschack].

Expand the tests with more boards and verify that
_capturingMove_ , _nonCapturingMove_ and _validMove_ works as
intended.  

How many test boards will you need to be sure your functions work correctly?

# Losing chess AI (slagschack)

Implement two AI that plays the game [losing chess](https://en.wikipedia.org/wiki/Losing_chess), a variation of chess where the object is to lose all your pieces to an opponent who is forced to capture whenever possible.
For the purposes of this lab, you can skip castling ("Rockad" in Swedish), En Passant and moves that place the king in check but you do need to implement [pawn promotion](https://en.wikipedia.org/wiki/Promotion_%28chess%29)

Use the given struct/classes from the previous assignement but add
member values/functions when needed.


## AI 1 - random thinker

* If there are no capturing moves, this AI will perform a non capturing at random.

* If there are several capturing moves, the AI will perform one of them at random.

* If there is a pawn promotion, a random piece will be selected.

## AI 2 - thinks one step ahead. but defaults to random

* If there are no capturing moves
    - Check if any non-capturing move will force a capturing move for the opponent.
    - If not, play a random move.

* If there are several capturing moves
    - Check if any capturing move will force a capturing move for the opponent
    - If not, play a random capturing move.

* If there is a pawn promotion
    - If possible, pick a piece that can not capture on its next move.
    - If not possible, promote to a random piece.


## Play the game

Let the two AI play against each other and print the gameboard after each move.
As before the game should be initialized by reading a starting board (not
necesarilly the chess standard starting positions).

Let the starting color and kind of AI be command line options to your program.

#### Questions


#### The code relies on virtual functions. Could the code have been written without virtual functions?


#### Capturingmove calls a protected virtual function but is not virtual in itself. Noncapturingmoves/Capturingmoves are public virtual functions. What is your opinion of that design difference? Write your thoughts.


#### Should ChessPiece have been an abstract class?


#### There was no separate unit test for each function in this assignement, instead you tested several functions at once with different boards. What are the benefits and drawbacks for this kind of testing compared to unit tests?


#### What is the problem with a diamond inheritance?


#### What do you think of the general design of this code? What could be improved?


#### What was most difficult to do in this assignement?
