//Matthew Bedford mdb190007
#include <iostream>
#include <map>
#include <cassert>
#include <fstream>
#include "Node.h"
#include "Seat.h"
#include "Auditorium.h"
#include <string>
#include <sstream>
#include <math.h>
#include <iomanip>
#include <list>



using namespace std;

struct passwordHolder
{
    bool hasNext = false;
    string password;
    order *next = nullptr;
};

int main()
{
    map<string, list<order>> customerOrders;

    ifstream userDatabase;

    string username;
    string password;
    userDatabase.open("userdb.dat");
    while(userDatabase)
    {
        list<order> passOfUser;
        order firstOrder;
        userDatabase >> username;
        userDatabase >> password;

        firstOrder.password = password;

        passOfUser.push_front(firstOrder);

        customerOrders[username] = passOfUser;

    }

    Auditorium A1 = Auditorium("A1.txt");
    Auditorium A2 = Auditorium("A2.txt");
    Auditorium A3 = Auditorium("A3.txt");

    bool exit = false;
    while(exit != true)
    {
    //login
        bool loggedIn = false;
        while(loggedIn != true)
        {
            cout << "Please enter your username" << endl;
            cin >> username;
            int failed = 0;
            while(failed != 3)
            {
                cout << "Please enter your password" << endl;
                cin >> password;
                if(password != customerOrders[username].front().password)
                {
                    cout << "Invalid password" << endl;
                    failed++;
                }
                else
                {
                    loggedIn = true;
                    failed = 3;
                }
            }
        }

        cout << "LOGGED IN" << endl;

        bool logOut = false;
        while(logOut != true)
        {
            int userInput;
            if(username == "admin")
            {
                cout << "IN ADMIN" << endl;
                cout << endl;
                cout << "1. Print Report" << endl;
                cout << "2. Logout" << endl;
                cout << "3. Exit" << endl;
                cin >> userInput;
                while(userInput < 1 || userInput > 3)
                {
                    cin >> userInput;
                }
                if(userInput == 1)
                {
                    cout << "IN ADMIN1" << endl;
                    int totalOpen = 0;
                    int totalReserved = 0;
                    int totalAdult = 0;
                    int totalChild = 0;
                    int totalSenior = 0;
                    double allSales = 0;

                    cout << "Auditorium 1\t";
                    A1.writeReport(totalOpen, totalReserved, totalAdult, totalChild, totalSenior, allSales); cout << endl;

                    cout << "Auditorium 2\t";
                    A2.writeReport(totalOpen, totalReserved, totalAdult, totalChild, totalSenior, allSales); cout << endl;

                    cout << "Auditorium 3\t";
                    A3.writeReport(totalOpen, totalReserved, totalAdult, totalChild, totalSenior, allSales); cout << endl;

                    cout << "Total Report \t" << "Available: " << totalOpen << "\t";
                    cout << "Reserved: " << totalReserved << "\t" << "Adult: " << totalAdult << "\t";
                    cout << "Child: " << totalChild << "\t" << "Senior: " << totalSenior << "\t";
                    cout << "Sales: $" << allSales << endl;

                }
                else if(userInput == 2)
                {
                    cout << "IN ADMIN2" << endl;
                    logOut = true;
                }
                else if(userInput == 3)
                {
                    cout << "IN ADMIN3" << endl;
                    exit = true;
                    logOut = true;
                    A1.writeToOutfile("A1Final.txt");
                    A2.writeToOutfile("A2Final.txt");
                    A3.writeToOutfile("A3Final.txt");
                }
            }
            else
            {
                cout << "IN USER" << endl;
                cout << endl;
                cout << "1. Reserve Seats" << endl;
                cout << "2. View Orders" << endl;
                cout << "3. Update Order" << endl;
                cout << "4. Display Receipt" << endl;
                cout << "5. Logout" << endl;
                while(!(cin >> userInput) || userInput < 0 || userInput > 5)
                {
                    cin.clear();
                    while(cin.get() != '\n') continue;
                    cout << "Invalid Value!" << endl;
                }
                int userInput2;
                if(userInput == 1)
                {
                    cout << "IN USER1" << endl;
                    order newOrder;
                    cout << endl;
                    cout << "1. Auditorium 1" << endl;
                    cout << "2. Auditorium 2" << endl;
                    cout << "3. Auditorium 3" << endl;
                    cin >> userInput2;
                    while(userInput2 < 1 || userInput > 3)
                    {
                        cin >> userInput2;
                    }
                    if(userInput2 == 1)
                    {
                        A1.displaySeating();
                        newOrder.auditorium = "Auditorium 1";
                    }
                    else if(userInput2 == 2)
                    {
                        A2.displaySeating();
                        newOrder.auditorium = "Auditorium 2";
                    }
                    else if(userInput2 == 3)
                    {
                        A3.displaySeating();
                        newOrder.auditorium = "Auditorium 3";
                    }

                    int rowNum;
                    cout << "Please enter row number" << endl;
                    cin >> rowNum;
                    while(rowNum < 0)
                    {
                        cin >> rowNum;
                    }

                    char colLetter;
                    cout << "Please enter starting seat letter" << endl;
                    cin >> colLetter;
                    while(colLetter < 'A' || colLetter > 'Z')
                    {
                        cin >> colLetter;
                    }

                    int adultNum;
                    cout << "Please enter number of adult tickets" << endl;
                    cin >> adultNum;
                    while(adultNum < 0)
                        cin >> adultNum;
                    newOrder.adultSeats = adultNum;

                    int childNum;
                    cout << "Please enter number of child tickets" << endl;
                    cin >> childNum;
                    while(childNum < 0)
                        cin >> childNum;
                    newOrder.childSeats = childNum;

                    int seniorNum;
                    cout << "Please enter number of senior tickets" << endl;
                    cin >> seniorNum;
                    while(seniorNum < 0)
                        cin >> seniorNum;
                    newOrder.seniorSeats = seniorNum;

                    bool rand = false;

                    cout << "BEFORE RESERVATION" << endl;
                    if(userInput2 == 1)
                    {
                        A1.reserveSeats(rowNum, colLetter, adultNum, childNum, seniorNum, newOrder.seats, rand);
                    }
                    else if(userInput2 == 2)
                    {
                        A2.reserveSeats(rowNum, colLetter, adultNum, childNum, seniorNum, newOrder.seats, rand);
                    }
                    else if(userInput2 == 3)
                    {
                        A3.reserveSeats(rowNum, colLetter, adultNum, childNum, seniorNum, newOrder.seats, rand);
                    }
                    cout << "AFTER RESERVATION" << endl;

                    if(newOrder.seats.size() > 0)
                    {
                        customerOrders[username].push_back(newOrder);
                    }
                    else
                        continue;
                }
                else if(userInput == 2)
                {
                    cout << "IN USER2" << endl;
                    if(customerOrders[username].size() > 1)
                    {
                        order tempOrder = customerOrders[username].front();
                        customerOrders[username].pop_front();
                        customerOrders[username].push_back(tempOrder);
                        for(int i = 0; i < (int)(customerOrders[username].size()) - 1; i++)
                        {
                            tempOrder = customerOrders[username].front();
                            customerOrders[username].pop_front();
                            cout << tempOrder.auditorium << ", ";

                            for(int i = 0; i < (int)(tempOrder.seats.size()); i++)
                            {
                                string temp = tempOrder.seats.front();
                                if((int)(tempOrder.seats.size()) > 1)
                                {
                                    tempOrder.seats.pop_front();
                                    if(i == 0)
                                        cout << temp;
                                    else
                                        cout << "," << temp;
                                    tempOrder.seats.push_back(temp);
                                }
                                else
                                    cout << temp;
                            }

                            cout << endl << tempOrder.adultSeats << " adult, " << tempOrder.childSeats << " child, " << tempOrder.seniorSeats << " senior" << endl;

                            customerOrders[username].push_back(tempOrder);
                        }
                    }
                    else
                        cout << "No orders";
                }
                else if(userInput == 3)
                {
                    cout << "IN USER3" << endl;
                    int counter = 1;
                    if(customerOrders[username].size() > 1)
                    {
                        order *tempOrder = new order;
                        tempOrder = &(customerOrders[username].front());
                        customerOrders[username].pop_front();
                        customerOrders[username].push_back(*tempOrder);

                        for(int i = 0; i < (int)(customerOrders[username].size()) - 1; i++)
                        {
                            tempOrder = &(customerOrders[username].front());
                            customerOrders[username].pop_front();
                            cout << counter << ".) ";
                            cout << tempOrder->auditorium << ", ";
                            for(int i = 0; i < (int)(tempOrder->seats.size()); i++)
                            {
                                string temp = tempOrder->seats.front();
                                if((int)(tempOrder->seats.size()) > 1)
                                {
                                    tempOrder->seats.pop_front();
                                    if(i == 0)
                                        cout << temp;
                                    else
                                        cout << "," << temp;
                                    tempOrder->seats.push_back(temp);
                                }
                                else
                                    cout << temp;
                            }
                            cout << endl << tempOrder->adultSeats << " adult, " << tempOrder->childSeats << " child, " << tempOrder->seniorSeats << " senior" << endl;

                            counter++;

                            customerOrders[username].push_back(*tempOrder);

                        }

                        cout << "Which order would you like to update?" << endl;
                        int userInput4;
                        cin >> userInput4;
                        while(userInput4 > counter)
                        {
                            cout << "That order does not exist. Select a different one." << endl;
                            cin >> userInput4;
                        }

                        int newCounter = 1;
                        for(order & i : customerOrders[username])
                        {
                            if(newCounter == userInput4)
                            newCounter++;
                            tempOrder = &i;
                        }

                        cout << "1. Add tickets to order" << endl;
                        cout << "2. Delete tickets from order" << endl;
                        cout << "3. Cancel Order" << endl;
                        int userInput3;
                        cin >> userInput3;
                        bool finished = false;
                        while(finished != true)
                        {
                        if(userInput3 == 1)
                        {
                            int rowNum2;
                            char colLetter2;
                            int adultNum2;
                            int childNum2;
                            int seniorNum2;
                            finished = true;
                            cout << "What row num" << endl;
                            cin >> rowNum2;
                            cout << "What col letter" << endl;
                            cin >> colLetter2;
                            cout << "What adult num" << endl;
                            cin >> adultNum2;
                            cout << "What child num" << endl;
                            cin >> childNum2;
                            cout << "What senior num" << endl;
                            cin >> seniorNum2;

                            if(tempOrder->auditorium == "Auditorium 1")
                                A1.reserveSeats(rowNum2, colLetter2, adultNum2, childNum2, seniorNum2, tempOrder->seats, finished);
                            else if(tempOrder->auditorium == "Auditorium 2")
                                A2.reserveSeats(rowNum2, colLetter2, adultNum2, childNum2, seniorNum2, tempOrder->seats, finished);
                            else
                                A3.reserveSeats(rowNum2, colLetter2, adultNum2, childNum2, seniorNum2, tempOrder->seats, finished);

                            if(finished == true)
                            {
                                tempOrder->adultSeats = tempOrder->adultSeats + adultNum2;
                                tempOrder->childSeats = tempOrder->childSeats + childNum2;
                                tempOrder->seniorSeats = tempOrder->seniorSeats + seniorNum2;
                            }
                        }
                        else if(userInput3 == 2)
                        {
                            cout << "What is the row of the ticket you wish to delete?" << endl;
                            int rowDelete;
                            cin >> rowDelete;

                            cout << "What is the column of the ticket you wish to delete?" << endl;
                            char colDelete;
                            cin >> colDelete;

                            string placeDelete = to_string(rowDelete) + colDelete;

                            for(int i = 0; i < (int)(tempOrder->seats.size()); i++)
                            {
                                string currentNode = tempOrder->seats.front();
                                tempOrder->seats.pop_front();
                                if(currentNode == placeDelete)
                                {
                                    if(tempOrder->auditorium == "Auditorium 1")
                                        A1.removeSeats(rowDelete, colDelete, tempOrder->adultSeats, tempOrder->childSeats, tempOrder->seniorSeats);
                                    else if(tempOrder->auditorium == "Auditorium 2")
                                        A2.removeSeats(rowDelete, colDelete, tempOrder->adultSeats, tempOrder->childSeats, tempOrder->seniorSeats);
                                    else
                                        A3.removeSeats(rowDelete, colDelete, tempOrder->adultSeats, tempOrder->childSeats, tempOrder->seniorSeats);
                                    finished = true;
                                }
                                else
                                    tempOrder->seats.push_back(currentNode);
                            }
                            if(finished != true)
                                cout << "That ticket is not in this order" << endl;
                        }
                        else if(userInput3 == 3)
                        {
                            for(int i = 0; i < (int)(tempOrder->seats.size()); i++)
                            {
                                string nodePlace = tempOrder->seats.front();
                                tempOrder->seats.pop_front();

                                char letter = nodePlace[nodePlace.length() - 1];
                                string row = nodePlace.substr(0,nodePlace.length() - 1);
                                int rowInt;
                                stringstream RowString(row);
                                RowString >> rowInt;

                                if(tempOrder->auditorium == "Auditorium 1")
                                    A1.removeSeats(rowInt, letter, tempOrder->adultSeats, tempOrder->childSeats, tempOrder->seniorSeats);
                                else if(tempOrder->auditorium == "Auditorium 2")
                                    A2.removeSeats(rowInt, letter, tempOrder->adultSeats, tempOrder->childSeats, tempOrder->seniorSeats);
                                else
                                    A3.removeSeats(rowInt, letter, tempOrder->adultSeats, tempOrder->childSeats, tempOrder->seniorSeats);
                            }
                            finished = true;
                        }
                        }
                    }
                    else
                        cout << "no orders" << endl;
                }
                else if(userInput == 4)
                {
                    cout << "IN USER4" << endl;
                    double totalSales = 0.00;
                    if(customerOrders[username].size() > 1)
                    {
                        order tempOrder = customerOrders[username].front();
                        customerOrders[username].pop_front();
                        customerOrders[username].push_back(tempOrder);
                        for(int i = 0; i < (int)(customerOrders[username].size() - 1); i++)
                        {
                            order tempOrder = customerOrders[username].front();
                            customerOrders[username].pop_front();

                            cout << tempOrder.auditorium << ", ";

                            for(int i = 0; i < (int)(tempOrder.seats.size()); i++)
                            {
                                string temp = tempOrder.seats.front();
                                tempOrder.seats.pop_front();
                                if(i == 0)
                                    cout << temp;
                                else
                                    cout << "," << temp;
                                tempOrder.seats.push_back(temp);
                            }

                            cout << endl << tempOrder.adultSeats << " adult, " << tempOrder.childSeats << " child, " << tempOrder.seniorSeats << " senior" << endl;

                            double orderSales = 0.00;
                            for(int i = 0; i < tempOrder.adultSeats; i++)
                            {
                                orderSales += 10.00;
                                totalSales += 10.00;
                            }
                            for(int i = 0; i < tempOrder.childSeats; i++)
                            {
                                orderSales += 5.00;
                                totalSales += 5.00;
                            }
                            for(int i = 0; i < tempOrder.seniorSeats; i++)
                            {
                                orderSales += 7.50;
                                totalSales += 7.50;
                            }

                            cout << "Order Total: $" << setprecision(2) << fixed << orderSales << endl << endl;

                            customerOrders[username].push_back(tempOrder);
                        }
                        cout << "Customer Total: $" << setprecision(2) << fixed << totalSales << endl;
                    }
                }
                else if(userInput == 5)
                {
                    cout << "IN USER5" << endl;
                    logOut = true;
                }
            }
        }
    }
    return 0;
    }
