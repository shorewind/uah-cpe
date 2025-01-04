//
// stack.cpp   2023 Spring CPE 212 -- Project03 -- Stacks
//
#include <iostream>
#include <new>
#include "stack.h"

using namespace std;

// Attempts to increase size of stack array to 2*num and then push n onto stack
// If unable to resize, throw StackFull exception
void Stack::Resize(int n)
{
	num = 2*num;
}

// Parameterized constructor dynamically allocates an empty stack array  
// that may hold no more than n elements and initializes other private variables
Stack::Stack(int n)
{
	num = n;
	top = -1;
	array = new int[n];
}

// Destructor deallocates all dynamically-allocated memory
// associated with the object
Stack::~Stack()
{
	delete[] array;
}

// Pushes integer n onto top of stack.  If stack is full, attempts to
// resize stack and then push n.  If unable to resize, throws StackFull
void Stack::Push(int n)
{
	if (IsFull())
	{
		Resize(n);
	}
	top++;
	array[top] = n;
}

// Removes top integer from stack
// If stack is empty, throws StackEmpty exception
void Stack::Pop()
{
	if (IsEmpty())
	{
		throw StackEmpty();
	}
	top--;
}

// Returns true if stack is empty; false otherwise
bool Stack::IsEmpty() const
{
	return (top == -1);
}

// Returns true if stack is full; false otherwise
bool Stack::IsFull() const
{
	return (top == (num - 1));
}

// Removes all items from stack leaving an empty, but usable stack with capacity num
// If stack is already empty, MakeEmpty() does nothing
void Stack::MakeEmpty()
{
	top= -1;
}

// Returns value of top integer on stack WITHOUT modifying the stack
// If stack is empty, throws StackEmpty exception
int Stack::Top() const
{
	if (IsEmpty())
	{
		throw StackEmpty();
	}
	return array[top];
}

// Returns number of items on stack WITHOUT modifying the stack
int Stack::Size() const
{
	return top + 1;
}

// Returns value of largest integer on stack WITHOUT modifying the stack
// If stack is empty, throws StackEmpty
int Stack::Max() const
{
	if (IsEmpty())
	{
		throw StackEmpty();
	}
	
	int max = Top();
	
	for (int j = 0; j < top; j++)
	{
		if (array[j] > max)
		{
			max = array[j];
		}
	}
	return max;
}

// Returns value of smallest integer on stack WITHOUT modifying the stack
// If stack is empty, throws StackEmpty
int Stack::Min() const
{
	int min = Top();
	
	if (IsEmpty())
	{
		throw StackEmpty();
	}

	for (int j = 0; j < top; j++)
	{
		if (array[j] < min)
		{
			min = array[j];
		}
	}
	return min;
}

// Returns stack value n levels down from top of stack. Peek(0) = Top()
// If position n does not exist, throws StackInvalidPeek
int Stack::Peek(unsigned int n) const
{
	int index = top - n;
	if (index < 0 || index > top)
	{
		throw StackInvalidPeek();
	}
	return array[index];
}

// Returns total num of elements that maybe stored in stack array
int Stack::Capacity() const
{
	return num;
}
