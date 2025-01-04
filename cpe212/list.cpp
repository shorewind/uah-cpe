//
// list.cpp -- 2023 Spring CPE 212 -- Project04 -- Lists
//
#include <iostream>
#include <new>
#include "list.h"

/***** Constructor and Destructor *****/
// Constructor sets state of list to empty
List::List()
{
	head = NULL;
	num = 0;
}          

// Destructor must deallocate all list nodes
List::~List()
{
	Node* current = head;
	while (current != NULL)
	{
		Node* next = current->next;
		delete current;
		current = next;
	}
	num = 0;
}

/***** Transformer Methods *****/
// Appends newword to the end of the current phrase 
// Error Handling: If list is full, throw ListFull object.
void List::Append(string newword)
{
	Node* newNode = new Node;
	newNode->word = newword;
	newNode->next = NULL;
	
	if (newNode == NULL)
	{
		throw ListFull();
	}
	else if (head == NULL)
	{
		head = newNode;
	}
	else
	{
		Node* current = head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = newNode;
	}
	num++;
}                  

// Inserts newword at position pos.
// Positions numbered starting with zero (0 <= pos <= num).
// Hint: pos == num ==> append
// Word previously at pos should now be at position pos+1
// Error Handling: If list is full, throws ListFull object
//                 If pos out of range, throws ListBadPosition object
void List::InsertAt(int pos, string newword)
{
	if (pos < 0 || pos > num)
	{
		throw ListBadPosition();
	}
	
	Node* newNode = new Node;
	newNode->word = newword;
	
	if (newNode == NULL)
	{
		throw ListFull();
	}
	else if (pos == 0)
	{
		newNode->next = head;
		head = newNode;
	}
	else
	{
		Node* current = head;
		for (int i = 0; i < pos - 1; i++)
		{
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
	num++;
}

// Deletes the first instance of someword if it is present.  
// Error Handling: If someword is not in list, throws ListNotFound object
void List::Delete(string someword)
{
	if (Find(someword) == false)
	{
		throw ListNotFound();
	}
	
	if (head->word == someword)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
		num--;
		return;
	}
	Node* current = head;
	while (current->next != NULL)
	{
		if (current->next->word == someword)
		{
			Node* temp = current->next;
			current->next = current->next->next;
			delete temp;
			num--;
			return;
		}
		current = current->next;
	}
	throw ListNotFound();
}

// Replaces the first instance of oldword with newword.  
// Error Handling: If oldword not found, throws ListNotFound object
void List::Replace(string oldword, string newword)
{
	if (Find(oldword) == false)
	{
		throw ListNotFound();
	}
	
	Node* current = head;
	while (current != NULL)
	{
		if (current->word == oldword)
		{
			current->word = newword;
			return;
		}
		current = current->next;
	}
}

/***** Observer Methods *****/
// Returns number of words in the list
// Error Handling: none
int List::Length() const
{
	return num;
}

// Returns true if someword is in list, false otherwise
// Error Handling: none
bool List::Find(string someword) const
{
	Node* current = head;
	while (current != NULL)
	{
		if (current->word == someword)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}
  