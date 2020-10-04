/*
 * MyDate.h
 * Nick Sturch-Flint
 * October 4, 2020
 * 100303769
 *
 *	The MyDate class stores and manipulates Gregorian dates in a C++ program.
 *  The aim of creating this class is to demonstrate some fundamental and
 *  intermediate class/object concepts. It will serve as a base for exploring
 *	and implementing further OOP techniques.
 *
 *
 *	@author		Thom MacDonald <thom.macdonald@durhamcollege.ca>
 *	@author		Tom Tsiliopoulos <tom.tsiliopoulos@durhamcollege.ca>
 *	@author
 *	@version	2020.09
 *	@since		28 Jul 2018
 *	@see		<http://en.wikipedia.org/wiki/Gregorian_calendar>
 *	@see
*/

#pragma once
#ifndef _MY_DATE_H

#define _MY_DATE_H

#include <iostream> 	// for console I/O
#include <iomanip>		// for output stream formatting
#include <sstream>		// for stringstream
#include <stdexcept>	// for standard exceptions
#include <ctime>		// for time related items
using namespace std;

class MyDate
{
public:

	/***************************************************************************
	*	CONSTRUCTORS
	***************************************************************************/

	/** Default Constructor
	 *	Initializes the day/month/year fields to 1/1/2000.
	 */
	MyDate() :myDay(1), myMonth(1), myYear(2000) {}

	/** Parametrized Constructor
	 *	Sets the day/month/year fields to parameters.
	 *	@param day (int) - the day to set to
	 *	@param month (int) - the month to set to
	 *	@param year (int) - the year to set to
	 */
	MyDate(const int day, const int month, const int year) { MyDate::SetDate(day, month, year); }

	/** Copy Constructor
	 *	Sets the day/month/year fields to an existing objects day/month/year fields.
	 *	@param copy (MyDate) - the existing object to copy
	 */
	MyDate(const MyDate& copy) : myDay(copy.myDay), myMonth(copy.myMonth), myYear(copy.myYear) {}

	/** Long Constructor
	 *	Sets the day/month/year fields from a long. Also used to
	 *  convert a long to a MyDate.
	 *	@param days_since (long) - the days since 1/1/0001
	 *	@throws (out_of_range) if the parameter is < 1.
	 */
	MyDate(long days_since);

	/***************************************************************************
	*	PUBLIC MUTATORS
	***************************************************************************/

	/** SetDate()
	 *	Sets the day/month/year fields to parameters.
	 *	@param day (int) - the day to set to
	 *	@param month (int) - the month to set to
	 *	@param year (int) - the year to set to
	 */
	virtual void SetDate(int day, int month, int year) { SetYear(year); SetMonth(month); SetDay(day); }

	/** Individual Property Mutators (Sets)
	 *	Sets the corresponding field to the parameter.
	 *	@param year
	 *	@param (int) - the value to set to
	 *	@throws (out_of_range) if the parameter is out of a valid range
	 */
	void SetYear(int year);
	void SetMonth(int month);
	void SetDay(int day);

	/***************************************************************************
	*	PUBLIC ACCESSORS
	***************************************************************************/

	/** isLeapYear()
	 *	Determines if the year stored in the object is a leap year.
	 *	@return (bool) - true for leap year, false for non-leap year.
	 */
	bool IsLeapYear() const { return IsLeapYear(myYear); }

	/** GetDayOfWeek()
	 *	Returns the day of the week the date stored in the object is.
	 *	@return (string) - the day of the week the date stored in the object is.
	 */
	string GetDayOfWeek() const { return days_of_week[static_cast<long>(*this) % 7 + 1]; }

	/** Individual Property Accessors (Gets)
	 *	Gets the value stored in the corresponding.
	 *	@return (int) - the value stored in the field
	 */
	int GetMonth() const { return myMonth; }
	int GetYear() const { return myYear; }
	int GetDay() const { return myDay; }

	/***************************************************************************
	*	STATIC METHODS
	***************************************************************************/
	/** isLeapYear(int)
	 *	Determines if the year passed as a parameter is a leap year.
	 *	@return (bool) - true for leap year, false for non-leap year.
	 */
	static bool IsLeapYear(int year);

	/** Today()
	 *	Returns the current date as a MyDate object.
	 *	@return (MyDate) - today's date.
	 */
	static MyDate Today();

	/***************************************************************************
	*	OPERATOR METHODS
	***************************************************************************/

	/** operator + (Addition)
	 *	Adds a specified number of days to the date and returns it.
	 *	@param  days (int) - the number of days to add
	 *	@return (MyDate) - the new date.
	 */
	MyDate operator+(int days) const;

	/** operator - (int) (Subtract days)
	 *	Subtracts a specified number of days from this date and returns it.
	 *	@param  days (int) - the number of days to subtract
	 *	@return (MyDate) - the new date.
	 */
	MyDate operator-(int days) const;

	/** operator - (MyDate) (Subtract a MyDate) **NEW!**
	 *	Subtracts a specified date from this date and returns it.
	 *	@param  aDate (MyDate) - the number of days to subtract
	 *	@return (long) - the number of days difference.
	 */
	long operator-(const MyDate& aDate) const { return static_cast<long>(*(this)) - static_cast<long>(aDate); }

	/** operator = (Assignment)
	 *	Assigns the member values of a specified date to this date.
	 *	@param  copy (MyDate by const ref) - the date being compared to
	 *	@return (MyDate by ref) - returns this date
	 */
	MyDate& operator=(const MyDate& copy);

	/** operator -= (Shorthand Subtract Assignment)
	 *	Subtracts a specified number of days from this date.
	 *	@param  days (int) - the number of days to subtract
	 *	@return (MyDate by ref) - this date.
	 */
	MyDate& operator-=(const int days) { return *(this) = *(this) - days; }

	/** operator += (Shorthand Addition Assignment)
	 *	Adds a specified number of days to this date.
	 *	@param  days (int) - the number of days to subtract
	 *	@return (MyDate by ref) - this date.
	 */
	MyDate& operator+=(const int days) { return *(this) = *(this) + days; }

	/** operator ++ (Prefix Increment)
	 *	Adds one day to this date.
	 *	@return (MyDate by ref) - this date.
	 */
	MyDate& operator++() { return *(this) = *(this) + 1; }

	/** operator ++ (Postfix Increment)
	 *	Adds one day to this date.
	 *	@return (MyDate) - the original date.
	 */
	MyDate operator++(int)
	{
		MyDate original_date = *(this); // copy this date
		*(this) = *(this) + 1; // modify this date
		return original_date; // return the copy
	}

	/** operator -- (Prefix Increment)
	 *	Subtracts one day from this date.
	 *	@return (MyDate by ref) - this date.
	 */
	MyDate& operator--() { return *(this) = *(this) - 1; }

	/** operator -- (Postfix Increment)
	 *	Subtracts one day from this date.
	 *	@return (MyDate) - the original date.
	 */
	MyDate operator--(int)
	{
		auto original_date = *(this); // copy this date
		*(this) = *(this) - 1; // modify this date
		return original_date; // return the copy
	}

	/** operator == (Equality)
	 *	Compares two dates memberwise and returns true if they are the same date.
	 *	@param  compare (MyDate by const ref) - the date being compared to
	 *	@return (bool) - true if the dates are the same, false if not
	 */
	bool operator==(const MyDate& compare) const
	{
		return (myDay == compare.myDay &&
			myMonth == compare.myMonth &&
			myYear == compare.myYear);
	}

	/** operator != (Non-Equality)
	 *	Compares two dates memberwise and returns false if they are the same date.
	 *	@param  compare (MyDate by const ref) - the date being compared to
	 *	@return (bool) - false if the dates are the same, true if not
	 */
	bool operator!=(const MyDate& compare) const
	{
		return (!(myDay == compare.myDay &&
			myMonth == compare.myMonth &&
			myYear == compare.myYear));
	}

	/** operator < (Less than)
	 *	Compares two dates
	 *	@param  compare (MyDate by const ref) - the date being compared to
	 *	@return (bool) - returns true if this date is < the parameter date, false if not
	 */
	bool operator<(const MyDate& compare) const { return static_cast<long>(*this) < static_cast<long>(compare); }

	/** operator > (Greater than)
	 *	Compares two dates
	 *	@param  compare (MyDate by const ref) - the date being compared to
	 *	@return (bool) - returns true if this date is > the parameter date, false if not
	 */
	bool operator>(const MyDate& compare) const { return static_cast<long>(*this) > static_cast<long>(compare); }

	/** operator <= (Less than or equal to)
	 *	Compares two dates
	 *	@param  compare (MyDate by const ref) - the date being compared to
	 *	@return (bool) - returns true if this date is <= the parameter date, false if not
	 */
	bool operator<=(const MyDate& compare) const { return static_cast<long>(*this) <= static_cast<long>(compare); }

	/** operator > (Greater than or equal to)
	 *	Compares two dates
	 *	@param  compare (MyDate by const ref) - the date being compared to
	 *	@return (bool) - returns true if this date is >= the parameter date, false if not
	 */
	bool operator>=(const MyDate& compare) const { return static_cast<long>(*this) >= static_cast<long>(compare); }


	/** operator (long) (Typecast)
	 *	Typecasts this date as a long.
	 *	@return (long) - the number of days since 1/1/0001
	 */
	virtual operator long() const;

	/** operator (string) (Typecast)
	 *	Typecasts this date as a string.
	 *	@return (string) - the date stored formatted as a Long Date
	 */
	virtual operator string() const;

	/** operator [char] (Subscript)
	 *	Returns the day, month or year value depending on the parameter specified
	 *  @param  value_type (char) - 'd' for day, 'm' for month, 'y' for year
	 *	@return (int) - the day, month or year value
	 */
	int operator[](char value_type) const;

	/***************************************************************************
	*	OPERATOR FRIENDS (NEW!)
	***************************************************************************/

	/** operator << (Insertion/Output)
	 *	Inserts a date into an ostream
	 *  @param  out (ostream by ref) - the output stream to insert into
	 *  @param  the_date (const MyDate by ref) - the date to insert
	 *	@return (ostream by ref) - supports daisy-chaining
	 */
	friend ostream& operator<<(ostream& out, const MyDate& the_date);

	/** operator >> (Extraction/Input)
	 *	Extracts a date from an istream
	 *  @param  in (istream by ref) - the input stream to extract from
	 *  @param  the_date (MyDate by ref) - stores the extracted date
	 *	@return (istream by ref) - supports daisy-chaining
	 */
	friend istream& operator>>(istream& in, MyDate& the_date);

protected: //**NEW!**
/***************************************************************************
*	PRIVATE INSTANCE ATTRIBUTES/FIELDS
***************************************************************************/
	int myDay;		// stores the day of the month (1-28, 29, 30, or 31)
	int myMonth;	// stores the month (1-12)
	int myYear;		// stores the year (1+)

/***************************************************************************
*	PRIVATE STATIC DATA MEMBERS
***************************************************************************/
	static const int day_limits[];		// the limit of the day based on the month, e.g. 31
	static const string month_names[];	// the month names e.g. "January"
	static const string days_of_week[];	// the day of week names e.g. "Sunday"
}; // End of MyDate class declaration section




#endif
