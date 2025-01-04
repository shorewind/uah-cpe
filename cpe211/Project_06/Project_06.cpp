// ****************************************
// Program Title: Project 6
// Project File: Project_06.cpp
// Name: Esther Shore
// Course Section: CPE-211-02
// Lab Section: 1
// Due Date: 10/04/22
// program description: Description of
// What the program does.
// ****************************************
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>  // isalpha(), isdigit()

using namespace std;

int main(int argc, char *argv[])
{
	string inFileName;
	string outFileName;  // declare file name variables
	ifstream inFile;
	ofstream outFile;  // declare input and output file streams
	char char1;  // declare character variable
	
	int line = 0;
	int letters = 0;
	int digits = 0;
	int other = 0;
	int total = 0;  // declare and initialize counter variables
	
	int totalLetters = 0;
	int totalDigits = 0;
	int totalOther = 0;
	int totalChar = 0;  // declare and initialize totals
	
	double percentLetters;
	double percentDigits;
	double percentOther;  // declare percentages as type double
	
	// command line argument error
	if(argc != 3)  // if there are not three command line arguments given (exe, inFile, outFile)
	{
		cout << endl;
		cout << string(9, '*') << " Command Line Argument Error " << string(9, '*') << endl;
		cout << "==> Incorrect number of Command Line Arguments!" << endl;
		cout << "==> Command for running the program is:" << endl;
		cout << "==> ./Project_06 inputFileName outputFileName" << endl;
		cout << string(47, '*') << endl << endl;
		return 1;
	}
	
	cout << endl;
	cout << "Opening the input file..." << endl << endl;
	
	inFileName = argv[1];  // assign the argument at index 1 to inFileName
	inFile.open(inFileName.c_str());  // open inFileName as the input file stream inFile
	
	// input file open error
	while(inFile.fail())  // while the input file stream is in the fail state
	{
		cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> Input file failed to open properly!!" << endl;
		cout << "==> Attempted to open file: " << inFileName << endl;
		cout << "==> Please try again..." << endl;
		cout << string(47, '*') << endl << endl;
		
		inFile.clear();  // clear the input file stream
				
		cout << "Enter in the name of the input file: ";  // prompt user for another input file
		cin >> inFileName;
		cout << inFileName << endl << endl;  // echo print output file name
		inFile.open(inFileName.c_str());  // try opening, continue loop if failed
	}
	
	cout << "Opening the output file..." << endl << endl;
	
	outFileName = argv[2];  // assign the argument at index 2 to outFileName
	outFile.open(outFileName.c_str());  // open outFileName as the output file stream outFile
	
	// output file open error
	while(outFile.fail())  // while the output file stream is in the fail state
	{
		cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> Output file failed to open properly!!" << endl;
		cout << "==> Attempted to open file: " << outFileName << endl;
		cout << "==> Please try again..." << endl;
		cout << string(47, '*') << endl << endl;
		
		outFile.clear();  // clear the output file stream
				
		cout << "Enter in the name of the output file: ";  // prompt user for another output file
		cin >> outFileName;
		cout << outFileName << endl << endl;  // echo print output file name
		outFile.open(outFileName.c_str());  // try opening, continue looping if failed
	}
	
	inFile.get(char1);  // priming read, get first character from input file stream
	
	// input file is empty error
	if(inFile.fail())  // if the input file stream is in the fail state after the priming read
	{
		cout << string(13, '*') << " Input File Is Empty " << string(13, '*') << endl;
		cout << "==> The input file is empty." << endl;
		cout << "==> Terminating the program." << endl;
		cout << string(47, '*') << endl << endl;
		return 1;
	}
	
	// write header to output file stream
	outFile << left << setw(15) << "Line Number" << setw(10) << "Letters"
		 << setw(10) << "Digits" << setw(10) << "Other" << "Total" << endl;
	outFile << setw(15) << string(11, '-') << setw(10) << string(7, '-')
		 << setw(10) << string(6, '-') << setw(10) << string(5, '-') << string(5, '-') << endl;;
	
	// read lines and characters, adding to totals
	while(!inFile.eof())  // while the end of file is not reached	
	{	
		line = line + 1;  // add one to line number
		while(char1 != '\n')  // while the character is not the newline character
		{
			if(isdigit(char1))
				digits = digits + 1;
			else if(isalpha(char1))
				letters = letters + 1;
			else
				other = other + 1;
			inFile.get(char1);  // get next character
		}
		other = other + 1;  // broke out of inner while loop, therefore newline character was reached
		total = digits + letters + other;  // add to total characters for that line
		
		totalOther = totalOther + other;
		totalLetters = totalLetters + letters;
		totalDigits = totalDigits + digits;
		totalChar = totalChar + total;  // add to totals for the entire file
		
		// write results for the current line to output file stream
		outFile << setw(15) << line << setw(10) << letters
			 << setw(10) << digits << setw(10) << other << total << endl;
		
		letters = 0;
		digits = 0;
		other = 0;
		total = 0;  // reset line totals to zero

		inFile.get(char1);  // get next character (on new line)
	}

	// output footer with totals
	outFile << string(50, '-') << endl;
	outFile << left << setw(15) << "Totals" << setw(10) << totalLetters
		 << setw(10) << totalDigits << setw(10) << totalOther << totalChar << endl;
	
	// calculate percentages
	percentLetters = totalLetters / float(totalChar) * 100;
	percentDigits = totalDigits / float(totalChar) * 100;
	percentOther = totalOther / float(totalChar) * 100;
	
	// output percentages to two decimal places
	outFile << fixed << setprecision(2);
	outFile << left << setw(15) << "Percent" << setw(10) << percentLetters
			<< setw(10) << percentDigits << percentOther << endl << endl;
	
	inFile.close();
	outFile.close();  // close file streams
	return 0;
}
