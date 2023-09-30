#include "HotelFunctions.h"

using namespace std;



void displayAllGuests() {
    std::ifstream guestFile("guests.txt"); // Open the guests file

    if (!guestFile.is_open()) {
        std::cerr << "Unable to open guests file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(guestFile, line)) {
        std::cout << line << std::endl; // Print each line (guest information)
    }

    guestFile.close(); // Close the file
}

void initialRoom(RoomAvail roomAvailable[], int size)
{
    roomAvailable[0] = {"Basic", 50};
    roomAvailable[1] = {"Standard", 50};
    roomAvailable[2] = {"Deluxe", 50};
    roomAvailable[3] = {"Premium", 50};
    roomAvailable[4] = {"Superior", 50};
}

void displayRoom(const RoomAvail roomAvailable[], int size)
{
    cout <<"Room Availability: " << endl;
    for (int i = 0; i < size; ++i)
    {
        cout << roomAvailable[i].packageName << ": " << roomAvailable[i].slotsAvail << " available slots" << endl;
    }
}

void updateRoom(RoomAvail roomAvailable[], int size, const string& selectedPackage)
{
    for (int i=0; i < size; ++i)
    {
        if (roomAvailable[i].packageName == selectedPackage)
        {
            roomAvailable[i].slotsAvail -= 1;
            break;
        }
    }
}

void saveInfo(const GuestInfo& guest)
{
    ofstream guestFile("guests.txt", ios::app);
    if (guestFile.is_open())
    {
        guestFile << "-------------------------" << endl;
        guestFile <<"Name of the Payor: " << guest.name << endl;
        guestFile <<"Date of Birth: " << guest.dob << endl;
        guestFile <<"Contact Number: " << guest.contact << endl;
        guestFile <<"Email Address: " << guest.email << endl;
        guestFile <<"Room Package: " << guest.package << endl;
        guestFile <<"Number of Guests: " << guest.numGuest << endl;
        guestFile <<"Number of Days: " << guest.numDays << endl;
        guestFile << "Payment Status: " << (guest.paid ? "Paid" : "Not Paid") << endl;
        if (guest.paid) {
            guestFile << "Payment Method: " << guest.paymentMethod << endl;
            guestFile << "Reference/Invoice Number: " << guest.referenceNumber << endl;
        }
        guestFile << "-------------------------" << endl;
        guestFile.close();
        cout <<"Guest information saved successfully!" << endl;

    }
    else
    {
        cout <<"Error saving guest information!" << endl;
    }
}

bool guestExist(const string& guestName)
{
    ifstream inputFile("guests.txt");
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            if (line.find("Name: " + guestName) != string::npos)
            {
                inputFile.close();
                return true;
            }
        }
        inputFile.close();
    }
    return false;
}
void makePayment(GuestInfo& guest) {
    cout << "Select a payment option:" << endl;
    cout << "1. Gcash Payment" << endl;
    cout << "2. Credit / Debit Payment" << endl;
    cout << "3. Exit (error, reservation cancelled)" << endl;
    cout << "Enter your choice: ";

    int paymentChoice;
    cin >> paymentChoice;

    switch (paymentChoice) {
        case 1:
            guest.paymentMethod = "Gcash Payment";
            break;
        case 2:
            guest.paymentMethod = "Credit / Debit Payment";
            break;
        case 3:
            cout << "Reservation cancelled." << endl;
            return;
        default:
            cout << "Invalid choice. Reservation cancelled." << endl;
            return;
    }

    cout << "Enter the reference or invoice number: ";
    cin.ignore(); // Clear the newline from the input buffer
    getline(cin, guest.referenceNumber);

    guest.paid = true;
    cout << "Payment successful for guest: " << guest.name << endl;
    cout << "Payment Method: " << guest.paymentMethod << endl;
    cout << "Reference/Invoice Number: " << guest.referenceNumber << endl;
    saveInfo(guest);
}

void checkIn(RoomAvail roomAvailable[], int RoomAvailSize)
{
    GuestInfo guest;
    cout << "Please enter the following information before we check you in: " << endl;
    cout << "Name: ";
    cin.ignore();
    getline(cin, guest.name);

    if (guestExist(guest.name))
    {
        cout << "A guest with the same name already exists in the database. Please try again." << endl;
    }
    else
    {
        cout << "Date of Birth: ";
        getline(cin, guest.dob);

        cout << "Contact Number: ";
        getline(cin, guest.contact);

        cout << "Email Address: ";
        getline(cin, guest.email);

        cout << "Available Room Packages: " << endl;
        for (int i = 0; i < RoomAvailSize; ++i)
        {
            cout << i + 1 << ". " << roomAvailable[i].packageName << endl;
        }
        int choicePack;
        do
        {
            cout << "Please select a room package (1-" << RoomAvailSize << "): ";
            cin >> choicePack;
        } while (choicePack < 1 || choicePack > RoomAvailSize);

        guest.package = roomAvailable[choicePack - 1].packageName;
        updateRoom(roomAvailable, RoomAvailSize, guest.package);

        cout << "Number of Guests: ";
        cin >> guest.numGuest;

        cout << "Number of Days: ";
        cin >> guest.numDays;

        // Ask for payment if needed
        char paymentChoice;
        cout << "Do you want to make a payment? (y/n): ";
        cin >> paymentChoice;

        if (paymentChoice == 'y' || paymentChoice == 'Y') {
            makePayment(guest);
        } else {
            guest.paid = false;
            guest.referenceNumber = "N/A";
            cout << "Guest information saved successfully! (Not Paid)" << endl;
            saveInfo(guest);
        }
    }
}

void editInfo()
{
    string guestName;
    cout <<"Enter the name of the guest: " << endl;
    cin.ignore();
    getline(cin, guestName);

    ifstream inputFile("guests.txt");
    ofstream tempFile("temp.txt");

    if (!inputFile || !tempFile)
    {
        cout << "Error opening files for editing." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inputFile, line))
    {
        if (line.find("Name of the Payor: " + guestName) != string::npos)
        {
            found = true;
            cout <<"Information found, please enter updated information: " << endl;

            GuestInfo updateGuest;
            updateGuest.name = guestName;

            cout << "Date of Birth: ";
            getline(cin, updateGuest.dob);

            cout << "Contact Number: ";
            getline(cin, updateGuest.contact);

            cout << "Email Address: ";
            getline(cin, updateGuest.email);

            cout <<"Room Package: ";
            getline(cin, updateGuest.package);

            cout << "Number of Guests: ";
            cin >> updateGuest.numGuest;

            cout << "Number of Days: ";
            cin >> updateGuest.numDays;

            tempFile << "-------------------------" << endl;
            tempFile <<"Updated Information of: " << updateGuest.name << endl;
            tempFile <<"Name: " << updateGuest.name << endl;
            tempFile <<"Date of Birth: " << updateGuest.dob << endl;
            tempFile <<"Contact Number: " << updateGuest.contact << endl;
            tempFile <<"Email Address: " << updateGuest.email << endl;
            tempFile <<"Room Package: " << updateGuest.package << endl;
            tempFile <<"Number of Guests: " << updateGuest.numGuest << endl;
            tempFile <<"Number of Days: " << updateGuest.numDays << endl;

            tempFile << "-------------------------" << endl;
            cout <<"Guest information updated successfully!" << endl;
        }
        else
        {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    remove("guests.txt");
    rename("temp.txt", "guests.txt");

    if(!found)
    {
        cout <<"Guest information not found!" << endl;
    }
}

void checkoutGuest(const std::string& guestName) {
    std::ifstream inputFile("guests.txt");
    std::ofstream tempFile("temp.txt");

    if (!inputFile || !tempFile) {
        std::cerr << "Error opening files for checkout." << std::endl;
        return;
    }

    std::string line;
    bool found = false;

    while (std::getline(inputFile, line)) {
        // Check if the line contains the guest's name
        if (line.find("Name of the Payor: " + guestName) != std::string::npos) {
            found = true;
            std::cout << "Guest information found:" << std::endl;
            std::cout << line << std::endl;

            std::cout << "Do you want to checkout? (y/n): ";
            char checkoutChoice;
            std::cin >> checkoutChoice;

            if (checkoutChoice == 'y' || checkoutChoice == 'Y') {
                // Skip writing the guest information to tempFile, effectively deleting it
                std::cout << "Guest information deleted for: " << guestName << std::endl;
                while (std::getline(inputFile, line)) {
                    if (line == "-------------------------")
                        break;
                }
            } else {
                // Write the guest information to tempFile
                tempFile << line << std::endl;
                while (std::getline(inputFile, line)) {
                    if (line == "-------------------------")
                        break;
                    tempFile << line << std::endl;
                }
            }
        } else {
            tempFile << line << std::endl;
        }
    }

    inputFile.close();
    tempFile.close();

    // Remove old guests file
    remove("guests.txt");

    // Rename temp file to guests.txt
    rename("temp.txt", "guests.txt");

    if (!found) {
        std::cout << "Guest information for " << guestName << " not found!" << std::endl;
    }
}
void viewReservation(const std::string& guestName) {
    std::ifstream inputFile("guests.txt");
    if (!inputFile.is_open()) {
        std::cout << "Unable to open guests file." << std::endl;
        return;
    }

    std::string line;
    bool found = false;
    int linesToPrint = 9;  // Number of lines to print

    while (std::getline(inputFile, line)) {
        if (line.find("Name of the Payor: " + guestName) != std::string::npos) {
            std::cout << "Reservation Details for " << guestName << ":" << std::endl;
            while (std::getline(inputFile, line) && line != "-------------------------" && linesToPrint > 0) {
                std::cout << line << std::endl;
                linesToPrint--;
            }
            found = true;
            break;
        }
    }

    inputFile.close();

    if (!found) {
        std::cout << "Reservation details not found for " << guestName << "." << std::endl;
    }
}
