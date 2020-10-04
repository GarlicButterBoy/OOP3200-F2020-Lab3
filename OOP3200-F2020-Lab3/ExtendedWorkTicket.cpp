/**
 * Project Untitled
 */


#include "ExtendedWorkTicket.h"

//#include <string>

 /**
  * ExtendedWorkTicket implementation
  */


ExtendedWorkTicket::ExtendedWorkTicket() : WorkTicket(), m_isOpen(true)
{

}

  /**
   * @param myTicketNumber
   * @param myClientId
   * @param day
   * @param month
   * @param year
   * @param myDescription
   * @param isOpen
   */
ExtendedWorkTicket::ExtendedWorkTicket(const int myTicketNumber, std::string myClientId, const int day, const int month, const int year, std::string myDescription, const bool is_open)
	: WorkTicket(myTicketNumber, myClientId, day, month, year, myDescription), m_isOpen(is_open) {};

/**
 * @return bool
 */
bool ExtendedWorkTicket::GetIsOpen() const
{
    return m_isOpen;
}

/**
 * @param value
 */
void ExtendedWorkTicket::SetIsOpen(const bool value)
{
    m_isOpen = value;
}

/**
 * @return string
 */
void ExtendedWorkTicket::ShowWorkTicket() const
{
	//std::string outputString;
	std::string ticketStatus;

	if (m_isOpen)
	{
		ticketStatus = "open.";
	}
	else
	{
		ticketStatus = "closed.";
	}

	WorkTicket::ShowWorkTicket();
	cout << "\n Ticket is " + ticketStatus;

}

/**
 * @param ticketNumber
 * @param client_id
 * @param day
 * @param month
 * @param year
 * @param description
 * @param is_open
 */
bool ExtendedWorkTicket::SetWorkTicket(const int ticketNumber, const string& client_id, const int day, const int month, const int year, const string& description, bool is_open)
{
	is_open = WorkTicket::SetWorkTicket(ticketNumber, client_id, day, month, year, description);

	return is_open;
}

/**
 * @param isOpen
 */
void ExtendedWorkTicket::CloseTicket()
{
	if (m_isOpen)
	{
		m_isOpen = false;
	}
}

ExtendedWorkTicket& ExtendedWorkTicket::operator=(const ExtendedWorkTicket& original)
{
	SetWorkTicket(original.GetTicketNumber(), original.GetClientId(), original.GetDate().GetDay(),
		original.GetDate().GetMonth(), original.GetDate().GetYear(), original.GetDescription(), original.GetIsOpen());
	return *this;
}

ExtendedWorkTicket::operator string() const
{
	stringstream strStream;
	strStream << "Work Ticket # " << GetTicketNumber()
		<< " - " << GetClientId()
		<< " (" << GetDate() << "): "
		<< GetDescription() << "  "
		<< GetIsOpen();
	return strStream.str();
}

bool ExtendedWorkTicket::operator==(const ExtendedWorkTicket& original) const
{


	return ((GetTicketNumber() == original.GetTicketNumber())) &&
		((GetClientId() == original.GetClientId())) &&
		((GetDate() == original.GetDate())) &&
		(GetDescription() == original.GetDescription()) &&
		(GetIsOpen() == original.GetIsOpen());
}

//istream& operator>>(istream& in, ExtendedWorkTicket& ticket)
//{

//}

ostream& operator<<(ostream& out, const ExtendedWorkTicket& ticket)
{
	/* Overload the '<<' operator relative to the class to displays all the
	   object's attributes neatly on the console or to any ostream. This will
	   duplicate the functionality of the ShowWorkTicket() method however keep
	   the original method intact for legacy reasons. */

	out << "\nTicket is Open: " << ticket.m_isOpen << endl;

	return out;



	/*out << ticket.GetTicketNumber() << endl
		<< ticket.GetClientId() << endl
		<< ticket.GetDate() << endl
		<< ticket.GetDescription() << endl
		<< ticket.m_isOpen;
	return out;*/
}
