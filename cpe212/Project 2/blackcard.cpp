#include "blackcard.h"

BlackCard::BlackCard(int v) : Card(v)  // derived class constructor with constructor initializer
{
	// creates a black card with value v and unknown suit
	SetColor("black");
}

string BlackCard::Description() const
{
	// concatenate color to card description
	return Card::Description() + ", Color = " + GetColor();
}
