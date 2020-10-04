/**
 * Project Untitled
 */

#pragma once

#ifndef _EXTENDEDWORKTICKET_H
#define _EXTENDEDWORKTICKET_H
//#include <string>
#include "WorkTicket.h"

class ExtendedWorkTicket: public WorkTicket {
public:

    ExtendedWorkTicket();

	/**
     * @param myTicketNumber
     * @param myClientId
     * @param day
     * @param month
     * @param year
     * @param myDescription
     * @param isOpen
     */
	ExtendedWorkTicket(int myTicketNumber, std::string myClientId, int day, int month, int year, std::string myDescription, bool m_isOpen = true);


    bool GetIsOpen() const;

    /**
     * @param value
     */
    void SetIsOpen(bool value);

    virtual void ShowWorkTicket() const override;


    /**
     * @param ticketNumber
     * @param client_id
     * @param day
     * @param month
     * @param year
     * @param description
     * @param is_open
     */
   // virtual bool SetWorkTicket();
    bool SetWorkTicket(int ticketNumber, const string& client_id, int day, int month, int year, const string& description, bool is_open = true);

    /**
     * @param isOpen
     */
    void CloseTicket();
    ExtendedWorkTicket& operator=(const ExtendedWorkTicket& original); // Assignment
    operator string () const;	// (string)
    bool operator==(const ExtendedWorkTicket& original) const; // Equality
    //friend istream& operator>>(istream& in, ExtendedWorkTicket& ticket); // Input
    friend ostream& operator<<(ostream& out, const ExtendedWorkTicket& ticket); // Output

private:
    bool m_isOpen;
};

#endif //_EXTENDEDWORKTICKET_H
