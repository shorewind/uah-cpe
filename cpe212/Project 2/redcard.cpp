#include "redcard.h"

RedCard::RedCard(int v) : Card(v)  // derived class constructor with constructor initializer
{
	// creates a red card with value v and unknown suit
	SetColor("red");
}

string RedCard::Description() const
{
	// concatenate color to card description
	return Card::Description() + ", Color = " + GetColor();
}
