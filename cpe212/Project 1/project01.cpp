// CPE212 Project 01, 1-22-23
#include <iostream>
#include <fstream>
#include <string>

void LoadImage(const string imagefile, int image[MAXROWS][MAXCOLS])
{
	ifstream inputfile;  // declare input file stream
	int bit;  // declare bit variable for each 0 or 1 read
	
	inputfile.open(imagefile.c_str());  // open file stream
	inputfile.ignore(100, '\n');  // ignore until newline character to skip string on first line
	inputfile >> bit;  // initial read

	while (!inputfile.eof())  // while the end-of-file has not been reached 
	{
		for (int row = 0; row < MAXROWS; row++)
		{
			for (int col = 0; col < MAXCOLS; col++)
			{
				image[row][col] = bit;  // insert bit into array
				inputfile >> bit;  // extract next bit	
			}
		}
	}
}

void FlipHorizontal(int image[MAXROWS][MAXCOLS])
{
	int newCol;  // declare new column index
	int imageHflip[MAXROWS][MAXCOLS];  // declare temp horizontally flipped matrix

	for (int row = 0; row < MAXROWS; row++)  // for each row
	{
		newCol = 0;  // initialize new column index
		for (int col = MAXCOLS - 1; col >= 0; col--)  // iterate through columns backwards
		{
			imageHflip[row][newCol] = image[row][col];  // swap rows
			newCol++;  // increment new column index
		}
	}
	// reassign flipped values to original matrix
	for (int row = 0; row < MAXROWS; row++)
	{
		for (int col = 0; col < MAXCOLS; col++)
		{
			image[row][col] = imageHflip[row][col];
		}
	}
}
 
void FlipVertical(int image[MAXROWS][MAXCOLS])
{
	int newRow;  // declare new row index
	int imageVflip[MAXROWS][MAXCOLS];  // declare temp vertically flipped matrix
	
	for (int col = 0; col < MAXCOLS; col++)  // for each column
	{
		newRow = 0;  // initalize new row index
		for (int row = MAXROWS - 1; row >= 0; row--)  // iterature through rows backwards
		{
			imageVflip[newRow][col] = image[row][col];  // swap rows
			newRow++;  // increment new row index
		}
	}
	// reassign flipped values to original matrix
	for (int row = 0; row < MAXROWS; row++)
	{
		for (int col = 0; col < MAXCOLS; col++)
		{
			image[row][col] = imageVflip[row][col];
		}
	}
}
 
void RotateCW(int image[MAXROWS][MAXCOLS])
{
	Transpose(image);  // taking the transpose
	FlipHorizontal(image);  // then flipping horizontally
}

void RotateCCW(int image[MAXROWS][MAXCOLS])
{
	Transpose(image);  // taking transpose
	FlipVertical(image);  // then flipping vertically
}
 
void Transpose(int image[MAXROWS][MAXCOLS])
{
	int imageTpose[MAXROWS][MAXCOLS];  // declare temp transpose matrix

	for (int row = 0; row < MAXROWS; row++)
	{
		for (int col = 0; col < MAXCOLS; col++)
		{
			imageTpose[col][row] = image[row][col];  // swap rows and columns
		}
	}
	// reassign new transpose values to original matrix
	for (int row = 0; row < MAXROWS; row++)
	{
		for (int col = 0; col < MAXCOLS; col++)
		{
			image[row][col] = imageTpose[row][col];
		}
	}
}
