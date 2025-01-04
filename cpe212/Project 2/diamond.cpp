#include "diamond.h"

Diamond::Diamond(int v) : RedCard(v)  // derived class constructor with constructor initializer
{
	// creates a red card with value v and suit D
	SetSuit('D');
}

string Diamond::Description() const
{
	// concatenate suit to redcard description
	return RedCard::Description() + ", Suit = " + GetSuit();
}
