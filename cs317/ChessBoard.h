#pragma once
/* ChessBoard.h  -- Beth Allen Spring 2024
   Manipulate elements of an NxN chessboard
   Max Size of the chessboard will be 10x10
   To ensure reasonable runtimes in project - your mileage may vary
   To see specific details about the functions defined in this file, see the comments provided in the .cpp implementation file
*/
#include <iostream>
#include <fstream>
using namespace std;

const int MAXSIZE = 10;  // a reasonable max size, you may update this constant
class ChessBoard {
	int mSize;        // size of board
	int mNumSquares;  // "
	int** mBoard;     // 2-d board, size to be allocated at runtime

private:
	void freeBoardMemory();     // used by the destructor to clean up a board's allocated memory
public:
	ChessBoard();               // default constructor - does not allocate board memory
	ChessBoard(int size);       // construct a board that is size x size
	~ChessBoard();              // destructor

	void createNewBoard(int size);    // can be called by the user to create new memory for the board anytime
	void display(ostream&) const;     // writes out a board to the output stream givem
	void clear();                     // resets the contents of a board to all 0s

	bool inRange(int r, int c);       // returns true if a potential move is on the board

	bool solveIt(int row, int col);   // a wrapper to call the recursive backtracker that actually does the work
	bool findPath(int row, int col, int moveNumber);    // do the work recursively
};