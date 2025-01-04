// ****************************************
// Program Title: Sample header file
// Project File: Project_09.cpp
// Name: Esther Shore
// Course Section: CPE-211-02
// Lab Section: 1
// Due Date: 11/13/22
// program description: Description of
// What the program does.
// ****************************************
#include <iostream>
#include <fstream>  /// ifstream
#include <climits> // INT_MAX
#include <iomanip> // setw

using namespace std;

const int MAX_ROWS = 10;
const int MAX_COLS = 10;  // global constants

typedef int BitArray[MAX_ROWS][MAX_COLS];  // global definition

// function prototypes
void OpenInputFile(ifstream&);
void ReadData(ifstream&, int&, int&, BitArray, BitArray);
void PrintInputArrays(int&, int&, BitArray, BitArray);
void CalculateOutputArrays(int&, int&, BitArray, BitArray, BitArray, BitArray, BitArray);
void PrintOutputArrays(int&, int&, BitArray, BitArray, BitArray);
void PrintIntegerEquivalents(int&, int&, BitArray, BitArray, BitArray);

int main()
{
	ifstream inFile;  // declare input file stream
	int numRows;
	int numCols;
	BitArray Array1;
	BitArray Array2;  // input array variables
	BitArray orArray;
	BitArray andArray;
	BitArray xorArray;  // output array variables

	// function calls
	OpenInputFile(inFile);
	ReadData(inFile, numRows, numCols, Array1, Array2);
	PrintInputArrays(numRows, numCols, Array1, Array2);
	CalculateOutputArrays(numRows, numCols, Array1, Array2, orArray, andArray, xorArray);
	PrintOutputArrays(numRows, numCols, orArray, andArray, xorArray);
	PrintIntegerEquivalents(numRows, numCols, orArray, andArray, xorArray);

	return 0;
}

void OpenInputFile(ifstream& inFile)
{
	string inFileName;
	
	cout << endl;
	cout << "Enter the name of the input file: ";
	cin >> inFileName;
	cout << inFileName << endl << endl;  // query and echo print user input
	inFile.open(inFileName.c_str());  // open input file
	
	while (inFile.fail())  // while the input file stream is in the fail state
	{
		cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> Input file failed to open properly!!" << endl;
		cout << "==> Attempted to open file: " << inFileName << endl;
		cout << "==> Please try again..." << endl;
		cout << string(47, '*') << endl << endl;
		
		inFile.clear();
		cout << "Enter the name of the input file: ";
		cin >> inFileName;
		
		cout << inFileName << endl << endl;  // continue asking for input file name
		inFile.open(inFileName.c_str());
	}
}

void ReadData(ifstream& inFile, int& numRows, int& numCols, BitArray Array1, BitArray Array2)
{
	int bit;

	inFile >> numRows;  // read number of rows
	inFile.ignore(INT_MAX, '\n');  // ignore characters until newline
	inFile >> numCols;  // read number of columns
	inFile.ignore(INT_MAX, '\n');

	inFile >> bit;  // initial read
	while (inFile)  // while input file stream is not in the fail state
	{
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				Array1[row][col] = bit;
				inFile >> bit;
			}
		}  // store first input array

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				Array2[row][col] = bit;
				inFile >> bit;
			}
		}  // store second input array
	}
}

void PrintInputArrays(int& numRows, int& numCols, BitArray Array1, BitArray Array2)
{
	int width;
	width = 2*numCols;  // establish width for header as two times the number of columns

	cout << "Initial values of the arrays processed" << endl;
	cout << string(38, '-') << endl;
	cout << left << setw(width) << "Array 1" << "    " << setw(width) << "Array 2" << endl;
	cout << setw(width) << string(7, '-') << "    " << setw(width) << string(7, '-') << endl;

	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			cout << Array1[row][col] << ' ';
		}  // output first input array
		cout << "    ";
		for (int col = 0; col < numCols; col++)
		{
			cout << Array2[row][col] << ' ';
		}  // output second input array
		cout << endl;
	}
	cout << endl;
}

void CalculateOutputArrays(int& numRows, int& numCols, BitArray Array1, BitArray Array2, BitArray orArray, BitArray andArray, BitArray xorArray)
{
	int bitSum;

	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			orArray[row][col] = 0;
			andArray[row][col] = 0;
			xorArray[row][col] = 0;  // initialize entries
			bitSum = Array1[row][col] + Array2[row][col];  // sum of corresponding bit in each input array
			switch (bitSum)
			{
				case 0:
					orArray[row][col] = 0;
					andArray[row][col] = 0;
					xorArray[row][col] = 0;
					break;
				case 1:
					orArray[row][col] = 1;
					andArray[row][col] = 0;
					xorArray[row][col] = 1;
					break;
				case 2:
					orArray[row][col] = 1;
					andArray[row][col] = 1;
					xorArray[row][col] = 0;
			}
		}
	}
}

void PrintOutputArrays(int& numRows, int& numCols, BitArray orArray, BitArray andArray, BitArray xorArray)
{
	int width;
	width = 2*numCols;

	cout << "OR, AND and XOR results" << endl;
	cout << string(23, '-') << endl;
	cout << left << setw(width) << "OR" << "    " << setw(width) << "AND" << "    " << setw(width) << "XOR" << endl;
	cout << setw(width) << "--" << "    " << setw(width) << "---" << "    " << setw(width) << "---" << endl;

	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			cout << orArray[row][col] << ' ';
		}  // output or array
		cout << "    ";
		for (int col = 0; col < numCols; col++)
		{
			cout << andArray[row][col] << ' ';
		}  // output and array
		cout << "    ";
		for (int col = 0; col < numCols; col++)
		{
			cout << xorArray[row][col] << ' ';
		}  // output xor array
		cout << endl;
	}
	cout << endl << endl;
}

void PrintIntegerEquivalents(int& numRows, int& numCols, BitArray orArray, BitArray andArray, BitArray xorArray)
{
	int base;
	int orResult;
	int andResult;
	int xorResult;  // declare variables for decimal equivalents

	cout << "Integer Equivalents for the rows" << endl
		 << "of the OR, AND and XOR arrays" << endl;
	cout << string(32, '-') << endl;
	cout << left << setw(8) << "OR" << setw(8) << "AND" << setw(8) << "XOR" << endl;
	cout << setw(8) << "--" << setw(8) << "---" << setw(8) << "---" << endl;

	for (int row = 0; row < numRows; row++)
	{
		base = 1;  // 2^0 = 1
		orResult = 0;
		andResult = 0;
		xorResult = 0;  // initialize variables
		
		for (int col = numCols - 1; col >= 0; col--)
		{
			orResult += base*orArray[row][col];
			andResult += base*andArray[row][col];
			xorResult += base*xorArray[row][col];
			base *= 2;
		}  // convert rows from decimal to binary
		cout << setw(8) << orResult << setw(8) << andResult << setw(8) << xorResult << endl;
	}
}
