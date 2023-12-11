#pragma once

#include <vector>
#include <cstddef>
#include "User.h"

class UserManager
{
public:
    UserManager() = default;

    void registerUser();
    std::size_t getUserCount() const { return m_users.size(); }
    bool loginUser(const std::string_view name, const std::string_view pass);
    void showUsers() const;
    void searchUser(const std::string_view user) const;
    void deleteUser(const std::string_view name);
    bool logoutUser();
    void changeUsername();
    void changePassword();

    ~UserManager() = default;

private:
    std::vector<User> m_users;
};
