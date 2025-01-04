// ****************************************
// Program Title: Projectile Motion Calculator
// Project File: Project_03.cpp
// Name: Esther Shore
// Course Section: CPE-211-02
// Lab Section: 1
// Due Date: 09/09/22
// program description: Calculates value for
// projectile motion based on inputs.
// ****************************************
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

int main()
{
	cout << '\n' << string(30,'*') << endl;
	cout << string(5, '*') << " Projectile Motion" << endl;
	cout << string(30,'*') << endl << endl;  // program header and title
	
	const double g = 9.80665;  // acceleration due to gravity (m/s^2)
	const double PI = 3.14159265;  // shortened value of pi
	double velocity;
	double angle;  // declare input variables
	
	cout << "Enter in the initial velocity(in meters/sec): ";
	cin >> velocity;  // prompt the user for input
	cout << velocity << endl << endl;  // echo print
	
	cout << "Enter in the starting angle(in degrees): ";
	cin >> angle;  // prompt the user for input
	cout << angle << endl << endl;  // echo print
	angle = angle * PI / 180.0;  // convert angle from degrees to radians
		
	double max_h_time;
	double max_d_time;
	double max_height;
	double max_distance;
	double max_range;  // declare output variables
	
	max_h_time = (velocity * sin(angle)) / g;
	max_d_time = (2 * velocity * sin(angle)) / g;
	max_height = (pow(velocity, 2) * pow(sin(angle), 2)) / (2 * g);
	max_distance = velocity * max_d_time * cos(angle);
	max_range = pow(velocity, 2) / g;
	
	cout << fixed << setprecision(3)<< left;  // set fixed, precision to three decimal places, align left, set width to 25
	cout << setw(25) << "Time to max height: " << max_h_time << " seconds" << endl;
	cout << setw(25) << "Time to max distance: " << max_d_time << " seconds" << endl;
	cout << setw(25) << "Maximum height: " << max_height << " meters" << endl;
	cout << setw(25) << "Maximum distance: " << max_distance << " meters" << endl;
	cout << setw(25) << "Maximum range: " << max_range << " meters" << endl << endl;  // output results
	
	return 0;
}
