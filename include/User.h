#pragma once

#include <iostream>
#include <string>
#include <string_view>

class User
{
public:
    User(std::string username, std::string password);

    std::string_view getUsername() const;
    std::string_view getPassword() const;
    void login() { m_logged = true; }
    void logout() { m_logged = false; }
    bool isLogged(){ return m_logged; }
    void setUsername(std::string other) { m_username = other; }
    void setPassword(std::string other) { m_password = other; }

    ~User(){ m_logged = false; }

private:
    std::string m_username{};
    std::string m_password{};
    bool m_logged{ false };
};
