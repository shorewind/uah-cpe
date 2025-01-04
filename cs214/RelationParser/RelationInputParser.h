//===================================================================================
// CS214 Relation Data Parser C++
// File: RelationInputParser.h
//
// Author: Mr. Kevin Preston
// Date: July 2021
//===================================================================================
#include <fstream>

using namespace std;

class RelationDataParser
{
	private:
		char m_sFileName[64];
		ifstream	*inFile;	     // Relation Input file

		
		// Relation data elements
		int m_iSetSize;    // Order of the input relation

		string m_sX; 
		string m_sY;
		string m_sElements[10];
		
		char m_cElements[10];  // The elements that make up the set of the relation. 
		bool m_bElements[10][10]; // The matrix of the relation. 
		
		RelationDataParser();						// Default constructor for singleton
		bool getNextLine(char *buffer, int n);		// Read a line from the data file

	public:
		static RelationDataParser *getInstance();			// Get the singleton instance of this class
		~RelationDataParser();						// Destructor
		void initDataParser(char *filename);		// Initiaize the data parser with data file name
	
		int getRelationSize();  //How many elements are in the set S i.e., |S|?
		
		int getOrder(string X); //Find the string in the set S and return where in the list it was found. 

		bool getRelationElement(int X, int Y); //Get the value of the matrix of the relation. 

		string getElement(int X); //Given the order of the element return the element from set S. 
};