// ****************************************
// Program Title: Grade Processor
// Project File: Project_11.cpp
// Name: Esther Shore
// Course Section: CPE-211-02
// Lab Section: 1
// Due Date: 12/04/22
// Program Description: Computes averages and
// creates a histogram of grades
// ****************************************
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
	ifstream inFile;
	double numScores;
	string inFileName;
	string firstName;
	string lastName;
	double score;
	double average;
	double highAverage;
	double lowAverage;
	double classAverage;
	char grade;
	int numEntries = 0;
	double sumAverages = 0;
	int aCount = 0;
	int bCount = 0;
	int cCount = 0;
	int dCount = 0;
	int fCount = 0;
	
	cout << endl;
	cout << "Enter the name of the input file: ";
	cin >> inFileName;
	
	inFile.open(inFileName.c_str());  // open file
	cout << inFileName << endl << endl;

	while (inFile.fail())  // if the file did not open successfully and the file stream is in the fail state
	{
		cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> Input file failed to open properly!!\n";
		cout << "==> Attempted to open file: " << inFileName << endl;
		cout << string(47, '*') << endl << endl;
		inFile.clear();
		
		cout << "Try Again..." << endl << endl;
		
		cout << "Enter the name of the input file: ";
		cin >> inFileName;

		inFile.open(inFileName.c_str());  // open file
		cout << inFileName << endl << endl;
	}
	inFile >> numScores;  // priming read

	if (inFile.eof())  // if file is empty, end-of-file is reached with previous I/O operation
	{
		cout << string(16, '*') << " File Is Empty " << string(16, '*') << endl;
		cout << "==> Input file is empty" << endl;
		cout << "==> No information to process" << endl;
		cout << string(47, '*') << endl << endl;
		return 1;
	}
	
	cout << left << fixed << setprecision(2);
	cout << setw(4) << '#' << setw(15) << "Last"
		 << setw(10) << "First" << setw(9) << "Average" << "Grade" << endl;
	cout << setw(4) << '-' << setw(15) << "----"
		 << setw(10) << "-----" << setw(9) << "-------" << "-----" << endl;
	
	highAverage = 0;
	lowAverage = 100;
	
	while (!inFile.eof())
	{

		inFile >> lastName;
		inFile >> firstName;
		lastName = lastName.substr(0, 12);
		firstName = firstName.substr(0, 7);
		
		int i = 0;
		double sumScores = 0;
		while (i < numScores)
		{
			i++;
			inFile >> score;
			sumScores += score;
		}
		
		if (!inFile.fail())
		{
			numEntries++;
			average = sumScores / numScores;
			sumAverages += average;
			
			if (average >= 90)
			{
				grade = 'A';
				aCount++;
			}
			else if (average >= 80)
			{
				grade = 'B';
				bCount++;
			}
			else if (average >= 70)
			{
				grade = 'C';
				cCount++;
			}
			else if (average >= 60)
			{
				grade = 'D';
				dCount++;
			}
			else if (average < 60)
			{
				grade = 'F';
				fCount++;
			}
			
			cout << left << fixed << setprecision(2);
			cout << setw(4) << numEntries << setw(15) << lastName
				 << setw(10) << firstName << setw(9) << average << grade << endl;
			classAverage = sumAverages / numEntries;
			
			if (average > highAverage)
			{
				highAverage = average;
			}
			if (average < lowAverage)
			{
				lowAverage = average;
			}
		}
	}
	
	cout << fixed << setprecision(2) << endl;
	cout << setfill('.') << setw(25) << "Class Average" << classAverage << setfill(' ') << endl;
	cout << setfill('.') << setw(25) << "Highest Average" << highAverage << setfill(' ') << endl;
	cout << setfill('.') << setw(25) << "Lowest Average" << lowAverage << setfill(' ') << endl << endl;

	cout << right << setw(18) << "Grade Histogram"  << endl; 
	cout << "           1         2" << endl; 
	cout << "  12345678901234567890" << endl;
	cout << "A:" << string(aCount, '*') << endl;
	cout << "B:" << string(bCount, '*') << endl;
	cout << "C:" << string(cCount, '*') << endl;
	cout << "D:" << string(dCount, '*') << endl;
	cout << "F:" << string(fCount, '*') << endl << endl;

	inFile.close();
	return 0;
}
