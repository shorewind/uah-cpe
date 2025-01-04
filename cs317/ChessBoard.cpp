/* ChessBoard.cpp  -- Beth Allen Spring 2024
   Manipulate elements of an NxN chessboard
   Implements the features of the chessboard
*/
#include "ChessBoard.h"
#include <iomanip>

//-------------------------------------------------------------------------
// Default constructor - initializes a board to contain no data
//-------------------------------------------------------------------------
ChessBoard::ChessBoard() {
	mSize = 0;
	mBoard = NULL;
}

//-------------------------------------------------------------------------
// General constructor - Creates a board of a give size
//-------------------------------------------------------------------------
ChessBoard::ChessBoard(int size) {
	createNewBoard(size);
}

//-------------------------------------------------------------------------
// destructor -frees the board when its variable ceases to exist
//-------------------------------------------------------------------------
ChessBoard::~ChessBoard() {
	freeBoardMemory();
}

//-------------------------------------------------------------------------
// freeBoardMemory
// private utility method to release a board's allocated memory
//-------------------------------------------------------------------------
void ChessBoard::freeBoardMemory() {
	if (mBoard != NULL) {
		for (int row = 0; row < mSize; row++)
			delete[] mBoard[row];
		delete[] mBoard;
	}
	mBoard = NULL;
	mSize = 0;
}
//-------------------------------------------------------------------------
// createNewBoard
// interface method to create a board of a particular size
//-------------------------------------------------------------------------
void ChessBoard::createNewBoard(int size) {
	if (mBoard != NULL) {
		freeBoardMemory();  // free existing board if one is already here
	}
	if (size > MAXSIZE)
		size = MAXSIZE;  // I impose a limit on board size to keep it resonable for my computer system

	mBoard = new int* [size];
	for (int row = 0; row < size; row++)
		mBoard[row] = new int[size];					// allocate an array for each row
	mSize = size;
	mNumSquares = size * size;
	clear();
}

//-------------------------------------------------------------------------
// display
// Write the board contents to an output stream
//-------------------------------------------------------------------------
void ChessBoard::display(ostream & out) const {
	out << "Matrix of size: " << mSize << "\n";
	for (int row = 0; row < mSize; row++) {
		for (int col = 0; col < mSize; col++)
		{
			out << setw(5) << mBoard[row][col];
		}
		out << "\n";
	}

}
//-------------------------------------------------------------------------
// clear
// set the square values to all 0 indicating the knight has not visitied
//-------------------------------------------------------------------------
void ChessBoard::clear() {
	for (int row = 0; row < mSize; row++)
		for (int col = 0; col < mSize; col++)
			mBoard[row][col] = 0;
}

//-------------------------------------------------------------------------
// inRange
// Check whether a potential move is in range or not
//-------------------------------------------------------------------------
bool ChessBoard::inRange(int r, int c) {
	return (r >= 0 && r < mSize && c >= 0 && c < mSize);
}

//-------------------------------------------------------------------------
// solveIt
// interface method to start the backtracking solution algorithm
//-------------------------------------------------------------------------

bool ChessBoard::solveIt(int row = 0, int col = 0) {
	if (row < 0 || row >= mSize || col < 0 || col >= mSize)  // make sure start spot is actually on the board
		return true;

	if (findPath(row, col, 1))
		return true;
	else
		return false;

}
//-------------------------------------------------------------------------
// findpath
// Recursive backtracking method to find the sequence of moves to 
// tour the board.
//-------------------------------------------------------------------------
bool ChessBoard::findPath(int row, int col, int moveNumber) {

	if (mBoard[row][col] != 0) { // this spot is taken already and cannot be part of this solution
		return false;
	}
	mBoard[row][col] = moveNumber;    // this spot is open, so let's save it before computing the next move
	if (moveNumber == mNumSquares) {  // we have just filled the last square, so return success
		return true;
	}
	// otherwise try to solve the additional moves each failure from inrange or find path (goes forward) will cause us to
    // drop down to the next try below.  Basically if all 8 fail here, we end up returning false, which returns us out
    // to an earlier recursive call of findpath so that level can (backtrack) and try an alternate move
	if (inRange(row + 1, col + 2) && findPath(row + 1, col + 2, moveNumber + 1))
		return true;
	if (inRange(row + 2, col + 1) && findPath(row + 2, col + 1, moveNumber + 1))
		return true;
	if (inRange(row + 1, col - 2) && findPath(row + 1, col - 2, moveNumber + 1))
		return true;
	if (inRange(row + 2, col - 1) && findPath(row + 2, col - 1, moveNumber + 1))
		return true;
	if (inRange(row - 1, col + 2) && findPath(row - 1, col + 2, moveNumber + 1))
		return true;
	if (inRange(row - 2, col + 1) && findPath(row - 2, col + 1, moveNumber + 1))
		return true;
	if (inRange(row - 1, col - 2) && findPath(row - 1, col - 2, moveNumber + 1))
		return true;
	if (inRange(row - 2, col - 1) && findPath(row - 2, col - 1, moveNumber + 1))
		return true;

	// if we are still here we need to undue the proposed move, and then need to fail this level,
    // so it will return up a level to try the next move from there.
	mBoard[row][col] = 0;
	return false;
}