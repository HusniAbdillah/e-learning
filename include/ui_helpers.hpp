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
        const std::string BLUE = "\033[1;34m";
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

    inline void display_header(const std::string& title) {
        clrscr();
        std::cout << Color::CYAN << "==================================================" << Color::RESET << std::endl;
        std::cout << Color::CYAN << "  " << title << Color::RESET << std::endl;
        std::cout << Color::CYAN << "==================================================" << Color::RESET << std::endl << std::endl;
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
    
    // Fungsi untuk menampilkan menu sederhana tanpa tabel
    inline void display_menu(const std::vector<std::string>& menu_items) {
        std::cout << std::endl;
        for (const auto& item : menu_items) {
            std::cout << Color::RESET<< " " << item << Color::RESET << std::endl;
        }
        std::cout << std::endl;
    }

    // Fungsi untuk menampilkan tabel yang lebih adaptif
    inline void draw_table(const std::vector<std::vector<std::string>>& rows, const std::vector<int>& column_widths) {
        if (rows.empty() || column_widths.empty()) return;
        
        // Tentukan lebar kolom sebenarnya (jangan lebih panjang dari konten)
        std::vector<int> actual_widths = column_widths;
        for (size_t i = 0; i < rows.size(); ++i) {
            for (size_t j = 0; j < rows[i].size() && j < column_widths.size(); ++j) {
                // Pastikan lebar kolom cukup untuk konten terpanjang
                if (rows[i][j].length() > static_cast<size_t>(actual_widths[j])) {
                    actual_widths[j] = rows[i][j].length();
                }
            }
        }
        
        // Fungsi tambahan untuk menggambar garis pembatas
        auto draw_border = [&actual_widths]() {
            std::cout << "+";
            for (const auto& width : actual_widths) {
                std::cout << std::string(width + 2, '-') << "+";
            }
            std::cout << std::endl;
        };
        
        // Tampilkan pembatas atas
        draw_border();
        
        // Isi tabel
        for (size_t i = 0; i < rows.size(); ++i) {
            std::cout << "| ";
            for (size_t j = 0; j < rows[i].size() && j < actual_widths.size(); ++j) {
                std::cout << std::setw(actual_widths[j]) << std::left << rows[i][j] << " | ";
            }
            std::cout << std::endl;
            
            // Tambahkan pembatas setelah header
            if (i == 0) {
                draw_border();
            }
        }
        
        // Tampilkan pembatas bawah
        draw_border();
    }
}

#endif