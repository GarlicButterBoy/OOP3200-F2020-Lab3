/**
 * Project Untitled
 */


#include "ExtendedWorkTicket.h"

#include <string>

 /**
  * ExtendedWorkTicket implementation
  */


  /**
   * @param myTicketNumber
   * @param myClientId
   * @param day
   * @param month
   * @param year
   * @param myDescription
   * @param isOpen
   */
ExtendedWorkTicket::ExtendedWorkTicket(int myTicketNumber, std::string myClientId, int day, int month, int year, std::string myDescription, bool m_isOpen)
	: WorkTicket(myTicketNumber, myClientId, day, month, year, myDescription), m_isOpen(true) {};

/**
 * @return bool
 */
bool ExtendedWorkTicket::GetIsOpen()
{
    return m_isOpen;
}

/**
 * @param value
 */
void ExtendedWorkTicket::SetIsOpen(bool value)
{
    m_isOpen = value;
}

/**
 * @return string
 */
void ExtendedWorkTicket::ShowWorkTicket()
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
 * @param isOpen
 */
bool ExtendedWorkTicket::SetWorkTicket(int ticketNumber, string clientId, int day, int month, int year, string description, bool isOpen)
{
	bool valid = WorkTicket::SetWorkTicket(ticketNumber, clientId, day, month, year, description);
	if (valid)
	{
		isOpen = true;
		//valid = true;
	}
	return valid;
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

ostream& operator<<(ostream& out, const ExtendedWorkTicket& ticket)
{
	out << ticket.GetTicketNumber() << endl
		<< ticket.GetClientId() << endl
		<< ticket.GetDate() << endl
		<< ticket.GetDescription() << endl
		<< ticket.m_isOpen;
	return out;
}
