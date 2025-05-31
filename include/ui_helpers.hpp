#ifndef UI_HELPERS_HPP
#define UI_HELPERS_HPP

#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

namespace UI {
    
    inline void enableANSIColors() {
        #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        #endif
    }

    namespace Color {
        const std::string RED = "\033[1;31m";
        const std::string GREEN = "\033[1;32m";
        const std::string YELLOW = "\033[1;33m";
        const std::string CYAN = "\033[1;36m";
        const std::string BLUE = "\033[1;34m";
        const std::string MAGENTA = "\033[1;35m";
        const std::string RESET = "\033[0m";
    }
    
    inline void clrscr() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    inline void pause_input() {
        std::cout << "\n" << Color::CYAN << "Tekan enter untuk melanjutkan..." << Color::RESET;
        std::cin.get();
    }
    inline void display_logo() {
        std::cout << Color::CYAN <<
        R"(                  __                                        _                      )" << std::endl;
        std::cout << Color::CYAN <<
        R"(                 [  |                                      (_)                     )" << std::endl;
        std::cout << Color::BLUE <<
        R"( .---.   ______   | |   .---.   ,--.    _ .--.   _ .--.    __    _ .--.     .--./) )" << std::endl;
        std::cout << Color::BLUE <<
        R"(/ /__\  |______|  | |  / /__\ ` '_\ :  [ `/'`\] [ `.-. |  [  |  [ `.-. |   / /'`\; )" << std::endl;
        std::cout << Color::MAGENTA <<
        R"(| \__.,           | |  | \__., // | |,  | |      | | | |   | |   | | | |   \ \._// )" << std::endl;
        std::cout << Color::YELLOW <<
        R"( '.__.'          [___]  '.__.' \'-;__/ [___]    [___||__] [___] [___||__]  .',__`  )" << std::endl;
        std::cout << Color::GREEN <<
        R"(                                                                          ( ( __)) )" << std::endl;
        std::cout << Color::RESET << std::endl;
    }
    inline void display_header(const std::string& title) {
        clrscr();
        display_logo();
        std::cout << Color::CYAN << "==================================================================================" << Color::RESET << std::endl;
        std::cout << Color::CYAN << "  " << title << Color::RESET << std::endl;
        std::cout << Color::CYAN << "==================================================================================" << Color::RESET << std::endl << std::endl;
    }

    inline void display_error(const std::string& message) {
        std::cout << Color::RED << "[ERROR] " << message << Color::RESET << std::endl;
    }

    inline void display_success(const std::string& message) {
        std::cout << Color::GREEN << "[SUCCESS] " << message << Color::RESET << std::endl;
    }
    
    inline void display_info(const std::string& message) {
        std::cout << Color::YELLOW << "[INFO] " << message << Color::RESET << std::endl;
    }
    
    inline void display_menu(const std::vector<std::string>& menu_items) {
        std::cout << std::endl;
        for (const auto& item : menu_items) {
            std::cout << Color::RESET<< " " << item << Color::RESET << std::endl;
        }
        std::cout << std::endl;
    }

    inline void draw_table(const std::vector<std::vector<std::string>>& rows, const std::vector<int>& column_widths) {
        if (rows.empty() || column_widths.empty()) return;

        const char horizontal = '-';
        const char vertical = '|';
        const char junction = '+';
        const char header_horizontal = '=';  

        auto draw_border = [&column_widths, horizontal, junction]() {
            std::cout << junction;
            for (const auto& width : column_widths) {
                std::cout << std::string(width + 2, horizontal) << junction;
            }
            std::cout << std::endl;
        };

        auto draw_header_border = [&column_widths, header_horizontal, junction]() {
            std::cout << junction;
            for (const auto& width : column_widths) {
                std::cout << std::string(width + 2, header_horizontal) << junction;
            }
            std::cout << std::endl;
        };

        auto wrap_text = [](const std::string& text, int width) -> std::vector<std::string> {
            if (width <= 0) return {text};
            
            std::vector<std::string> lines;
            std::string remaining = text;
            
            while (!remaining.empty()) {
                if (remaining.length() <= static_cast<size_t>(width)) {
                    lines.push_back(remaining);
                    break;
                }
                
                size_t break_pos = width;
                size_t last_space = remaining.find_last_of(" \t", width - 1);
                
                if (last_space != std::string::npos && last_space > 0) {
                    break_pos = last_space;
                }
                
                std::string line = remaining.substr(0, break_pos);
                lines.push_back(line);
                
                remaining = remaining.substr(break_pos);
                
                while (!remaining.empty() && (remaining[0] == ' ' || remaining[0] == '\t')) {
                    remaining = remaining.substr(1);
                }
            }
            
            return lines.empty() ? std::vector<std::string>{""} : lines;
        };

        draw_header_border();

        for (size_t i = 0; i < rows.size(); ++i) {
            size_t max_lines = 1;
            std::vector<std::vector<std::string>> wrapped_row;
            
            for (size_t j = 0; j < rows[i].size() && j < column_widths.size(); ++j) {
                auto wrapped = wrap_text(rows[i][j], column_widths[j]);
                wrapped_row.push_back(wrapped);
                max_lines = std::max(max_lines, wrapped.size());
            }

            for (size_t line = 0; line < max_lines; ++line) {
                std::cout << vertical;
                for (size_t j = 0; j < wrapped_row.size() && j < column_widths.size(); ++j) {
                    std::string text = (line < wrapped_row[j].size()) ? wrapped_row[j][line] : "";
                    
                    if (i == 0) {
                        std::cout << " " << Color::CYAN << std::setw(column_widths[j]) << std::left << text << Color::RESET << " " << vertical;
                    } else {
                        std::cout << " " << std::setw(column_widths[j]) << std::left << text << " " << vertical;
                    }
                }                std::cout << std::endl;
            }
            
            if (i == 0) {
                draw_header_border();
            } else {
                draw_border();
            }
        }
    }
}

#endif