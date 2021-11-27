// Matthew Bedford mdb190007
#ifndef SEAT_H
#define SEAT_H
#include <string>
#include <iostream>
using namespace std;

class Seat
{
    private:
        int Row;
        char Column;
        char TicketType;
    public:
        Seat();
        Seat(int ,char, char);
        int getRow();
        void setRow(int);
        char getCol();
        void setCol(char);
        char getType();
        void setType(char);
};

#endif // SEAT_H
