#pragma once

#include "UserManager.h"
#include "Settings.h"

namespace fnc
{
    struct Flags
    {
        bool control{ true };
        bool logged_in{ false };
        bool info_menu{ false };
    };

    inline void printMenu(const Flags flag);
    inline void menuInfo();
    inline int  getChoice(const Flags& flag);
    inline void management(UserManager& UM, Flags& flag);
    inline void infoManagement(UserManager& UM,Flags& flag);
    inline void changeInfo(UserManager& UM, Flags& flag);
    inline bool login(UserManager& UM);

    inline void printMenu(const Flags flag)
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

    inline void menuInfo()
    {
        std::cout << "\n\n\t\t1. Change Username \n";
        std::cout << "\t\t2. Change Password \n";
        std::cout << "\t\t3. Return to Main Menu \n";
    }

    inline int getChoice(const Flags& flag)
    {
        int max_choice{};

        if( flag.logged_in && flag.info_menu )
            max_choice = 3;
        else
            max_choice = 6; 

        int choice{};
        std::cout << "\n\n\t\tEnter Your Choice: ";
        while(true)
        {
            std::cin >> choice;

            if( !std::cin || choice <= 0 || choice > max_choice)
            {
                std::cout << '\t';
                MI::handleInput();
                continue;
            }

            MI::ignoreLine();
            return choice; 
        }
    }

    inline void management(UserManager& UM, Flags& flag)
    {
        switch(getChoice(flag))
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
                std::cout << "\n\n\t\t\t (Currently " << UM.getUserCount() << " users)\n\n";   
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
                    changeInfo(UM, flag);
                }
                break;
            case 6:
                flag.control = false;
                break;
            default:
                break;    
        } 
    }

    inline bool login(UserManager& UM)
    {
        Settings::clearScreen();
        std::string username{ Settings::enterUsername() };
        std::string password{ Settings::enterPassword() };
        return UM.loginUser(username, password);    
    }

    inline void infoManagement(UserManager& UM,Flags& flag)
    {
        switch(getChoice(flag))
        {
            case 1:
                UM.changeUsername();
                break;
            case 2:
                UM.changePassword();
                break;
            case 3:
                Settings::clearScreen();
                flag.info_menu = false;
                break;
            default:
                break;    
        }        
    }

    inline void changeInfo(UserManager& UM, Flags& flag)
    {
        flag.info_menu = true;
        while( flag.info_menu )
        {
            menuInfo();
            infoManagement(UM, flag);
        }
    }
}
