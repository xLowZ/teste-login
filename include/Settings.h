#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "Input.h"

namespace Settings
{
    inline void confirmPassword(std::string_view password)
    {
        while (true)
        {
            std::string confirmPassword;
            std::cout << "\t\tConfirm your password: ";
            std::cin >> confirmPassword;

            if (!std::cin || confirmPassword.empty())
            {
                std::cout << '\t';
                MI::handleInput();
                continue;
            }

            if (password == confirmPassword)
                return;
            else
            {
                std::cout << "\tPasswords do not match. Please try again." << std::endl;
                std::cin.clear();
                MI::ignoreLine();
                continue;
            }
        }
    }

    inline std::string enterUsername()
    {
        std::string username{};
        std::cout << "\n\t\tEnter the username: ";
        while(true)
        {
            std::cin >> username;

            auto it{ std::find_if(username.begin(), username.end(), 
                    [](char c)
                    {
                        return !(std::isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_' || c == '.');
                    }) };

            if( !std::cin || it != username.end())
            {
                std::cout << '\t';
                MI::handleInput();
                continue;
            }

            MI::ignoreLine();
            return username;
        }
    }

    inline std::string enterPassword()
    {
        std::string password{};
        std::cout << "\t\tEnter your password: ";
        while(true)
        {
            std::cin >> password;

            if( !std::cin )
            {
                std::cout << '\t';
                MI::handleInput();
                continue;
            }

            MI::ignoreLine();
            return password;
        }
    }

    inline void clearScreen()
    {
        #ifdef _WIN32
        {
            system("cls");
        }
        #else
            std::cout << "\033[2J\033[1;1H";  // Código ANSI para limpar a tela
        #endif    
    }
}
