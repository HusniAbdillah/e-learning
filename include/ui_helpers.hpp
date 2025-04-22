#ifndef UI_HELPERS_HPP
#define UI_HELPERS_HPP

#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>

namespace UI {
    namespace Color {
        const std::string RED = "\033[1;31m";      
        const std::string GREEN = "\033[1;32m";    
        const std::string YELLOW = "\033[1;33m";   
        const std::string CYAN = "\033[1;36m";     
        const std::string RESET = "\033[0m";
    }

    void clrscr() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void pause_input() {
        std::cout << "\n" << Color::CYAN << "Tekan enter untuk melanjutkan..." << Color::RESET;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    void display_header(const std::string& title) {
        clrscr();
        std::cout << Color::CYAN << "==================================================" << Color::RESET << std::endl;
        std::cout << Color::CYAN << "  " << title << Color::RESET << std::endl;
        std::cout << Color::CYAN << "==================================================" << Color::RESET << std::endl << std::endl;
    }

    void display_error(const std::string& message) {
        std::cout << Color::RED << "[ERROR] " << message << Color::RESET << std::endl;
    }

    void display_success(const std::string& message) {
        std::cout << Color::GREEN << "[SUCCESS] " << message << Color::RESET << std::endl;
    }

    void draw_table(const std::vector<std::vector<std::string>>& rows, const std::vector<int>& column_widths) {
        for (size_t i = 0; i < rows.size(); ++i) {
            std::cout << "| ";
            for (size_t j = 0; j < rows[i].size(); ++j) {
                std::cout << std::setw(column_widths[j]) << rows[i][j] << " | ";
            }
            std::cout << std::endl;
            if (i == 0) {
                std::cout << "|";
                for (const auto& width : column_widths) {
                    std::cout << std::setw(width + 2) << std::setfill('-') << "" << "|";
                }
                std::cout << std::setfill(' ') << std::endl;
            }
        }
    }
}

#endif