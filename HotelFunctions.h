#ifndef HOTELFUNCTIONS_H
#define HOTELFUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>

class User
{
public:
    User(){}
    User(std::string lname, std::string fname, std::string uname, std::string phone, std::string email, std::string pass):
            lname(lname), fname(fname), uname(uname), phone(phone), email(email), pass(pass) {}

    std::string lname;
    std::string fname;
    std::string uname;
    std::string phone;
    std::string email;
    std::string pass;
    std::string guestName;

};

class Registerr
{
public:
    Registerr() {}
    void rgstion();
};

class Login
{
public:
    Login() {}
    void LoginAdmin();
    void login();
};


struct GuestInfo
{
    std::string name;
    std::string dob;
    std::string contact;
    std::string email;
    std::string package;
    std::string referenceNumber;
    std::string paymentMethod;
    int numGuest;
    int numDays;
    bool paid;

};

struct RoomAvail
{
    std::string packageName;
    int slotsAvail;
};

void initialRoom(RoomAvail roomAvailable[], int size);
void displayRoom(const RoomAvail roomAvailable[], int size);
void updateRoom(RoomAvail roomAvailable[], int size, const std::string& selectedPackage);
void saveInfo(const GuestInfo& guest);
bool guestExist(const std::string& guestName);
void checkIn(RoomAvail roomAvailable[], int RoomAvailSize);
void displayAllGuests();
void viewReservation(const std::string& guestName);
void checkoutGuest(const std::string& guestName);
void editInfo();


#endif // HOTELFUNCTIONS_H
