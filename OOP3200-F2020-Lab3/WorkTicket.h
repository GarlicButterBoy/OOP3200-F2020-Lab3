/** MyLabC3WorkTicket.h
 *
 *	A solution to C++ Labs 1 and 2 using the MyDate class. Use this header for C++ Lab 3.
 *
 *	@author		Thom MacDonald
 *	@author     Tom Tsiliopoulos
 *	@version	2020.09
 *	@since		Jul 2018
 *	@see		Bronson, G. (2012). A First Book of C++ (4th ed.). Boston, MA: Course Technology.
 *	@see		MyDate.h
*/
#pragma once

#ifndef _WORKTICKET
#define _WORKTICKET


#include <iomanip> 		// for output formatting

#include <sstream>		// for stringstream
#include <utility>
#include "MyDate.h" 	// version 2018.01

using namespace std;


class WorkTicket
{
public:
	//friend class MyDate;

	virtual ~WorkTicket() = default;

	/***************************************************************************
	*	Default and parameterized constructor(s).
	*	If parameters are not specified, set the work ticket number to zero,
	*	the work ticket date to 1/1/2000, and all other attributes to empty
	*	strings.
	***************************************************************************/

	WorkTicket() : myTicketNumber(0), myClientId(""), myDate(1, 1, 2000), myDescription("") { }
	WorkTicket(int ticket_number, string& client_id, int day, int month, int year, string& description);

	/***************************************************************************
	*	 Copy constructor
	*	 Initializes a new WorkTicket object based on an existing WorkTicket
	*	 object.
	***************************************************************************/
	WorkTicket(const WorkTicket& original);

	/***************************************************************************
	*	SetWorkTicket()
	*	a mutator method to set all the attributes of the object to the
	*	parameters as long as the parameters are valid. ALL of the parameters
	*	must be valid in order for ANY of the attributes to change. Validation
	*	rules are explained for work ticket number and date. Client number
	*	and Description must be at least one character long. If no problems are
	*	detected, return TRUE.  Otherwise return FALSE.
	***************************************************************************/

	virtual bool SetWorkTicket(int ticket_number, const string& client_id, int day, int month, int year, const string&
	                   description);

	/***************************************************************************
	*	ShowWorkTicket( )
	*	An accessor method to display all the object's attributes neatly in
	*	the console window.
	***************************************************************************/

	virtual void ShowWorkTicket() const; // accessor

   /***************************************************************************
   *	Attribute Sets/Gets.
   *	Include a set (mutator) and get (accessor) method for each attribute.
   ***************************************************************************/

   // Ticket Number
	void SetTicketNumber(int ticketNumber);
	int GetTicketNumber() const { return myTicketNumber; }

	// Client ID
	void SetClientId(string clientId) { myClientId = std::move(clientId); }
	string GetClientId() const { return myClientId; }

	// Decsription
	void SetDescription(string description) { myDescription = std::move(description); }
	string GetDescription() const { return myDescription; }

	// Date
	void SetDate(int day, int month, int year);
	const MyDate& GetDate() const { return myDate; }

	/***************************************************************************
	*	Operators (LAB C2).
	*	Include a set (mutator) and get (accessor) method for each attribute.
	***************************************************************************/
	WorkTicket& operator=(const WorkTicket& original); // Assignment
	operator string () const;	// (string)
	bool operator==(const WorkTicket& original); // Equality
	friend ostream& operator<<(ostream& out, const WorkTicket& ticket); // Output
	friend istream& operator>>(istream& in, WorkTicket& ticket); // Input

private:

	/***************************************************************************
	*	Private Attributes.  An object of class WorkTicket has the following
	*		private attributes.
	***************************************************************************/

	int myTicketNumber;	// Work Ticket Number - A whole, positive number.
	string myClientId;		// Client ID - The alpha-numeric code assigned to the client.
	MyDate myDate; 		// Work Ticket Date - the date the workticket was created
	string myDescription;  // Issue Description - A description of the issue the client is having.
};  // end of WorkTicket class


#endif

