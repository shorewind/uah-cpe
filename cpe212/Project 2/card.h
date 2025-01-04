//
// card.h -- CPE 212-01, Spring 2023 -- Project02 -- Classes
//
#include <string>
using namespace std;

#ifndef CARD_H  // guards
#define CARD_H

class Card  // Class modeling Card ADT
{
	private:
		int value;  // Card value: 2-10 for number cards, 11-14 for JQKA; 0 for unknown
		string color;  // Card color: "red", "black", or "unknown"
		char suit;  // Card suit: 'H' for hearts, 'D' for diamonds, 'C' for clubs, 'S' for spades or 'U' for unknown

	public:
		/******** Constructor Prototypes  *********/
		// Default constructor prototype: creates card with value v, color unknown, and suit U
		Card();
	
		// Parameterized constructor prototype: creates card with value v, color unknown, and suit U	
		Card(int initValue);

		/******** Transformer Prototypes *********/
		// SetValue prototype: Sets card value equal to v
		void SetValue(int v);
		// SetColor prototype: Sets color value equal to c
		void SetColor(string c);
		// SetSuit prototype:  Sets suit value equal to s
		void SetSuit(char s);

		/******** Observer Prototypes *********/
		// GetValue prototype: Returns current value of value
		int GetValue() const;
		// GetColor prototype: Returns current value of color
		string GetColor() const;
		// GetSuit prototype:  Returns current value of suit
		char GetSuit() const;
		// Description prototype: Polymorphic Function!!! (virtual keyword used)
		virtual string Description() const;  // Outputs card characteristics - value as a string
};

#endif
