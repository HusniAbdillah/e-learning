#ifndef AUTH_H
#define AUTH_H

#include <string>
#include "HashTable.h" 

struct User {
    std::string nim;
    std::string nama;
    std::string role;  
};

class Auth {
private:
    static User currentUser;
    static HashTable<std::string, User> users; 

public:
    static bool loadUsers();
    static bool login(const std::string& nim);
    static void logout();
    static bool isLoggedIn();
    static bool isDosen();
    static bool isMahasiswa();
    static User getCurrentUser();
    static std::string getCurrentNIM();
};

#endif