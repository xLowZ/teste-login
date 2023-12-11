#include "../include/User.h"

User::User(std::string username, std::string password)
    : m_username{ username }, m_password{ password } {}

std::string_view User::getUsername() const
{
    return m_username;
}

std::string_view User::getPassword() const
{
    return m_password;
}
