#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

namespace Validator {
    // Fungsi untuk validasi format tanggal YYYY-MM-DD
    bool isValidDateFormat(const std::string& date);
    
    // Fungsi untuk validasi apakah tanggal deadline valid (tidak di masa lalu)
    bool isValidDeadline(const std::string& deadline);
    
    // Fungsi untuk mendapatkan tanggal hari ini dalam format YYYY-MM-DD
    std::string getCurrentDate();
}

#endif