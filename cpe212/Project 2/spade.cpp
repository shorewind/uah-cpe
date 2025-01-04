#include "spade.h"

Spade::Spade(int v) : BlackCard(v)  // derived class constructor with constructor initializer
{
	// creates a black card with value v and suit S
	SetSuit('S');
}

string Spade::Description() const
{
	// concatenate suit to blackcard description
	return BlackCard::Description() + ", Suit = " + GetSuit();
}
