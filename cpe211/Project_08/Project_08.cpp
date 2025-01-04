// ****************************************
// Program Title: Personal Records Reader
// Project File: Project_08.cpp
// Name: Esther Shore
// Course Section: CPE-211-02
// Lab Section: 1
// Due Date: 10/30/22
// program description: Reads person information from
// an input file and processes it into an output file
// ****************************************
#include <iostream>  // cout, cin
#include <fstream>  // ifstream, ofstream
#include <iomanip>  // setw()

using namespace std;

struct Person {
	string last_name;
	string first_name;
	string phone_number;
};

struct Address {
	string street;
	string city;
	string state;
	int zip_code;
};

// top-level struct containing Person and Address sub-structs
struct Record {
	Person person;
	Address address;
};

// function prototypes
void printHeader(ofstream& output_file);
void openInputFile(ifstream& input_file);
void openOutputFile(ofstream& output_file);
bool readInfo(ifstream& input_file, Record& record);
void printInfo(Record& record, ofstream& output_file);

int main()
{
	ifstream input_file;
	ofstream output_file;  // declare input and output file stream
	
	openInputFile(input_file);
	openOutputFile(output_file);  // open input and output file using functions
	
	Record record;  // declare instance of Record structure
	
	printHeader(output_file);
	
	cout << "Processing information. Please Wait...." << endl << endl;

	while (readInfo(input_file, record))  // while readInfo() returns true
	{
		printInfo(record, output_file);  // printInfo() for that entry
	}
			
	if (input_file.eof())  // if it made it to the end-of-file, output footer
	{
		output_file << setw(7) << string(5, '-') << setw(20) << string(9, '-')
					<< setw(15) << string(10, '-') << setw(20) << string(4, '-') << string(12, '-') << endl;
		cout << "Program has finished execution." << endl << endl;
	}

	return 0;
}

void printHeader(ofstream& output_file)
{
	output_file << left << setw(7) << "Entry" << setw(20) << "Last Name"
			    << setw(15) << "First Name" << setw(20) << "City" << "Phone Number" << endl;
	output_file << setw(7) << string(5, '-') << setw(20) << string(9, '-')
		   	    << setw(15) << string(10, '-') << setw(20) << string(4, '-') << string(12, '-') << endl;
}

void openInputFile(ifstream& input_file)
{
	string input_file_name;
	
	cout << endl;
	cout << "Enter the name of the input file: ";
	cin >> input_file_name;
	cout << input_file_name << endl << endl;  // query and echo print user input
	
	input_file.open(input_file_name.c_str());  // open input file
	
	while (input_file.fail())  // while the input file stream is in the fail state
	{
		cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> Input file failed to open properly!!" << endl;
		cout << "==> Attempted to open file: " << input_file_name << endl;
		cout << "==> Please try again..." << endl;
		cout << string(47, '*') << endl << endl;
		
		cout << "Enter the name of the input file: ";
		cin >> input_file_name;
		cout << input_file_name << endl << endl;  // continue asking for input file name
	
		input_file.open(input_file_name.c_str());
	}
}

void openOutputFile(ofstream& output_file)
{
	string output_file_name;
		
	cout << "Enter the name of the output file: ";
	cin >> output_file_name;
	cout << output_file_name << endl << endl;
	
	output_file.open(output_file_name.c_str());  // query and echo print user input

	while (output_file.fail())  // while the output file stream is in the fail state
	{
		cout << string(15, '*') << " File Open Error " << string(15, '*') << endl;
		cout << "==> Output file failed to open properly!!" << endl;
		cout << "==> Attempted to open file: " << output_file_name << endl;
		cout << "==> Please try again..." << endl;
		cout << string(47, '*') << endl << endl;
		
		cout << "Enter the name of the output file: ";
		cin >> output_file_name;
		cout << output_file_name << endl << endl;  // continue asking for output file name
	
		output_file.open(output_file_name.c_str());
	}
}

bool readInfo(ifstream& input_file, Record& record)
{	
	input_file >> record.person.phone_number >> record.person.last_name;
	input_file.ignore();  // ignore newline after extraction
	getline(input_file, record.address.street);
	getline(input_file, record.address.city);
	getline(input_file, record.address.state);  // getline() for members that could contain whitespace
	input_file >> record.address.zip_code >> record.person.first_name;
	input_file.ignore();
	
	if (input_file.fail())  // after reading, if the input file stream is in the fail state
	{
		if (!input_file.eof())  // if not at the end of input file stream
		{
			cout << string(15, '*') << " File Read Error " << string(15, '*') << endl;
			cout << "==> An error has occured while reading" << endl;
			cout << "==> the input file.  Error in file content." << endl;
			cout << "==> Terminating program!!!" << endl;
			cout << string(47, '*') << endl << endl;			
		}
		return false;
	}
	else {
		return true;
	}
}

void printInfo(Record& record, ofstream& output_file)
{
	static int entry = 0;  // initialize static variable for entry number
	
	entry++;  // increment entry count by 1 each time function is called
	
	output_file << left << setw(7) << entry << setw(20) << record.person.last_name << setw(15) << record.person.first_name
		 << setw(20) << record.address.city << record.person.phone_number << endl;  // write output entry
}
