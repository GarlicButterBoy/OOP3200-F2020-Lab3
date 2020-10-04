/*
 * MyDate.cpp
 * Nick Sturch-Flint
 * October 4, 2020
 * 100303769
 */

/***************************************************************************
*	 LAB C1 Method Definitions
*	 - Parameterized Constructor
*	 - SetWorkTicket()
*	 - ShowWorkTicket()
*	 - SetTicketNumber()
*	 - SetDate()
***************************************************************************/

//// WorkTicket::Parameterized Constructor definition
#include <iostream>		// for cin, cout
#include <stdexcept>	// for invalid_argument
#include "WorkTicket.h"

WorkTicket::WorkTicket(int ticket_number, string& client_id, int day, int month, int year, string& description)
{
	// Set each data member with appropriate validation:
	SetTicketNumber(ticket_number);
	SetClientId(client_id);
	SetDescription(description);
	SetDate(day, month, year);
}

// WorkTicket::SetTicket definition
inline bool WorkTicket::SetWorkTicket(int ticket_number, const string& client_id, int day, int month, int year, const string& description)
{
	MyDate workingDate;
	const auto min_year = 2000;
	const auto max_year = 2099;
	auto valid = true; // flag for if parameters are valid

	// check numeric parameters
	if (ticket_number < 0 || year < min_year || year > max_year)
		valid = false;
	// check string parameters
	else if (client_id.length() < 1 || description.length() < 1)
		valid = false;
	else
	{
		try
		{
			// sets the date (may throw an exception even if rules are met)
			workingDate.SetDate(day, month, year);
		}
		catch (...)
		{
			valid = false;
		}
	}

	if (valid) // all parameters are valid
	{
		// set the workticket date
		myDate = workingDate;

		// set atributes to parameter values
		myTicketNumber = ticket_number;
		myClientId = client_id;
		myDescription = description;
	}
	// return true or false based on parameter validity
	return valid;
}

// WorkTicket::ShowTicket definition
void WorkTicket::ShowWorkTicket() const
{
	// display the attributes of the object neatly to the console
	cout << "\nWork Ticket #: " << myTicketNumber
		<< "\nClient ID:     " << myClientId
		<< "\nDate:          " << myDate
		<< "\nIssue:         " << myDescription << endl;

}

// WorkTicket::SetTicketNumber definition
void WorkTicket::SetTicketNumber(const int ticketNumber)
{
	// If a work ticket number is set to a zero or a negative number,
	// an invalid_argument exception should be thrown, with an
	// appropriate message.
	if (ticketNumber > 0)
	{
		myTicketNumber = ticketNumber;
	}
	else
	{
		throw invalid_argument("Ticket number must be greater than zero. ");
	}
}

// WorkTicket::ShowTicket definition
void WorkTicket::SetDate(const int day, const int month, const int year)
{
	//  An invalid_argument exception should be thrown, with an
	//  appropriate message if the day, month, or year is set out of range.

	const int MIN_YEAR = 2000;
	const int MAX_YEAR = 2099;
	if (year >= MIN_YEAR && year <= MAX_YEAR) // unique year requirements
	{
		myDate.SetDate(day, month, year); // day and month validated in the method
	}
	else
	{
		stringstream errorString;
		errorString << "Year must be between " << MIN_YEAR << " and " << MAX_YEAR << ". ";
		throw invalid_argument(errorString.str());
	}
}

/***************************************************************************
*	 LAB C2 Method Definitions
*	 - Copy Constructor
*	 - operator string()
*	 - operator==()
*	 - operator=()
*	 - operator>>()
*	 - operator<<()
***************************************************************************/

// WorkTicket::Copy Constructor definition (Lab C2)
WorkTicket::WorkTicket(const WorkTicket& original)
{
	/*  A copy constructor that initializes a new WorkTicket object based
		on an existing WorkTicket object. For testing purposes, include the
		statement:
		cout << "\nA WorkTicket object was COPIED.\n";
	*/
	myTicketNumber = original.myTicketNumber;
	myClientId = original.myClientId;
	myDate = original.myDate;
	myDescription = original.myDescription;

	//cout << "\nA WorkTicket object was COPIED.\n";
}

// WorkTicket::Assignment operator (=) definition (Lab C2)
WorkTicket& WorkTicket::operator=(const WorkTicket& original)
{
	/*  Overload the assignment (=) operator to assign all of the attributes
		of one WorkTicket object to another (member-wise assignment).  For
		testing purposes, include the statement:
		cout << "\nA WorkTicket object was ASSIGNED.\n";
	*/

	myTicketNumber = original.myTicketNumber;
	myClientId = original.myClientId;
	myDate = original.myDate;
	myDescription = original.myDescription;

	//cout << "\nA WorkTicket object was ASSIGNED.\n";
	return *this;
}

// WorkTicket:: string typecast operator (Lab C2)
WorkTicket::operator string () const
{
	/*  A conversion operator that converts a WorkTicket object to a string
		in the following format: Work Ticket # Number - Client ID (Date): Description; e.g.:
		"Work Ticket # 2 - ABC123 (10/3/2012): User cannot locate \'any\' key"
	*/

	stringstream strStream;
	strStream << "Work Ticket # " << myTicketNumber
		<< " - " << myClientId
		<< " (" << myDate << "): "
		<< myDescription;
	return strStream.str();

}

// WorkTicket equality operator (Lab C2)
bool WorkTicket::operator==(const WorkTicket& original)
{
	/* Overload the equality ('==') operator  to compare a WorkTicket object
	   to another WorkTicket object using a member-wise comparison. Return
	   true if all the attributes of both objects are the same; false if they
	   are not all the same.
	*/

	return myTicketNumber == original.myTicketNumber &&
		myClientId == original.myClientId &&
		myDate == original.myDate &&
		myDescription == original.myDescription;
} // end of WorkTicket equality operator

// Overloaded input operator
ostream& operator<<(ostream& out, const WorkTicket& ticket)
{
	/* Overload the '<<' operator relative to the class to displays all the
	   object's attributes neatly on the console or to any ostream. This will
	   duplicate the functionality of the ShowWorkTicket() method however keep
	   the original method intact for legacy reasons. */

	out << "\nWork Ticket #: " << ticket.myTicketNumber
		<< "\nClient ID:     " << ticket.myClientId
		<< "\nDate:          " << ticket.myDate
		<< "\nIssue:         " << ticket.myDescription << endl;
	return out;
} // end of overloaded input operator

// Overloaded output operator
istream& operator>>(istream& in, WorkTicket& ticket)
{
	/* Overload the '>>' operator relative to the class to allow the user
	   to enter all of the attributes of a WorkTicket object from the console
	   or any istream. Include validation.
	*/

	int ticket_number;	 // temporary input variable
	string client_id;	 // temporary input variable
	MyDate date;		 // temporary input variable
	string description; // temporary input variable

	try
	{
		// prompt for user input for each attribute and store in the
		// corresponding temp variable
		cout << "\nWorkTicket #: ";
		in >> ticket_number;
		fflush(stdin);

		cout << "Client ID: ";
		in >> client_id;
		fflush(stdin);

		//getline(in, client_id);

		cout << "Date (dd/mm/yyyy): ";
		in >> date;
		fflush(stdin);

		cout << "Issue: ";
		getline(in, description);

		ticket.SetWorkTicket(ticket_number, client_id, date.GetDay(), date.GetMonth(), date.GetYear(), description);
	}
	catch (const out_of_range& oor)
	{
		in.setstate(ios::failbit); // set .fail() to true
		throw oor; // re-throw the exception
	}
	catch (const invalid_argument& invalid)
	{
		in.setstate(ios::failbit); // set .fail() to true
		throw invalid; // re-throw the exception
	}

	return in;
} // end of overloaded output operator