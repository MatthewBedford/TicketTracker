// Matthew Bedford mdb190007
#ifndef AUDITORIUM_H
#define AUDITORIUM_H
#include "Node.h"
#include "Seat.h"
#include <string>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

struct order
{
    string password;
    string auditorium;
    list<string> seats;
    int adultSeats = 0;
    int childSeats = 0;
    int seniorSeats = 0;
};

class Auditorium
{
    private:
        //header of the linked list that will all be connected off of this
        Node* First;

    public:
        //Constructor that puts the entire list together based of the name of the file that is given
        Auditorium(string);
        // write to file A1 with a function
        void writeToOutfile(string);
        // returns header of linked list
        Node getFirst();
        // sets header of linked list
        void setFirst(Node*);
        // writes report about how many tickets are sold and how many total seats there were at end of program
        void writeReport(int&, int&, int&, int&, int&, double&);
        // displays seats that are and are not taken to the user selecting their seats
        void displaySeating();
        // returns amount of rows in the auditorium
        int getRowNum();
        // returns amount of columns in the auditorium
        int getColNum();
        // reserves seats based on the given row and column of the starting seat and how many adult, child, and senior tickets there are
        void reserveSeats(int, char, int, int, int, list<string>&, bool&);
        // removes reserved seats
        void removeSeats(int, char, int&, int&, int&);

};

#endif // AUDITORIUM_H
