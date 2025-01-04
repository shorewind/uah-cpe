// ****************************************
// Program Title: Triangle Checker
// Project File: Project_05.cpp
// Name: Esther Shore
// Course Section: CPE-211-02
// Lab Section: 1
// Due Date: 09/25/22
// program description: Determines if the input file data forms a valid triangle.
// If so, outputs the type, area, and perimeter.
// Also, confirms whether the triangle type guess was correct or not.
// ****************************************
#include <iostream>  // cout, left, fixed, endl
#include <fstream>  // ifstream
#include <iomanip>  // setw, setfill, setprecision
#include <cmath>  // sqrt

using namespace std;

int main(int argc, char* argv[])
{
	string inFileName;
	ifstream inFile;  // establish input file stream
	char label;  // declare label: a, b, c, or ?
	double sideA;
	double sideB;
	double sideC;
	string guess;  // declare guess for type of triangle
	string type;  // declare actual type of triangle
	double s;  // declare s term in Heron's Formula for area
	double area;
	double perimeter;
	
	if (argc!= 2)  // if exactly two command line arguments are not given
	{
		cout << endl;
		cout << string(9, '*') << " Command Line Argument Error " << string(9, '*') << endl;
		cout << "==> Incorrect number of Command Line Arguments!\n";
		cout << "==> Command for running the program is:\n";
		cout << "==> ./Project_05 inputFileName\n";
		cout << string(47, '*') << endl << endl;
		return 1;
	}
	else
	{
		cout << '\n' << string(60, '*') << endl;
		cout << string(20, '*') << "  Triangle Checker  " << string(20, '*') << endl;
		cout << string(60, '*') << endl << endl;
		
		inFileName=argv[1];  // second command line argument given is the file name
		inFile.open(inFileName.c_str());  // open file
		cout << "Opening input file: " << inFileName << endl << endl;

		if(!inFile)  // if the file did not open successfully and the file stream is in the fail state
		{
			cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
			cout << "==> Input file failed to open properly!!\n";
			cout << "==> Attempted to open file: " << inFileName << endl;
			cout << "==> Terminating program!!!" << endl;
			cout << string(47, '*') << endl << endl;
			return 1;
		}
		else
		{
			cout << "Reading Values From Input File..." << endl << endl;
			inFile >> label;  // read first label
			
			if (inFile.eof())  // if file is empty, end-of-file is reached with previous I/O operation
			{
				cout << string(13, '*') << " Input File Is Empty " << string(13, '*') << endl;
				cout << "==> No Information in the input file." << endl;
				cout << "==> Terminating program now..." << endl;
				cout << string(47, '*') << endl << endl;
				return 1;
			}
			else
			{
				for(int i=0; i < 4; i++)  // loop four times, assign variables based on label read
				{
					if (label == 'a')
						inFile >> sideA;
					else if (label == 'b')
						inFile >> sideB;
					else if (label == 'c')
						inFile >> sideC;
					else if (label == '?')
						inFile >> guess;
					
					if (i != 3)
						inFile >> label;  // on last iteration, don't extract from input file stream
				}
	
				if (!inFile)  // if the file is in the fail state, file read error
				{
					cout << string(15, '*') << " File Read Error " << string(15, '*') << endl;
					cout << "==> Error reading data from input file." << endl;
					cout << "==> Terminating program now..." << endl;
					cout << string(47, '*') << endl << endl;
					return 1;
				}
				else
				{
					if (sideA < 0 || sideB < 0 || sideC < 0)  // if any of the sides are negative
					{
						cout << string(15, '*') << " File Data Error " << string(15, '*') << endl;
						cout << "==> Error: One or more side lengths are negative." << endl;
						cout << "==> Terminating program now..." << endl;
						cout << string(47, '*') << endl << endl;
						return 1;
					}
					else
					{
						cout << "Summary of Data Read..." << fixed << setprecision(2) << endl;
						cout << "Side A = " << sideA << endl
					 	  	 << "Side B = " << sideB << endl
					 		 << "Side C = " << sideC << endl
					 		 << "Guess  = " << guess << endl;  // echo print data read from input file
						cout << string(60, '*') << endl;
						
						cout << "Results From Data Read:" << endl;
						
						if ((sideA < sideB + sideC) && (sideB < sideA + sideC) && (sideC < sideA + sideB))  // if the sides form a valid triangle
						{
							if ((sideA == sideB) && (sideB == sideC))
								type = "equilateral";
							else if ((sideA == sideB) || (sideB == sideC) || (sideA == sideC))
								type = "isosceles";
							else
								type = "scalene";
							s = (sideA + sideB + sideC) / 2.0;  // use floating point division to determine the variable s in Heron's Formula
							area = sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));  // calculate and assign area value
							perimeter = sideA + sideB + sideC;  // calculate and assign perimeter value
							cout << left << setfill('.');  // align left and set fill spaces to .
							cout << setw(13) << "Type" << type << endl;
							cout << setw(13) << "Area" << area << endl;
							cout << setw(13) << "Perimeter" << perimeter << endl << endl;  // output results
						}
						else
						{
							type = "not-triangle";
							cout << left << setfill('.') << setw(13) << "Type" << type << endl << endl;  // no area or perimeter for not triangles
						}
						
						if (type == guess)  // if guess matches the actual triangle type
							cout << "Congratulations!  Triangle specified is correct" << endl;
						else
							cout << "Sorry! Triangle specified is incorrect" << endl;
						cout << string(60, '*') << endl << endl;
					}
				}
			}
			
		}
	}
	return 0;
}
