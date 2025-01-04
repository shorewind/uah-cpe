#include "heart.h"

Heart::Heart(int v) : RedCard(v)  // derived class constructor with constructor initializer
{
	// creates a red card with value v and suit H
	SetSuit('H');
}

string Heart::Description() const
{
	// concatenate suit to redcard description
	return RedCard::Description() + ", Suit = " + GetSuit();
}
