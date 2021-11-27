// Matthew Bedford mdb190007
#include "Auditorium.h"
#include <math.h>
#include <iomanip>
#include <iostream>
#include <list>

Auditorium::Auditorium(string filename)
{
    //start by going into the file and finding out how many columns and rows are needed in the linked list
    string check;
    int row = 0;
    int col = 0;
    ifstream infile;
    infile.open(filename);
    //find columns by reading an entire time and setting it equal to that length. Just to be sure
    //add up each rows length and then divide that total number by the number of rows to get the number of columns.
    while(infile >> check)
    {
            col += (int)(check.length());
    }
    infile.close();

    //get number of rows by counting how many lines there are
    infile.open(filename);
    while(getline(infile,check))
    {
        row++;
    }

    //get number of columns by dividing total number of things in the file by the number of rows
    col = col/row;
    infile.close();

    //Now create a linked list by using these variables col and row as your parameters so that
    //you do not set a value on the end of a row that should have advanced to next column

    //keep track of the seat row,col, and seat type by advancing col by one as each new piece of data is read in
    //and then resetting col and adding to row when it is time to form a new row. Keep track of seat type by reading in
    //the type into the payloadContent variable. Then, when traversing to node of choice, put seat object with these
    //parameters in that node.
    int curRow = 1;
    char curCol = 'A';
    char payloadContent;

    infile.open(filename);
    //create temporary node so that you do not have to change the header of the list in order to traverse it
    Node *currentNode;
    //Use outside for loop to track the row number and inside for loop to track the current row's column number
    for(int i = 0; i < row; i++)
    {
        curCol = 'A';
        for(int j = 0; j < col; j++)
        {
            //for each node, read in new data to the variable holding the payload
            infile >> payloadContent;
            currentNode = First;
            //if the position of the for loops is at 0,0 then this is the header of the list and is instantiated as so.
            if(i == 0 && j == 0)
            {
                //create node and point header at this node
                Node* newNode = new Node(curRow,curCol, payloadContent);
                setFirst(newNode);
            }
            //if the position of the for loops is at 0 for the row, and anything greater than 0 for the column, you only have to point
            //the right of the current node to the new node and then the left of the new node back to the current node
            else if(i == 0 && j > 0)
            {
                //first row so initialize object from the left only. Point at object to left and point from that object to this.
                for(int k = 0; k < j - 1; k++)
                    currentNode = (currentNode->getRight());

                //create new node and point the right of the current node to this and then the new node's left to the current node
                Node *newNode = new Node(curRow, curCol, payloadContent);
                currentNode->setRight(newNode);
                currentNode->getRight()->setLeft(currentNode);
            }
            //if for loops are at 0 for column, and greater than 0 for row. Only have to point down of current node and new node back up to current node.
            else if(i > 0 && j == 0)
            {
                //initialize from object above and make that object point at this and this point at that
                for(int k = 0; k < i - 1; k++)
                    currentNode = (currentNode->getDown());

                //create new node and point the down pointer of the current node at it and the up pointer of the new node at the current node
                Node *newNode = new Node(curRow, curCol, payloadContent);
                currentNode->setDown(newNode);
                currentNode->getDown()->setUp(currentNode);
            }
            //if both for loops are greater than 0, then you must go to the point of the list to the left of the new node and point that right at this node
            //and this new node back left at that. Then you must go to the node of the list that is above the new node and point that down at this new node and the new
            //node back up at that.
            else if(i > 0 && j > 0)
            {
                //initialize from object left and point back at it. Point to object above and have that object point back at this.
                //First do one from the left. Go down i instead of i - 1 and right j - 1;
                for(int k = 0; k < i; k++)
                    currentNode = (currentNode->getDown());

                for(int k = 0; k < j - 1; k++)
                    currentNode = (currentNode->getRight());

                //create new node to be used for both as it is the same node that these are pointing at
                Node* newNode = new Node(curRow, curCol, payloadContent);

                //point the right pointer of the node to the left of the new node at the new node and then the left of the new node back at it.
                currentNode->setRight(newNode);
                currentNode->getRight()->setLeft(currentNode);

                //Now do it from above. Reset currentNode first. Go all the way left but one away from above.
                currentNode = First;

                for(int k = 0; k < j; k++)
                    currentNode = (currentNode->getRight());
                for(int k = 0; k < i - 1; k++)
                    currentNode = (currentNode->getDown());

                //point the down pointer of the node above the new node at the new node and then the up of the new node back at it.
                currentNode->setDown(newNode);
                currentNode->getDown()->setUp(currentNode);
            }
            curCol++;
        }
        curRow++;
    }
}

void Auditorium::writeToOutfile(string file)
{
    //open outfile
    ofstream outfile(file);

    //output the header node first to the text.
    outfile << (First->getPayload().getType());

    //use a temporary node to point at what is being printed
    Node *printedNode = First;
    int rowCounter = 0;
    //while below the node is not null AND to the right of the node is not null, then
    //the pointer is not yet at the end of the list and must go on
    while(printedNode->getDown() != nullptr || printedNode->getRight() != nullptr)
    {
        //if to the right is null then the next one is down rowCounter amount of times from the header and printed out
        if(printedNode->getRight() == nullptr)
        {
            rowCounter++;
            printedNode = First;
            for(int h = 0; h < rowCounter; h++)
            {
                printedNode = printedNode->getDown();
            }
            outfile << "\n" << printedNode->getPayload().getType();
        }
        //else then the node is on the current row and printed out as such
        else
        {
            printedNode = printedNode->getRight();
            outfile << printedNode->getPayload().getType();
        }

    }
}

void Auditorium::writeReport(int &totalOpen, int &totalReserved, int &totalAdult, int &totalChild, int &totalSenior, double &allSales)
{
    //create counters to count all of the measurements in the report
    int totalSeats = 0;
    int adults = 0;
    int children = 0;
    int seniors = 0;
    float totalSales = 0.00;

    int rowCounter = 0;
    char temp;
    float childSale = 5;
    float adultSale = 10;
    float seniorSale = 7.5;

    //create temp node so that the entire list can be checked without changing the header
    Node *checkedNode = First;
    //first check header for a value and add to numbers as such
    if(checkedNode != nullptr)
    {
        //each time there is a value whether it be '.' or any of the type of seats, add to totalSeats
        temp = checkedNode->getPayload().getType();
        totalSeats++;
        //if the type in the node is A, then it is an adult ticket and cost $10
        if(temp == 'A')
        {
            adults++;
            totalSales+=adultSale;
        }
        //if the type in the node is C, then it is an child ticket and cost $5
        else if(temp == 'C')
        {
            children++;
            totalSales+=childSale;
        }
        //if the type in the node is S, then it is an senior ticket and cost $7.5
        else if(temp == 'S')
        {
            seniors++;
            totalSales+=seniorSale;
        }
    }

    //After checking header, continue to check rest of list until end
    while(checkedNode->getDown() != nullptr || checkedNode->getRight() != nullptr)
    {
        //if only the right is nullptr then go to the next row to check
        if(checkedNode->getRight() == nullptr)
        {
            //go to next row
            rowCounter++;
            checkedNode = First;
            for(int h = 0; h < rowCounter; h++)
                checkedNode = checkedNode->getDown();

            temp = checkedNode->getPayload().getType();
            totalSeats++;
            //same value check from header
            if(temp == 'A')
            {
                adults++;
                totalSales+= adultSale;
            }
            else if(temp == 'C')
            {
                children++;
                totalSales+= childSale;
            }
            else if(temp == 'S')
            {
                seniors++;
                totalSales+= seniorSale;
            }
        }
        //if the right is not nullptr then there is no need to go to next row
        else
        {
            //go to the right instead of next row
            checkedNode = checkedNode->getRight();
            temp = checkedNode->getPayload().getType();
            totalSeats++;
            //same value check from header
            if(temp == 'A')
            {
                adults++;
                totalSales+= adultSale;
            }
            else if(temp == 'C')
            {
                children++;
                totalSales+= childSale;
            }
            else if(temp == 'S')
            {
                seniors++;
                totalSales+= seniorSale;
            }
        }
    }

    //print out all important value types at end with appropriate syntax.
    cout << "Available: " << totalSeats - (adults + children + seniors) << "\t";
    cout << "Reserved: " << (adults + children + seniors) << "\t";
    cout << "Adult: " << adults << "\t";
    cout << "Child: " << children << "\t";
    cout << "Senior: " << seniors << "\t";
    cout << "Sales: $" << setprecision(2) << fixed << totalSales  << endl;


    totalOpen = (totalOpen + totalSeats - (adults + children + seniors));
    totalReserved = (totalReserved + (adults + children + seniors));
    totalAdult = (totalAdult + adults);
    totalChild = (totalChild + children);
    totalSenior = (totalSenior + seniors);
    allSales = (allSales + totalSales);
}

void Auditorium::displaySeating()
{
    // First display letters at the top that signify what column the seat is in
    // Do this by first getting the number of columns
    int colCounter = 0;
    char topLine = 'A';
    Node *printedNode = First;
    if(printedNode != nullptr)
        colCounter++;
    while(printedNode != nullptr && printedNode->getRight() != nullptr)
    {
        colCounter++;
        printedNode = printedNode->getRight();
    }

    //Use the number of columns found to put the characters at the top starting at A
    if(colCounter > 0)
    {
        cout << "  ";
        for(int i = 0; i < colCounter; i++)
        {
            cout << topLine;
            topLine++;
        }
        cout << endl;
    }

    //Next print out the number of rows that there are by first checking if there is at least one row and then printing a 1 if so.
    printedNode = First;
    if(First != nullptr)
    {
        if(printedNode->getPayload().getType() == '.')
            cout << "1 " << printedNode->getPayload().getType();
        else
            cout << "1 " << "#";
    }
    int rowCounter = 0;
    char temp;
    //while the array is still going as in before programs, print out the array
    //but now if the array goes to next row print out the number of the row as well
    //Also change values other than periods to #
    while(printedNode->getDown() != nullptr || printedNode->getRight() != nullptr)
    {
        //if the right is null, then go to the next row to print out but print out the row number beforehand
        if(printedNode->getRight() == nullptr)
        {
            rowCounter++;
            printedNode = First;
            for(int h = 0; h < rowCounter; h++)
            {
                printedNode = printedNode->getDown();
            }
            temp = printedNode->getPayload().getType();
            //if . then print it out but otherwise use #
            if(temp == '.')
                cout << "\n" << (rowCounter+1) << " " << temp;
            else
                cout << "\n" << (rowCounter+1) << " " << "#";
        }
        //else if the right is not null then the data is on the current row and can be printed on the current row
        else
        {
            printedNode = printedNode->getRight();

            temp = printedNode->getPayload().getType();
            //if . then print it out but otherwise use #
            if(temp == '.')
                cout << temp;
            else
                cout << "#";
        }
    }
    cout << "\n";
}

//return number of columns in auditorium
int Auditorium::getColNum()
{
    //create temp node to count columns
    Node* tempNode;
    int colNum = 0;
    //first check if the header exist and if it does then add one to columns
    if(First != nullptr)
    {
        tempNode = First;
        colNum++;
    }

    //next, while the list can still go to the right without being null, then there is another column there
    //and colNum is increased by 1
    while(tempNode != nullptr)
    {
        if(tempNode->getRight() != nullptr)
        {
            tempNode = tempNode->getRight();
            colNum++;
        }
        else
            tempNode = nullptr;
    }
    //colNum is returned as number of columns
    return colNum;
}

//return number of rows in auditorium
int Auditorium::getRowNum()
{
    //create temp node to count rows
    Node* tempNode;
    int rowNum = 0;
    //first check if the header exist and if it does then add one to rows
    if(First != nullptr)
    {
        tempNode = First;
        rowNum++;
    }

    //while list can still go down without being null, then there is another row there
    //and rowNum is increased by 1
    while(tempNode != nullptr)
    {
        if(tempNode->getDown() != nullptr)
        {
            tempNode = tempNode->getDown();
            rowNum++;
        }
        else
            tempNode = nullptr;
    }
    //rowNum is returned as number of rows
    return rowNum;
}

void Auditorium::removeSeats(int Row, char Col, int &adult, int &child, int &senior)
{
    Node* removeSeat = First;

    for(int i = 1; i < Row; i++)
        removeSeat = removeSeat->getDown();
    for(char i = 'A'; i < Col; i++)
        removeSeat = removeSeat->getRight();

    if(removeSeat->getPayload().getType() == 'A')
        adult--;
    else if(removeSeat->getPayload().getType() == 'C')
        child--;
    else if(removeSeat->getPayload().getType() == 'S')
        senior--;

    removeSeat->getPayload().setType('.');

}

void Auditorium::reserveSeats(int rowSelected, char colSelected, int adultSeats, int childSeats, int seniorSeats, list<string>& seats, bool &addition)
{
    //create pointer that will start at the users selected starting seat
    //create boolean statement to determine if the seats selected are capable of being reserved
    Node* startingSeat = First;
    bool reservable = true;

    //get number of col by adding onto 'A' until it is equal to col selected
    int colSelectedNum = 1;
    char currentCol = 'A';
    bool colFound = false;
    while(colFound != true)
    {
        if(currentCol == colSelected)
            colFound = true;
        else
        {
            colSelectedNum++;
            currentCol++;
        }
    }

    //for loops to get the startingSeat pointer to the actual starting seat using the chosen row and col
    for(int i = 1; i < rowSelected; i++)
        startingSeat = startingSeat->getDown();
    for(int i = 1; i < colSelectedNum; i++)
        startingSeat = startingSeat->getRight();

    //then for loop for how many seats there are being reserved that checks that number of seats to the
    //right of starting seat to see if they are capable of being reserved
    int totalSeats = (adultSeats + childSeats + seniorSeats);
    Node* checkSeat = startingSeat;

    //look through each seat following starting seat and make sure they are all vacant. Return false if not.
    for(int i = 0; i < totalSeats; i++)
    {
        if(checkSeat->getPayload().getType() != '.')
            reservable = false;
        if(checkSeat->getRight() == nullptr && i != totalSeats - 1)
            reservable = false;
        else if(checkSeat->getRight() != nullptr)
            checkSeat = checkSeat->getRight();
    }

    Seat tempSeat;

    //if they are all vacant then reservable is true
    if(reservable == true)
    {
        //for how ever many adult tickets there were, reserve those
        for(int i = 0; i < adultSeats; i++)
        {
            seats.push_back(to_string(rowSelected) + colSelected);
            tempSeat = Seat(rowSelected,colSelected,'A');
            startingSeat->setPayload(tempSeat);
            colSelected++;
            startingSeat = startingSeat->getRight();
        }
        //for how ever many child tickers there were, reserve those
        for(int j = 0; j < childSeats; j++)
        {
            seats.push_back(to_string(rowSelected) + colSelected);
            tempSeat = Seat(rowSelected,colSelected,'C');
            startingSeat->setPayload(tempSeat);
            colSelected++;
            startingSeat = startingSeat->getRight();
        }
        //for how ever many senior tickets there were, reserve those
        for(int k = 0; k < seniorSeats; k++)
        {
            seats.push_back(to_string(rowSelected) + colSelected);
            tempSeat = Seat(rowSelected,colSelected,'S');
            startingSeat->setPayload(tempSeat);
            colSelected++;
            if(k != (seniorSeats-1))
                startingSeat = startingSeat->getRight();
        }
    }
    else if(addition == true)
    {
        cout << "seats not available" << endl;
        addition = false;
    }
    // if they are not all vacant then you must search for best possible seats and offer those.
    else
    {
        bool otherSeatsAvailable = false;
        int totalRows = 0;
        int totalCols = 0;
        Node* tempNode;
        startingSeat = First;

        //Getting rows of the list
        if(First != nullptr)
        {
            tempNode = First;
            totalRows++;
        }
        while(tempNode != nullptr)
        {
            if(tempNode->getDown() != nullptr)
            {
                tempNode = tempNode->getDown();
                totalRows++;
            }
            else
                tempNode = nullptr;
        }

        //Getting columns of the list
        if(First != nullptr)
        {
            tempNode = First;
            totalCols++;
        }
        while(tempNode != nullptr)
        {
            if(tempNode->getRight() != nullptr)
            {
                tempNode = tempNode->getRight();
                totalCols++;
            }
            else
                tempNode = nullptr;
        }

        //Getting the middle part in which the code will begin to start checking for closest available spot
        //First go to middle then go left half of the total number of seats to center the wanted seats.
        for(int i = 1; i < ((totalCols+1)/2); i++)
            startingSeat = startingSeat->getRight();
        for(int i = 1; i < ((totalRows+1)/2); i++)
            startingSeat = startingSeat->getDown();
        for(int i = 0; i < ((totalSeats)/2); i++)
            startingSeat = startingSeat->getLeft();

        int startingRow = 0;
        int startingCol = 0;

        //find row of the middle portion
        startingRow = startingSeat->getPayload().getRow();

        colFound = false;
        colSelectedNum = 1;
        currentCol = 'A';
        //find col of the middle portion
        while(colFound != true)
        {
            if(currentCol == startingSeat->getPayload().getCol())
                colFound = true;
            else
            {
                colSelectedNum++;
                currentCol++;
            }
        }

        startingCol = colSelectedNum;
        double tempShortestDist = 100000;
        Node* tempShortest = new Node();
        Node* newStartingSeat = First;
        Node* tempCurrentSeat;
        colSelectedNum = 0;

        while(newStartingSeat->getRight() != nullptr || newStartingSeat->getDown() != nullptr)
        {
            tempCurrentSeat = newStartingSeat;
            reservable = true;
            for(int i = 0; i < totalSeats; i++)
            {
                if(tempCurrentSeat->getPayload().getType() != '.')
                    reservable = false;
                if(tempCurrentSeat->getRight() == nullptr && i != totalSeats - 1)
                    reservable = false;
                else if(tempCurrentSeat->getRight() != nullptr)
                    tempCurrentSeat = tempCurrentSeat->getRight();
                else
                    reservable = false;
            }

            if(reservable == true)
            {
                double tempDistance = abs(sqrt((((newStartingSeat->getPayload().getCol() - 'A' + 1)-startingCol)*((newStartingSeat->getPayload().getCol() - 'A' + 1)-startingCol)) + (newStartingSeat->getPayload().getRow()-startingRow)*(newStartingSeat->getPayload().getRow()-startingRow)));
                //if distance is smaller than current shortest distance, make it the new best seating
                if(tempDistance < tempShortestDist)
                {
                    tempShortest = newStartingSeat;
                    tempShortestDist = tempDistance;
                }
                else if(tempDistance == tempShortestDist)
                {
                    //if new node that is equal to shortest is a closer row to the middle of the auditorium, that row is now the shortest
                    if(abs(newStartingSeat->getPayload().getRow() - startingRow) < abs(tempShortest->getPayload().getRow() - startingRow))
                        tempShortest = newStartingSeat;
                    //else if they are equal distance away from middle, the row with the smaller number is the shortest
                    else if(abs(newStartingSeat->getPayload().getRow() - startingRow) == abs(tempShortest->getPayload().getRow() - startingRow))
                    {
                        if(newStartingSeat->getPayload().getRow() < tempShortest->getPayload().getRow())
                            tempShortest = newStartingSeat;
                    }
                }
            }

            if(newStartingSeat->getRight() != nullptr)
                newStartingSeat = newStartingSeat->getRight();
            else
            {
                colSelectedNum++;
                newStartingSeat = First;
                for(int i = 0; i < colSelectedNum; i++)
                    newStartingSeat = newStartingSeat->getDown();
            }

        }

        //this means that there was actually a place for the seats to go
        if(tempShortestDist != 100000)
            otherSeatsAvailable = true;

        if(otherSeatsAvailable == true)
        {
            //if there is a place for the seats to go then print out the places that they are able to go
            string userAnswer;
            if(totalSeats == 1)
                cout << tempShortest->getPayload().getRow() << tempShortest->getPayload().getCol() << " - " << tempShortest->getPayload().getRow() << tempShortest->getPayload().getCol();
            else
            {
                char secondCol = tempShortest->getPayload().getCol();
                for(int i = 1; i < totalSeats; i++)
                    secondCol++;
                cout << tempShortest->getPayload().getRow() << tempShortest->getPayload().getCol() << " - " << tempShortest->getPayload().getRow() << (secondCol);
            }
            //prompt if the user would like to reserve the best available seats
            cout << endl << "These are the best available seats. Y or N?" << endl;
            cin >> userAnswer;
            if(userAnswer == "Y")
            {
                //for how ever many adult tickets there were, reserve those
                for(int i = 0; i < adultSeats; i++)
                {
                    seats.push_back(to_string(tempShortest->getPayload().getRow()) + tempShortest->getPayload().getCol());
                    tempSeat = Seat(tempShortest->getPayload().getRow(),tempShortest->getPayload().getCol(),'A');
                    tempShortest->setPayload(tempSeat);
                    tempShortest = tempShortest->getRight();
                }
                //for how ever many child tickers there were, reserve those
                for(int j = 0; j < childSeats; j++)
                {
                    seats.push_back(to_string(tempShortest->getPayload().getRow()) + tempShortest->getPayload().getCol());
                    tempSeat = Seat(tempShortest->getPayload().getRow(),tempShortest->getPayload().getCol(),'C');
                    tempShortest->setPayload(tempSeat);
                    tempShortest = tempShortest->getRight();
                }
                //for how ever many senior tickets there were, reserve those
                for(int k = 0; k < seniorSeats; k++)
                {
                    seats.push_back(to_string(tempShortest->getPayload().getRow()) + tempShortest->getPayload().getCol());
                    tempSeat = Seat(tempShortest->getPayload().getRow(),tempShortest->getPayload().getCol(),'S');
                    tempShortest->setPayload(tempSeat);
                    if(k != (seniorSeats-1))
                        tempShortest = tempShortest->getRight();
                }
            }
        }
        else
        {
            cout << "no seats available";
        }
    }
}

Node Auditorium::getFirst()
{
    return *First;
}

void Auditorium::setFirst(Node* F)
{
    First = F;
}
