#include "Auth.h"
#include "ui_helpers.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

User Auth::currentUser;
HashTable<std::string, User> Auth::users;

bool Auth::loadUsers() {
    std::ifstream file("data/pengguna.csv");
    if (!file.is_open()) {
        UI::display_error("File pengguna.csv tidak ditemukan!");
        return false;
    }

    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        User user;
        
        std::getline(ss, user.nim, ';');
        std::getline(ss, user.nama, ';');
        std::getline(ss, user.role, ';');
        users.tambah(user.nim, user);
    }
    
    file.close();
    return true;
}

bool Auth::login(const std::string& nim) {
    if (users.cekKeyExist(nim)) {
        User* userPtr = users.cari(nim);
        if (userPtr) {
            currentUser = *userPtr;
            return true;
        }
    }
    return false;
}

void Auth::logout() {
    currentUser = User{};
}

bool Auth::isLoggedIn() {
    return !currentUser.nim.empty();
}

bool Auth::isDosen() {
    return isLoggedIn() && currentUser.role == "DOSEN";
}

bool Auth::isMahasiswa() {
    return isLoggedIn() && currentUser.role == "MAHASISWA";
}

User Auth::getCurrentUser() {
    return currentUser;
}

std::string Auth::getCurrentNIM() {
    return currentUser.nim;
}