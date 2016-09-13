#include "ticket.h"

Ticket::Ticket(int index, Passenger &passenger, Train &train, Spot &spot)
    : m_index(index), m_passenger(&passenger), m_train(&train), m_spot(&spot) {}

Passenger &Ticket::passenger()
{
    return *m_passenger;
}
Train &Ticket::train()
{
    return *m_train;
}
Spot &Ticket::spot()
{
    return *m_spot;
}

int Ticket::index() const
{
    return m_index;
}
