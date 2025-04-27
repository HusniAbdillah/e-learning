#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <map>

struct User {
    std::string nim;
    std::string nama;
    std::string role;  // "MAHASISWA" or "DOSEN"
};

class Auth {
private:
    static User currentUser;
    static std::map<std::string, User> users;

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