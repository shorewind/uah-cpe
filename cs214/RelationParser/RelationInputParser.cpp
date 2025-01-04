//===================================================================================
// CS214 Relation Data Parser C++
// File: RelationInputParser.cpp
//
// Author: Mr. Kevin Preston
// Date: July 2021
//===================================================================================

#include "RelationInputParser.h"

using namespace std;

//------------------------------------------
// Default constructor
//------------------------------------------
RelationDataParser::RelationDataParser()
{
}

//------------------------------------------
// Destructor
//------------------------------------------
RelationDataParser::~RelationDataParser()
{
}

//------------------------------------------
// Get the singleton instance of this class
//------------------------------------------
RelationDataParser *RelationDataParser::getInstance()
{
	static RelationDataParser *theInstance = NULL;
	if(theInstance == NULL)
	{
		theInstance = new RelationDataParser();
	}
	return theInstance;
}

//------------------------------------------
// Initiaize the data parser with data file name
//------------------------------------------
void RelationDataParser::initDataParser(char *filename)
{
	char line[128];
    int i=0; //Counter for the element 
	
	strcpy_s(m_sFileName, strlen(filename) + 1, filename); 
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in); // Open the data file

    for (int i=0; i<10; i++)
		for (int j=0; j<10; j++)
			m_bElements[i][j] = 0; 
			
	if(inFile->is_open())
	{
		// Get the basic information
		while(getNextLine(line, 127))
		{
			if(strcmp(line, "<SETSIZE>") == 0)
			{
				getNextLine(line, 127); // Get the order of the set S. 
				m_iSetSize = int (atof(line));
			}
			else if(strcmp(line, "<ELEMENT>") == 0)
			{
				getNextLine(line, 127); // Get ELEMENT of the set S.
				m_sElements[i] = line;
				i++; //May want to check that the number of elements does not exceed the order of the set (m_iSetSize).
			}
			else if(strcmp(line, "<X>") == 0)
			{
				getNextLine(line, 127); 
				m_sX = line;
			}
			else if(strcmp(line, "<Y>") == 0)
			{
				// I have the values for the ordered pair. I need to translate that to an element in the boolean
				// matrix of the relation. 
				getNextLine(line, 127); // Get y
				m_sY = line;
				m_bElements[getOrder(m_sX)][getOrder(m_sY)] = 1;
			}
			
		}
		inFile->close();
	}
	else
	{
		printf("***** FAILED TO OPEN THE DATA FILE ***** \n");
		printf("You will not be able to read simulation data.\n");
	}
}


int RelationDataParser::getOrder(string X)
{
	for (int i = 0; i < 10; i++)
		if (m_sElements[i] == X) return i;
	return -1; // If the element is not found send a negative value. 

} // End getOrder 


//-------------------------------------------------------------------
// Return the value of the relation of the boolean matrix
//-------------------------------------------------------------------
bool RelationDataParser::getRelationElement(int X, int Y)
{	
	return m_bElements[X][Y]; // 
}

int RelationDataParser::getRelationSize()
{
	return m_iSetSize;
}


string RelationDataParser::getElement(int X)
{
	return m_sElements[X];
}

//------------------------------------------------
// Function: getNextLine()
// Purpose: Reads lines from a file and places
//   them in buffer, removing any leading white
//   space.  Skips blank lines. Ignors comment
//   lines starting with <!-- and ending with -->
//   
// Args:  buffer -- char array to read line into.
//        n -- length of buffer.
// Returns: True if a line was successfully read,
//    false if the end of file was encountered.
// Notes: Function provided by instructor.
// Author: Dr. Coleman that was not changed by Mr. Preston
//------------------------------------------------
bool RelationDataParser::getNextLine(char *buffer, int n)
{
	bool    done = false;
	char    tempBuf[128];
	char	*temp;
	while (!done)
	{
		inFile->getline(tempBuf, n); // Read a line from the file

		if (inFile->good())          // If a line was successfully read check it
		{
			if (strlen(tempBuf) == 0)     // Skip any blank lines
				continue;
			else if (strncmp(tempBuf, "<!--", 4) == 0) // Skip comment lines
				continue;
			else done = true;    // Got a valid data line so return with this line
		}
		else
		{
			strcpy(buffer, "");  // Clear the buffer array
			return false;        // Flag end of file
		}
	} // end while
	// Remove white space from end of string
	temp = &tempBuf[strlen(tempBuf)]; // point to closing \0
	temp--; // back up 1 space
	while (isspace(*temp))
	{
		*temp = '\0'; // Make it another NULL terminator
		temp--;  // Back up 1 char
	}
	// Remove white space from front of string
	temp = tempBuf;
	while (isspace(*temp)) temp++; // Skip leading white space
	// Copy remainder of string into the buffer
	strcpy(buffer, temp);
	return true;  // Flag a successful read
}
