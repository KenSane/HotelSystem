#include <iostream>
#include "HotelFunctions.h"
using namespace std;

int main()
{
    const int roomAvailableSize = 5;
    RoomAvail roomAvailable[roomAvailableSize];
    GuestInfo guest;

    initialRoom(roomAvailable, roomAvailableSize);


    int choice;
    int choice2;
    int choice3;
    Registerr reg;
    Login log;
    string guestName;
    string adminUsername = "ADMIN";
    string adminPassword = "adminonly";
    string inputAdmin,inputAdminPass;

    //Main Menu
    do{
        system("cls");
        std::cout << "Welcome to Grand Maple Hotel!"<< std::endl;
        std::cout << "----------------------------------------------" << std::endl;
        std::cout << "1. User Login" << std::endl;
        std::cout << "2. Register" << std::endl;
        std::cout << "3. Admin" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;


        switch (choice)
        {

            case 1:
                //login
                system("cls");
                log.login();

                do {
                    std::cout << "Welcome to Grand Maple Hotel!"<< std::endl;
                    std::cout << "----------------------------------------------" << std::endl;
                    cout << "Please select an option: " << endl;
                    cout << "[1] Check-in" << endl; // DONE
                    cout << "[2] Check Room Availability" << endl; //DONE
                    cout << "[3] Check my Reservations"<< endl;
                    cout << "Enter your choice: ";
                    cin >> choice2;
                    system("cls");

                    switch (choice2)
                    {
                        case 1:
                            checkIn(roomAvailable, roomAvailableSize);
                            break;

                        case 2:
                            displayRoom(roomAvailable, roomAvailableSize);
                            break;

                        case 3:
                            cout << "Enter the name of the payor: ";
                            cin.ignore();
                            getline(cin, guestName);
                            viewReservation(guestName);
                            cout << "Thank you for using the Grand Maple Hotel Reservation System!" << endl;
                            break;

                        default:
                            cout <<"Invalid choice. Please try again." << endl;
                            break;
                    }

                } while (choice2 != 5);
            case 2:
                //Registration
                system("cls");
                reg.rgstion();
                break;

            case 3:
                system("cls");
                cout << "Admin Username: ";
                cin.ignore();
                getline(cin, inputAdmin);
                cout << "Admin Password: ";
                getline(cin, inputAdminPass);
                if (adminUsername == inputAdmin &&  adminPassword == inputAdminPass) {
                    // Admin is logged in
                    do {
                        cout << "Welcome to Grand Maple Hotel (Admin)!" << endl;
                        cout << "----------------------------------------------" << endl;
                        cout << "Please select an option: " << endl;
                        cout << "[1] View All Guest" << endl;
                        cout << "[2] Checkout a Guest" << endl;
                        cout << "[3] View Unpaid Reservation:" << endl;
                        cout << "[4] Delete Unpaid Reservation:" << endl;
                        cout << "[5] Exit:" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice3;

                        switch (choice3)
                        {
                            case 1:
                                checkIn(roomAvailable, roomAvailableSize);
                                break;

                            case 2:
                                displayAllGuests();
                                // Add code for checking room availability
                                break;

                            case 3:
                                std::cout << "Enter guest name to checkout: ";
                                std::cin.ignore();  // Ignore the newline left by previous inputs
                                std::getline(std::cin, guestName);
                                checkoutGuest(guestName);
                                break;

                            case 4:
                                editInfo();
                                break;

                            default:
                                cout << "Invalid choice. Please try again." << endl;
                                break;
                        }
                    } while (choice3 != 5);
                } else {
                    cout << "Invalid admin credentials." << endl;
                }
                break;

            default:
                std::cout << "\t\tWrong Input" << std::endl;
                break;
        }
    }
    while(choice != 3);

    return 0;
}
