#include "Validator.h"
#include <ctime>
#include <sstream>
#include <iomanip>

namespace Validator {
    
    bool isValidDateFormat(const std::string& date) {
        if (date.length() != 10) return false;
        
        if (date[4] != '-' || date[7] != '-') return false;
        
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
    
    bool isValidDateValue(const std::string& date) {
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));
        if (month < 1 || month > 12) return false;
        if (day < 1) return false;
        int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (leap && month == 2) {
            if (day > 29) return false;
        } else {
            if (day > daysInMonth[month - 1]) return false;
        }
        return true;
    }
    
    bool isValidDeadline(const std::string& deadline) {
        if (!isValidDateFormat(deadline)) return false;
        if (!isValidDateValue(deadline)) return false;
        std::string today = getCurrentDate();
        return deadline >= today;
    }
}