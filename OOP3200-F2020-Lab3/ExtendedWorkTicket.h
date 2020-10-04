/**
 * Project Untitled
 */

#pragma once

#ifndef _EXTENDEDWORKTICKET_H
#define _EXTENDEDWORKTICKET_H
#include <string>
#include "WorkTicket.h"

class ExtendedWorkTicket: public WorkTicket {
public:
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
        

    bool GetIsOpen();

    /**
     * @param value
     */
    void SetIsOpen(bool value);

    void ShowWorkTicket();

    /**
     * @param isOpen
     */
   // virtual bool SetWorkTicket();
    virtual bool SetWorkTicket(int ticketNumber, string clientId, int day, int month, int year, string description, bool isOpen = true);

    /**
     * @param isOpen
     */
    void CloseTicket();

    friend ostream& operator<<(ostream& out, const ExtendedWorkTicket& ticket); // Output

private:
    bool m_isOpen;
};

#endif //_EXTENDEDWORKTICKET_H
