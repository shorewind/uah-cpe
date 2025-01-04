// ****************************************
// Program Title: Password Generator
// Project File: Project_04.cpp
// Name: Esther Shore
// Course Section: CPE-211-02
// Lab Section: 1
// Due Date: 09/18/22
// program description: Generates a password
// based on name and word inputs from user.
// ****************************************
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	string name;  // declare name and word variables
	string word1;
	string word2;
	string word3;
	
	int length1;  // length of each word
	int length2;
	int length3;
	double avg_length;
	
	int space_index;  // declare variable for the index of the space character
	char initial1;  // first initial of name
	char initial2;  // last initial of name
	char special0;  // special character variables
	char special1;
	char special2;
	char special3;
	
	string special;  // declaration of variable to hold special characters
	int spec_len;  // length of special character string variable
	
	cout << '\n' << string(60, '*') << endl;
	cout << setw(40) << "Password Generator" << endl;
	cout << string(60, '*') << endl;  // output header
	
	// query the user for inputs
	cout << "Enter user's first and last names separated by a space: ";
	getline(cin, name);  // get entire line of input as name
	cout << "\nname = " << name << endl << endl;  // echo print name
	
	cout << "Enter the first word: ";
	cin >> word1;
	cout << "\nfirst word = " << word1 << endl << endl;  // echo print first word
	
	cout << "Enter the second word: ";
	cin >> word2;
	cout << "\nsecond word = " << word2 << endl << endl;  // echo print second word

	cout << "Enter the third word: ";
	cin >> word3;
	cout << "\nthird word = " << word3 << endl << endl;  // echo print third word
	
	length1 = word1.length();  // assign word length variables
	length2 = word2.length();
	length3 = word3.length();
	
	avg_length = (length1 + length2 + length3) / 3.0;  // assign average length using floating point division
	
	cout << string(60, '*') << endl;  // output three column table consisting of word#, length, and word
	cout << left << setw(8) << "Word#" << setw(10) << "Length" << setw(20) << "Word" << endl;
	cout << setw(8) << string(5, '-') << setw(10) << string(6, '-') << setw(20) << string(4, '-') << endl;
	cout << setw(8) << '1' << setw(10) << length1 << setw(20) << word1 << endl;
	cout << setw(8) << '2' << setw(10) << length2 << setw(20) << word2 << endl;
	cout << setw(8) << '3' << setw(10) << length3 << setw(20) << word3 << endl;
	cout << setw(8) << string(5, '-') << setw(10) << string(6, '-') << setw(20) << string(4, '-') << endl << endl;

	// output average word length to two decimal places
	cout << "Average word length = " << fixed << setprecision(2) << avg_length << endl << endl;
	

	special = "!@#$%^&*(){}[]?";  // assign special character string
	spec_len = special.length();  // assign special character string length
	
	space_index = name.find(' ');  // find index of the space in the full name
	initial1 = name.at(0);  // first initial is the first character
	initial2 = name.at(space_index + 1);  // last initial is the character after the space
	special0 = special.at(name.length() % spec_len);
	special1 = special.at(length1 % spec_len);
	special2 = special.at(length2 % spec_len);
	special3 = special.at(length3 % spec_len);
	
	cout << "password = " << initial1 << initial2 << name.length() << special0;
	cout << word1.at(0) << word1.at(length1 - 1) << length1 << special1;  // first character of word at index 0
	cout << word2.at(0) << word2.at(length2 - 1) << length2 << special2;  // last character of word at index length - 1
	cout << word3.at(0) << word3.at(length3 - 1) << length3 << special3 << endl;  // output sequentially onto same line
	cout << string(60, '*') << endl << endl;
	
	return 0;
}
