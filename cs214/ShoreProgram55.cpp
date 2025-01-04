/*******************************************************************
*   CS214-01 Programming Assignment
*   File: ShoreProgram55.cpp
*   Author: Esther Shore
*   Desc: Algorithm computation times
*   Date: 3/26/2023
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

void convertTime(double);

int main()
{
    double t0;  // time for one calculation
    int nums[3];  // array to hold number of iterations
    double times[3];  // array to hold time for each number of iterations

    // prompt user for input and echo print
    cout << endl;
    cout << "Enter time for one calculation in seconds: ";
    cin >> t0;
    cout << t0 << " seconds" << endl;
    cout << "Enter LOW number of iterations: ";
    cin >> nums[0];
    cout << nums[0] << " iterations" << endl;
    cout << "Enter MIDDLE number of iterations: ";
    cin >> nums[1];
    cout << nums[1] << " iterations" << endl;
    cout << "Enter HIGH number of iterations: ";
    cin >> nums[2];
    cout << nums[2] << " iterations" << endl << endl;

    // output results
    cout << left;
    cout << setw(10) << "Order" << setw(30) << "Low = " + to_string(nums[0]) << setw(30) << "Middle = " + to_string(nums[1]) << "High = " + to_string(nums[2]) << endl;
    cout << setw(10) << "log2(n)";
    for (int i=0; i<3; i++)  // for low, middle, and high iterations: calculate time and convert time to proper units
    {
        times[i] = t0 * log2(nums[i]);
        convertTime(times[i]);
    }
    cout << endl;
    cout << setw(10) << "n";
    for (int i=0; i<3; i++)
    {
        times[i] = t0 * nums[i];
        convertTime(times[i]);
    }
    cout << endl;
    cout << setw(10) << "nlog2(n)";
    for (int i=0; i<3; i++)
    {
        times[i] = t0 * nums[i] * log2(nums[i]);
        convertTime(times[i]);
    }
    cout << endl;
    cout << setw(10) << "n^2";
    for (int i=0; i<3; i++)
    {
        times[i] = t0 * pow(nums[i], 2);
        convertTime(times[i]);
    }
    cout << endl;
    cout << setw(10) << "n^3";
    for (int i=0; i<3; i++)
    {
        times[i] = t0 * pow(nums[i], 3);
        convertTime(times[i]);
    }
    cout << endl;
    cout << setw(10) << "n!";
    for (int i=0; i<3; i++)
    {
        times[i] = t0 * tgamma(nums[i] + 1);  // tgamma(n + 1) = n!
        convertTime(times[i]);
    }
    cout << endl;
    cout << setw(10) << "2^n";
    for (int i=0; i<3; i++)
    {
        times[i] = t0 * pow(2, nums[i]);
        convertTime(times[i]);
    }
    cout << endl << endl;
    return 0;
}

// function to convert to proper time units
void convertTime(double t_sec)
{
    double t_min;
    double t_hr;
    double t_day;
    double t_yr;
    double t_cent;

    if (isnan(t_sec))  // indicates tgamma resulted in inf
    {
        cout << setw(30) << "Greater than 1,000 Centuries.";
        return;
    }
    else
    {
        if (t_sec >= 60)
        {
            t_min = t_sec / 60;
        }
        else
        {
            cout << setw(30) << to_string(t_sec) + " seconds";
            return;
        }
        
        if (t_min >= 60)
        {
            t_hr = t_min / 60;
        }
        else
        {
            cout << setw(30) << to_string(t_min) + " minutes";
            return;
        }   

        if (t_hr >= 24)
        {
            t_day = t_hr / 24;
        }
        else
        {
            cout << setw(30) << to_string(t_hr) + " hours";
            return;
        }

        if (t_day >= 365)
        {
            t_yr = t_day / 365;
        }
        else
        {
            cout << setw(30) << to_string(t_day) + " days";
            return;
        }
        
        if (t_yr >= 100)
        {
            t_cent = t_yr / 100;
        }
        else
        {
            cout << setw(30) << to_string(t_yr) + " years";
            return;
        }

        if (t_cent > 1000)
        {
            cout << setw(30) << "Greater than 1,000 Centuries.";  
        }
        else
        {
            cout << setw(30) << to_string(t_cent) + " centuries";
            return;
        }
    }
}
