#include "Validator.h"
#include <ctime>
#include <sstream>
#include <iomanip>

namespace Validator {
    
    bool isValidDateFormat(const std::string& date) {
        // Cek panjang string (harus 10 karakter: YYYY-MM-DD)
        if (date.length() != 10) return false;
        
        // Cek format dengan delimiter '-'
        if (date[4] != '-' || date[7] != '-') return false;
        
        // Cek apakah karakter tahun, bulan, dan tanggal adalah digit
        for (int i = 0; i < 4; i++) { // YYYY
            if (!isdigit(date[i])) return false;
        }
        for (int i = 5; i < 7; i++) { // MM
            if (!isdigit(date[i])) return false;
        }
        for (int i = 8; i < 10; i++) { // DD
            if (!isdigit(date[i])) return false;
        }
        
        return true;
    }
    
    std::string getCurrentDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        
        std::stringstream ss;
        ss << (1900 + ltm->tm_year) << "-"
           << std::setfill('0') << std::setw(2) << (1 + ltm->tm_mon) << "-"
           << std::setfill('0') << std::setw(2) << ltm->tm_mday;
        
        return ss.str();
    }
    
    bool isValidDeadline(const std::string& deadline) {
        if (!isValidDateFormat(deadline)) return false;
        
        // Bandingkan dengan tanggal hari ini (simple string comparison)
        std::string today = getCurrentDate();
        return deadline >= today;
    }
}