#include <cstddef>
#include <cctype>
#include "../include/UserManager.h"
#include "../include/Input.h"
#include "../include/Settings.h"

void UserManager::registerUser()
{
    std::string username{ Settings::enterUsername() };

    for( const auto& user : m_users)
    {
        if( user.getUsername() == username )
        {
            Settings::clearScreen();
            std::cout << "\t\tUsername already in use. Choose a different one.\n\n";
            return;
        }
    }

    std::string password{ Settings::enterPassword() };

    Settings::confirmPassword(password);

    User newUser(username, password);
    m_users.emplace_back(newUser);

    Settings::clearScreen();

    std::cout << "\n\t\tUser Register Successfully\n\n";
}

bool UserManager::loginUser(const std::string_view name, const std::string_view pass)
{
    Settings::clearScreen();

    for( auto& user : m_users )
    {
        if( user.getUsername() == name && user.getPassword() == pass )
        {
            user.login();
            std::cout << "\t\tLogin Successfully\n";
            return true;
        }  
    }

    std::cout << "\t\tInvalid Username or Password.\n";
    return false;
}

bool UserManager::logoutUser()
{
    for( auto& user : m_users )
    {
        if( user.isLogged() )
        {
            Settings::clearScreen();
            user.logout();
            std::cout << "\t\t '" << user.getUsername() << "' has logout successfully\n";
            return user.isLogged();
        }  
    }
    return false; // Pra evitar warning do compilador
}

void UserManager::showUsers() const
{
    Settings::clearScreen();

    std::cout << "\t\t-=-=-=-=-=- Users List -=-=-=-=-=-\n\n";
    for( const auto& user: m_users )
        std::cout << "\t\t\t\t" << user.getUsername() << '\n';
}

void UserManager::searchUser(const std::string_view name) const
{
    Settings::clearScreen();

    for( const auto& user : m_users)
    {
        if( user.getUsername() == name )
        {
            std::cout << "\t\tUser Found\n\n";
            return;
        }
    }
    
    std::cout << "\t\tUser Not Found\n\n";
}

void UserManager::deleteUser(const std::string_view name)
{
    auto it{ std::remove_if(m_users.begin(), m_users.end(), 
             [&name](const User& user) { return user.getUsername() == name; }) };

    Settings::clearScreen();

    if( it != m_users.end() )
    {
        m_users.erase(it, m_users.end());
        std::cout << "\t\tUser '" << name << "' deleted successfully.\n";
    }         
    else {
        std::cout << "\t\tUser '" << name << "' not found.\n";
    }
}

void UserManager::changeUsername()
{
    Settings::clearScreen();

    for( auto& user : m_users )
    {
        if( user.isLogged() )
        {
           std::string NewUsername{ Settings::enterUsername() };

            for( const auto& user : m_users)
            {
                if( user.getUsername() == NewUsername )
                {
                    Settings::clearScreen();
                    std::cout << "\t\tUsername already in use. Choose a different one.\n\n";
                    return;
                }
            }

            user.setUsername(NewUsername);           
        }  
    }
}

void UserManager::changePassword()
{
    Settings::clearScreen();

    for( auto& user : m_users )
    {
        if( user.isLogged() )
        {
            std::cout << "\t\tBefore it, please confirm your password\n";

            Settings::confirmPassword(user.getPassword());

            std::cout << "\t\tNow, enter your new password\n";

            std::string NewPassword{ Settings::enterPassword() };

            Settings::confirmPassword(NewPassword);

            user.setPassword(NewPassword);           
        }  
    }
}
