#include "club.h"

Club::Club(int v) : BlackCard(v)  // derived class constructor with constructor initializer
{
	// creates a black card with value v and suit C
	SetSuit('C');
}

string Club::Description() const
{
	// concatenate suit to blackcard description
	return BlackCard::Description() + ", Suit = " + GetSuit();
}
