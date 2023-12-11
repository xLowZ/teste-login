#include <iostream>
#include "../include/UserManager.h"
#include "../include/Input.h"
#include "../include/Settings.h"

struct Flags
{
    bool control{ true };
    bool logged_in{ false };
};

void printMenu(const Flags flag);
void menuInfo();
int  getChoice();
int  getInfoChoice();
void management(UserManager& UM, Flags& flag);
void infoManagement(UserManager& UM, bool& flag);
void changeInfo(UserManager& UM);
bool login(UserManager& UM);

int main()
{
    UserManager usermanager;
    Flags flags;

    while( flags.control )
    {
        printMenu(flags);
        management(usermanager, flags);
    }

    return 0;
}

void printMenu(const Flags flag)
{
    if(!flag.logged_in)
    {
        std::cout << "\n\n\t\t1. Register User \n";
        std::cout << "\t\t2. Login \n";
    }
    else
    {   
        std::cout << "\n\n\t\t1. Welcome !!! \n";
        std::cout << "\t\t2. Logout \n";
    }
    std::cout << "\t\t3. Show User list \n";
    std::cout << "\t\t4. Search User \n";
    if(!flag.logged_in)
    {
        std::cout << "\t\t5. Delete User \n";
    }
    else
    {
        std::cout << "\t\t5. Change Info \n";
    }
    std::cout << "\t\t6. Exit \n\n";
}

void menuInfo()
{
    std::cout << "\n\n\t\t1. Change Username \n";
    std::cout << "\t\t2. Change Password \n";
    std::cout << "\t\t3. Return to Main Menu \n";
}

int getChoice()
{
    int choice{};
    std::cout << "\t\tEnter Your Choice: ";
    while(true)
    {
        std::cin >> choice;

        if( !std::cin || choice <= 0 || choice > 6)
        {
            std::cout << '\t';
            MI::handleInput();
            continue;
        }

        MI::ignoreLine();
        return choice; 
    }
}

int getInfoChoice()
{
    int choice{};
    std::cout << "\n\n\t\tEnter Your Choice: ";
    while(true)
    {
        std::cin >> choice;

        if( !std::cin || choice <= 0 || choice > 3)
        {
            std::cout << '\t';
            MI::handleInput();
            continue;
        }

        MI::ignoreLine();
        return choice; 
    }
}

void management(UserManager& UM, Flags& flag)
{
    switch(getChoice())
    {
        case 1:
            if(!flag.logged_in)
            {
                Settings::clearScreen();
                UM.registerUser();
            }
            else
            {
                Settings::clearScreen();
                std::cout << "\t\t Welcome to the program !!!";
            }
            break;
        case 2:
            if(!flag.logged_in)
                flag.logged_in = login(UM);
            else
                flag.logged_in = UM.logoutUser();   
            break;
        case 3:
            UM.showUsers();
            break;
        case 4:
            UM.searchUser(Settings::enterUsername());
            break;
        case 5:
            if(!flag.logged_in)
            {
                UM.showUsers();
                UM.deleteUser(Settings::enterUsername());
            }
            else
            {
                changeInfo(UM);
            }
            break;
        case 6:
            flag.control = false;
            break;
        default:
            break;    
    } 
}

bool login(UserManager& UM)
{
    Settings::clearScreen();
    std::string username{ Settings::enterUsername() };
    std::string password{ Settings::enterPassword() };
    return UM.loginUser(username, password);    
}

void infoManagement(UserManager& UM, bool& scnd_flag)
{
    switch(getInfoChoice())
    {
        case 1:
            UM.changeUsername();
            break;
        case 2:
            UM.changePassword();
            break;
        case 3:
            Settings::clearScreen();
            scnd_flag = false;
            break;
        default:
            break;    
    }        
}

void changeInfo(UserManager& UM)
{
    bool scnd_flag{ true };
    while( scnd_flag )
    {
        menuInfo();
        infoManagement(UM, scnd_flag);
    }
}
