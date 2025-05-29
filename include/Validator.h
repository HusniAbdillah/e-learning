#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

namespace Validator {
    
    bool isValidDateFormat(const std::string& date);
    
    bool isValidDeadline(const std::string& deadline);
    
    std::string getCurrentDate();
}

#endif