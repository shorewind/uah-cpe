// ****************************************
// Program Title: Simulations
// Project File: Project_07.cpp
// Name: Esther Shore
// Course Section: CPE-211-02
// Lab Section: 1
// Due Date: 10/18/22
// program description: Approximates pi using Monte Carlo Method,
// simulates coin flips and die tosses, outputting the percent of each result
// ****************************************
#include <iostream>
#include <string>
#include <cstdlib>  // srand, rand, RAND_MAX
#include <climits> // INT_MAX
#include <iomanip> // setprecision
#include <cmath> // sqrt, pow

using namespace std;

void printMenu();
int obtainInt();
void calculatePi();
void coinFlip();
void dieToss();  // function prototypes

int main()
{
	int seed;
	int choice;
	
	cout << "\nEnter in the seed(integer > 0) for the random number generator: ";
	cin >> seed;
	cout << seed << endl << endl;
	srand(seed);
	
	do {
		printMenu();
		choice = obtainInt();
		switch(choice) {
			case 1:
				calculatePi();
				break;
			case 2:
				coinFlip();
				break;
			case 3:
				dieToss();
				break;
			case 4:
				cout << "Exit selected.  Exiting the program now..." << endl << endl;
				break;
			default:  // if integer not 1, 2, 3, or 4
				cout << string(15, '*') << " Invalid Integer " << string(15, '*') << endl;
				cout << "==> Invalid integer entered." << endl;
				cout << "==> Please try again..." << endl;
				cout << string(47, '*') << endl << endl;
		}
	}
	while (choice!= 4);  // while not exit
	
	return 0;
}

void printMenu()
{
	cout << string(24, '*') << endl;
	cout << string(5, '*') << " Menu Options " << string(5, '*') << endl;
	cout << string(24, '*') << endl;
	cout << "1) Approximate PI" << endl;
	cout << "2) Flip a fair coin" << endl;
	cout << "3) Toss a fair 5-sided die" << endl;
	cout << "4) Exit" << endl;
	cout << string(24, '*') << endl << endl;
}

int obtainInt()  // get selection from user and process selection
{
	int selection;
	char invalid_selection;
	
	cout << "Enter your choice: ";
	cin >> selection;
	
	while (cin.fail()) {  // selection is not an int, then cin enters fail state
		cin.clear();  // clear error flag
		cin >> invalid_selection;  // get invalid selection
		cout << invalid_selection << endl << endl;  // echo print invalid selection
		cin.ignore(INT_MAX, '\n');  // ignore rest of input
		cout << string(14, '*') << " Invalid Character " << string(14, '*') << endl;
		cout << "==> Invalid character(s) entered." << endl;
		cout << "==> Please try again..." << endl;
		cout << string(47, '*') << endl << endl;
		printMenu();
		cout << "Enter your choice: ";
		cin >> selection;  // repeat query
	}
			
	cin.ignore(INT_MAX, '\n');  // ignore rest of input
	cout << selection << endl << endl;  // echo print integer
	
	return selection;
}

void calculatePi()
{
	double x_coord;
	double y_coord;
	int iterations;
	int count_inside;  // declare variable counter for number of coordinates inside circle
	double pi_approx;
	
	count_inside = 0;  // initialize counter to zero
	
	cout << "Monte Carlo Method for finding PI has been selected" << endl << endl;
	
	cout << "Number of iterations: ";
	cin >> iterations;
	cout << iterations << endl << endl;
	
	for (int i = 0; i < iterations; i++) {  // for each iteration
		x_coord = double(rand())/double(RAND_MAX);  // random num from 0 to 1
		y_coord = double(rand())/double(RAND_MAX);  // random num from 0 to 1
		if (sqrt(pow(x_coord, 2) + pow(y_coord, 2)) <= 1.0)  // if coordinate falls inside circle
			count_inside++;  // add one to counter
	}
	
	pi_approx = 4 * (count_inside / double(iterations));  // calculate approximation for pi
	
	cout << fixed << setprecision(6);
	cout << string(10, '*') << " Option 1: Calculating PI " << string(10, '*') << endl;
	cout << "For " << iterations << " iterations, pi is about " << pi_approx << endl;
	cout << string(46, '*') << endl << endl;
}

void coinFlip()
{
	int flips;
	double flip_value;  // random num from 0 to 1 representing coin flip
	int heads_count;  // declare variable counter for number of heads
	double heads_perc;
	double tails_perc;
	
	heads_count = 0;  // initialize counter to 0
	
	cout << "Flipping of a fair coin has been selected" << endl << endl;
	
	cout << "How many flips of the coin? ";
	cin >> flips;
	cout << flips << endl << endl;
	
	for (int i = 0; i < flips; i++) {  // for each coin flip
		flip_value = double(rand())/double(RAND_MAX);  // random num from 0 to 1
		if (flip_value > 0.5)
			heads_count++;  // if random number greater than 0.5, add one to head count
	}
	
	heads_perc = (heads_count / double(flips)) * 100;  // calculate heads percentage using floating point division
	tails_perc = 100 - heads_perc;  // tails percentage is the complement of the heads percentage
	
	cout << fixed << setprecision(4);
	cout << string(10, '*') << " Option 2: Flipping a Coin " << string(10, '*') << endl;
	cout << "For " << flips << " flips of a fair coin:" << endl;
	cout << "Heads percentage: " << heads_perc << endl;
	cout << "Tails percentage: " << tails_perc << endl;
	cout << string(47, '*') << endl << endl;
}

void dieToss()
{
	int rolls;
	double roll_value;  // random num from 0 to 1 representing dice roll
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int count4 = 0;
	int count5 = 0;  // declare and initialize counters to 0
	double percent1;
	double percent2;
	double percent3;
	double percent4;
	double percent5;
	
	cout << "Tossing of a fair 5-sided die has been selected" << endl << endl;
	
	cout << "How many times do you want to roll the die? ";
	cin >> rolls;
	cout << rolls << endl << endl;
	
	for (int i = 0; i < rolls; i++) {  // for each dice roll
		roll_value = double(rand())/double(RAND_MAX);  // random num from 0 to 1
		if (roll_value < 0.2)  // values representing side 1
			count1++;
		else if (0.2 <= roll_value && roll_value < 0.4)  // values representing side 2
			count2++;
		else if (0.4 <= roll_value && roll_value < 0.6)  // values representing side 3
			count3++;
		else if (0.6 <= roll_value && roll_value < 0.8)  // values representing side 4
			count4++;
		else  // else, side 5 came up
			count5++;  // add one to corresponding counter variable
	}
	
	percent1 = count1 / double(rolls) * 100;
	percent2 = count2 / double(rolls) * 100;
	percent3 = count3 / double(rolls) * 100;
	percent4 = count4 / double(rolls) * 100;
	percent5 = count5 / double(rolls) * 100;  // calculate percentages using floating point division
	
	cout << fixed << setprecision(4);
	cout << string(10, '*') << " Option 3: Tossing a Die " << string(10, '*') << endl;
	cout << "For " << rolls << " rolls of a fair die:" << endl;
	cout << "Side 1 percentage: " << percent1 << endl;
	cout << "Side 2 percentage: " << percent2 << endl;
	cout << "Side 3 percentage: " << percent3 << endl;
	cout << "Side 4 percentage: " << percent4 << endl;
	cout << "Side 5 percentage: " << percent5 << endl;
	cout << string(45, '*') << endl << endl;
}
