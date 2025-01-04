// ****************************************
// Program Title: Using a Date Class
// Project File: Project_10.cpp
// Name: Esther Shore
// Course Section: CPE-211-02
// Lab Section: 1
// Due Date: 12/02/2022
// Program Description: Establishes constructors,
// transformers, and observers to alter a date
// ****************************************

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "Project_10.h"

using namespace std;

// ************** CONSTRUCTORS **************
// default constructor - set date to 1/1/2000
Date::Date()
{
	month = 1;
	day = 1;
	year = 2000;
}

// parameterized constructors
Date::Date(int initMonth, int initDay, int initYear)
{
	month = initMonth;
	day = initDay;
	year = initYear;
}  
   
Date::Date(int initMonth, int initYear)
{
	month = initMonth;
	day = 1;
	year = initYear;
}

Date::Date(int initYear)
{
	month = 1;
	day = 1;
	year = initYear;
}

// ************** TRANSFORMERS **************
void Date::SetDate(int m, int d, int y)
{
	month = m;
	day = d;
	year = y;
}

void Date::IncrementDateDay()
{
	day++;
	// months with 30 days: sept, april, june, nov
	// months with 28 days: feb
	// months with 31 days: jan, march, may, july, aug, oct, dec
	// if day is greater than number of days in the month, increment to first day of next month
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
		{
			day = 1;
			month++;
		}
	}
	else if (month == 2)
	{
		if (day > 28)
		{
			day = 1;
			month++;
		}	
	}
	else
	{
		if (day > 31)
		{
			day = 1;
			month++;
		}
	}
	// if month is greater than number of months, increment to first month of next year
	if (month > 12)
	{
		month = 1;
		year++;
	}
}

void Date::IncrementDateMonth()
{
	month++;
	
	if (month > 12)
	{
		month = 1;
		year++;
	}
}

void Date::IncrementDateYear()
{
	year++;
}

void Date::IncrementDateDays(int days)
{
	day += days;
	// loop to increment appropriate number of months and set correct day
	while (days > 0)
	{
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day > 30)
			{	
				day -= 30;
				days -= 30;  // subtract number of days in the month from additional days and day
				month++;
			}
			else  // if day is less than or equal to number of days in month, then the month and day are correct
				days = 0;  // break out of loop
		}
		else if (month == 2)
		{
			if (day > 28)
			{
				day -= 28;
				days -= 28;
				month++;
			}	
			else
				days = 0;
		}
		else
		{
			if (day > 31)
			{
				day -= 31;
				days -= 31;
				month++;
			}
			else
				days = 0;
		}

		if (month > 12)
		{
			month = 1;
			year++;
		}		
	}
}

// ************** OBSERVERS *******************
// write out date in format of MM/DD/YYYY
void Date::WriteNumberFormat() const
{
	if (month < 10)
		cout << '0';
	cout << month << '/';
	if (day < 10)
		cout << '0';
	cout << day << '/';

	cout << year << endl;
}

// write out date in MONTH DAY, YEAR format
void Date::WriteNameFormat() const
{
	switch (month)
	{
		case 1:
			cout << "January ";
			break;
		case 2:
			cout << "February ";
			break;
		case 3:
			cout << "March ";
			break;
		case 4:
			cout << "April ";
			break;
		case 5:
			cout << "May ";
			break;
		case 6:
			cout << "June ";
			break;
		case 7:
			cout << "July ";
			break;
		case 8:
			cout << "August ";
			break;
		case 9:
			cout << "September ";
			break;
		case 10:
			cout << "October ";
			break;
		case 11:
			cout << "November ";
			break;
		case 12:
			cout << "December ";
	}
	cout << day << ", " << year << endl;
}
