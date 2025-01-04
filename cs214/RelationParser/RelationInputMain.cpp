//===================================================================================
// CS214 Relation Inputs Parser C++
// File: RelationInputMain.cpp
//
// Author: Mr. Kevin Preston
// Date:  25-Sep-2021
//===================================================================================
//
// This is the main program that handles the:
//     - Read the input .xml file and build the object that is the boolean matrix of the relation.
//     - Print the information of the relation. 
// If there is ever a problem reading the input file change the input file so Parser can handle it. This is 
// based on Dr. Coleman's code for CS307 and CS499 project assignments. 
//
// The main and the RelationInputParser class are provided to the CS214 students. This was necessary 
// because this was more difficult for the students to parse the input files. 
//
// This zip file should contain this file, the RelationInputParser class and the four input files that contain the
// relations. 

#include <iostream>
#include "RelationInputParser.h"

using namespace std;
#define MAX_RELATIONS 4 // Range is 0 to MAX_RELATIONS

char  *inputfilename[MAX_RELATIONS]; // This is the array that contains all the input relation filenames. 

int    relationsize;    // The order of the set S i.e., |S|.
string relationelement; // The elements of the set S. Need to make them strings. 
bool   rvalue;          // The boolean value returned by accessing the matrix of the relation. 

void main()
{
	// Initialize the array with the files that contain all the relations to check. 
	inputfilename[0] = "Relation01.xml";
	inputfilename[1] = "Relation02.xml";
	inputfilename[2] = "Relation03.xml";
	inputfilename[3] = "Relation04.xml";
	

	// Loop through all the files. 

	for (int k = 0; k < MAX_RELATIONS; k++)
	{
		printf("\n*********************************************************\n");
		printf("*********************************************************\n");
		printf("\nThe input Relation File is: %s\n", inputfilename[k]);
		RelationDataParser *lsdp = RelationDataParser::getInstance();	// Get the singleton
		lsdp->initDataParser(inputfilename[k]);

		// Print size of the relation
		relationsize = lsdp->getRelationSize();
		printf("Set size is: %d\n \n", relationsize);

		// Print the relation elements. 
		printf("The set S contains: \n  {");

		for (int i = 0; i < relationsize - 1; i++)
		{
			relationelement = lsdp->getElement(i);
			printf("%s, ", relationelement.c_str());
		}
		relationelement = lsdp->getElement(relationsize - 1);
		printf("%s} \n\n", relationelement.c_str());

		// Print the Boolean matrix of the relation
		printf("\n The Boolean Matrix of the relation R is: \n\n");

		for (int i = 0; i < relationsize; i++)
		{
			for (int j = 0; j < relationsize; j++)
			{
				rvalue = lsdp->getRelationElement(i, j);
				printf(" %x ", rvalue);
			}
			printf("\n");
		}


		// Print the ordered pairs of the relation. Not a perfect printing (extra ,) but close enough. 
		printf("\nThe ordered pairs of the relation R: \n");
		printf("{ ");

		for (int i = 0; i < relationsize; i++)
		{
			for (int j = 0; j < relationsize; j++)
			{
				rvalue = lsdp->getRelationElement(i, j);
				if (rvalue)
				{
					relationelement = lsdp->getElement(i);
					printf("(%s, ", relationelement.c_str());
					relationelement = lsdp->getElement(j);
					printf("%s),  ", relationelement.c_str());
				}
			}
		}
		printf("} \n");

		//
		//Students should enter their code to check the relation after this point. 
		//

		printf("\nThe properties of the Relation R is as follows: \n\n");


	} // end for k loop for the input data files.
} // end main