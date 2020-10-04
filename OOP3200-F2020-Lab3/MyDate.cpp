/***************************************************************************
 *	CONSTRUCTOR DEFINITIONS
 ***************************************************************************/
 // MyDate(long) definition
#include "MyDate.h"
/***************************************************************************
 *	STATIC DATA MEMBER DEFINITIONS
 ***************************************************************************/

const int MyDate::day_limits[] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // Index 0 not used.

const string MyDate::month_names[] = { "Not Used", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

const string MyDate::days_of_week[] = { "Not Used", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };


//#include <iostream>

MyDate::MyDate(const long day_number)
{
	const auto last_day = 3652059L; // 31 Dec 9999

	// if the parameter is valid
	if (day_number >= 1L && day_number <= last_day)
	{
		// Local variables
		auto day = 1;	// temporary day
		auto month = 1;	// temporary month
		auto year = 1;	// temporary year
		int day_limit;	// the highest day of any given month

		// Loop from 1 to the parameter
		for (int i = 1; i < day_number; i++)
		{
			// determine the highest day for the current month
			day_limit = day_limits[month];
			// adjust if it is a leap year and Feb
			if (IsLeapYear(year) && month == 2)
			{
				day_limit = 29;
			}

			// increase the day counter by 1
			day++;

			// if the day counter exceeded the limit for this month:
			if (day > day_limit)
			{
				month++; // roll to the next month
				day = 1; // reset to the 1st

				// if the month counter exceeded December (12)
				if (month > 12)
				{
					year++; // roll to the next year
					month = 1; // reset to Jan (1)
				}
			} // end of adjustment for roll-over
		} // end of counting up to parameter

		// Sets the fields to the day/month/year counters
		myDay = day;
		myMonth = month;
		myYear = year;
	}
	else // Otherwise, parameter was not valid
	{
		// Build an error string
		stringstream errorMessage;
		errorMessage << day_number << " is an invalid value for a day number.\nValue must be greater than 0.";
		// throw exception
		throw out_of_range(errorMessage.str());
	}
}

/***************************************************************************
 *	MUTATOR DEFINITIONS
 ***************************************************************************/
 // MyDate::SetYear
void MyDate::SetYear(const int year)
{
	const auto max_year = 9999; // max possible year
	const auto min_year = 1; // min possible year

	// if the year is in range
	if (year >= min_year && year <= max_year)
	{
		myYear = year; // set the year field
	}
	else // otherwise
	{
		// Build an error msg
		stringstream errorMessage;
		errorMessage << year << " is an invalid value for year.\nValue must be between "
			<< setfill('0') << setw(4) << min_year << " and "
			<< setw(4) << max_year << " inclusive.";
		// throw an exception
		throw out_of_range(errorMessage.str());
	}
}
// MyDate::SetMonth
void MyDate::SetMonth(int month)
{
	const auto max_month = 12; // max possible month
	const auto min_month = 1; // min possible month

	// if the month is in range
	if (month >= min_month && month <= max_month)
	{
		myMonth = month; // set the month field
	}
	else // otherwise
	{
		// Build an error msg
		stringstream errorMessage;
		errorMessage << month << " is an invalid value for month.\nValue must be between "
			<< min_month << " and " << max_month << " inclusive.";
		// throw an exception
		throw out_of_range(errorMessage.str());
	}
}

// MyDate::SetDay
void MyDate::SetDay(const int day)
{
	const auto min_day = 1;// min possible day
	auto max_day = day_limits[myMonth]; // max possible day (depends on month)

	// if it is Feb and a leap year
	if (IsLeapYear() && myMonth == 2)
		max_day = 29; // set the max to 29

	// if the day is in range
	if (day >= min_day && day <= max_day)
	{
		myDay = day; // set the day field
	}
	else // otherwise
	{
		// Build an error msg
		stringstream errorMessage;
		errorMessage << day << " is an invalid value for a day in " << month_names[myMonth] << " "
			<< setfill('0') << setw(4) << myYear << ".\nValue must be between "
			<< min_day << " and " << max_day << " inclusive.";
		// throw an exception
		throw out_of_range(errorMessage.str());
	}
}


/***************************************************************************
 *	ACCESSOR DEFINITIONS
 ***************************************************************************/



 /***************************************************************************
  *	STATIC METHOD DEFINITIONS
  ***************************************************************************/

  // MyDate::IsLeapYear(int)
bool MyDate::IsLeapYear(const int year)
{
	/*
	In the Gregorian calendar 3 criteria must be taken into account to identify leap years:

	The year is evenly divisible by 4;
	If the year can be evenly divided by 100, it is NOT a leap year, unless;
	The year is also evenly divisible by 400. Then it is a leap yea
	*/
	bool leapYear = false; // assume it is not a leap year

	if (year % 4 == 0) // Leap years must be evenly divisible by 4
	{
		// If year can be evenly divided by 100
		if (year % 100 == 0)
		{
			// it is NOT a leap year, UNLESS
			// year is also evenly divisible by 400
			if (year % 400 == 0)
			{
				// it is a leap year
				leapYear = true;
			}
		}
		else // Leap year was not divisible by 100
		{
			// it is a leap year
			leapYear = true;
		}
	}
	return leapYear;
}

// MyDate::Today() definition
MyDate MyDate::Today()
{
	MyDate today; // the object to set to today and return
	auto the_time = time(nullptr); // get the current time/date
	tm time_structure{};
	localtime_s(&time_structure, &the_time); // convert to a tm structure
	today.myDay = time_structure.tm_mday; // set the day
	today.myMonth = time_structure.tm_mon + 1; // set the month (tm_mon is months from Jan <0-11>)
	today.myYear = time_structure.tm_year + 1900; // set the year (tm_year is years since 1900)
	// return the object
	return today;
}

/***************************************************************************
 *	Operator DEFINITIONS
 ***************************************************************************/

 // operator + (Addition)
MyDate MyDate::operator+(const int days) const
{
	MyDate newDate; // create a new empty date
	long thisDateNumber = static_cast<long>(*this); // store this date as a long
	thisDateNumber += days; // add the number of days to it
	newDate = static_cast<MyDate>(thisDateNumber); // set the new date based on the long
	return newDate; // return the new date
}

// operator - (Subtraction)
MyDate MyDate::operator-(int days) const
{
	MyDate newDate; // create a new empty date
	long thisDateNumber = static_cast<long>(*this); // store this date as a long
	thisDateNumber -= days; // subtract the number of days from it
	newDate = static_cast<MyDate>(thisDateNumber); // set the new date based on the long
	return newDate; // return the new date
}

// operator = (Assignment)
MyDate& MyDate::operator=(const MyDate& copy)
{
	// assign each member the corresponding
	// member from the copy object
	myDay = copy.myDay;
	myMonth = copy.myMonth;
	myYear = copy.myYear;
	// return this object (supports obj3 = obj2 = obj1)
	return *(this);
}

// MyDate::operator string definition
MyDate::operator string() const
{
	stringstream dateString; // string stream to build the formatted date string
	int postFixDigit;		 // the last digit of the day value

	// Stream the day of the week, followed by month name and day value
	dateString << GetDayOfWeek() << ", " << month_names[myMonth] << " " << myDay;

	// determine the last digit of the day value
	postFixDigit = myDay % 10;

	// determine and stream the approriate post-fix
	if (postFixDigit == 1 && myDay != 11)
	{
		dateString << "st";
	}
	else if (postFixDigit == 2 && myDay != 12)
	{
		dateString << "nd";
	}
	else if (postFixDigit == 3 && myDay != 13)
	{
		dateString << "rd";
	}
	else
	{
		dateString << "th";
	}

	// stream the year, showing 4 digits (minimum)
	dateString << ", " << setfill('0') << setw(4) << myYear;

	// return the formatted string
	return dateString.str();
}

// MyDate::operator long definition
MyDate::operator long() const
{
	long dayNumber = 0; // counter for the days since 1/1/0001
	int leapYears = 0;	// counter for the leap years since 1/1/0001

	// Add 365 for each year up to but not including this year
	dayNumber = (myYear - 1) * 365;

	// Count the leap years up to but not including this year
	for (int year = 1; year < myYear; year++)
	{
		if (IsLeapYear(year))
			leapYears++;
	}
	// Add 1 more day for each leap year found
	dayNumber += leapYears;

	// Add the number of days in each month for each month of this year
	// up to but not including this month
	for (int i = 1; i < myMonth; i++)
	{
		dayNumber += day_limits[i];
	}
	// Add the days for this month
	dayNumber += myDay;

	// if this is a leap year and it is past 28 Feb
	if (IsLeapYear() && myMonth > 2)
	{
		dayNumber++;
	}

	// return the sum.
	return dayNumber;
}

// operator [char] (Subscript)
int MyDate::operator[](const char value_type) const
{
	int value = 0; // value to return
	switch (value_type) // based on the parameter char
	{
	case 'd':
	case 'D':
		value = myDay; // get day
		break;
	case 'm':
	case 'M':
		value = myMonth; // get month
		break;
	case 'y':
	case 'Y':
		value = myYear; // get year
		break;
	default: // error, throw invalid_argument exception
		// Build an error msg
		stringstream errorMessage;
		errorMessage << value_type << " is an invalid parameter. Options are \'d\', \'m\', or \'y\'";
		// throw an exception
		throw invalid_argument(errorMessage.str());
	}
	return value;
}

// operator << (Insertion/Output)
ostream& operator<<(ostream& out, const MyDate& the_date)
{
	// output the date in the format dd/mm/yyyy
	out << setfill('0')
		<< setw(2) << the_date.myDay << '/'
		<< setw(2) << the_date.myMonth << '/'
		<< setw(4) << the_date.myYear << setfill(' ');
	return out;  // return the output stream
}

// operator >> (Extraction/Input)
istream& operator>>(istream& in, MyDate& the_date)
{
	int day;  // temp day
	int month; // temp month
	int year; // temp year

	cout << "Enter Day: ";
	in >> day; // get day
	fflush(stdin);
	//in.ignore(); // ignore the '/'

	cout << "Enter Month: ";
	in >> month; // get month
	fflush(stdin);

	//in.ignore(); // ignore the '/'

	std::cout << "Enter Year: ";
	in >> year; // get year

	// store the date
	the_date.SetDate(day, month, year);

	return in; // return the input stream
}