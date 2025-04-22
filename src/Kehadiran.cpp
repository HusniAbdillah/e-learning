#include "Kehadiran.h"
#include "ui_helpers.hpp"

bool verifikasiKehadiran(const std::string& token) {
    return daftarKehadiran.cekKeyExist(token);
}

void menuKehadiran() {
    display_header("KEHADIRAN");
    std::string token;
    std::cout << "Masukkan token kehadiran: ";
    std::cin >> token;
    
    if(verifikasiKehadiran(token)) {
        display_success("Kehadiran berhasil diverifikasi!");
    } else {
        display_error("Token kehadiran tidak valid!");
    }
    pause_input();
}