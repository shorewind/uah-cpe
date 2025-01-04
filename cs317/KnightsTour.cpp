// File: KnightsTour.cpp -- BETH ALLEN SPRING 2024
// Gathers the information for the size of a chessboard and the starting point for the
// knight's tour.  The chessboard returns true or false indicating whether there is a solution
// Then provides the ability to display the board with the given path.
//-----------------------------------------------------------------------------

#include <iostream>
#include <chrono>

#include "ChessBoard.h"
using namespace std;

int main(void) {

	ChessBoard myBoard;
	int row, col;
	int N;

    cout << "Enter the board size (max of " << MAXSIZE << "): ";
	cin >> N;
	myBoard.createNewBoard(N);
	cout << "Enter starting square row number: (0-" << N-1 << "): ";
	cin >> row;
	cout << "Enter starting square col number: (0-" << N-1 << "): ";
	cin >> col;

    // start measuring time here
	chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();

	if (myBoard.solveIt(row, col))
		cout << "\nSolved! ";
	else
		cout << "\nNo solution found! ";

    // end measuring time here, do computation and print it out
	chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
	chrono::duration<double, micro> time = end - start;
	
	cout << "in " << fixed << setprecision(0) << time.count() << " microseconds\n\n";

	myBoard.display(cout);

	return 0;
}