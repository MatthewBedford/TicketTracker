// Matthew Bedford mdb190007
#include "Seat.h"
#include <iostream>
#include <string>

using namespace std;

Seat::Seat()
{
    Row = 0;
    Column = ' ';
    TicketType = ' ';
}
//In the constructor set the object's data types equal to the inputs
Seat::Seat(int r, char c, char t)
{
    Row = r;
    Column = c;
    TicketType = t;
}

int Seat::getRow()
{
    return Row;
}

char Seat::getCol()
{
    return Column;
}

char Seat::getType()
{
    return TicketType;
}

void Seat::setRow(int r)
{
    Row = r;
}

void Seat::setCol(char c)
{
    Column = c;
}

void Seat::setType(char t)
{
    TicketType = t;
}

