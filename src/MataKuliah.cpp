#include "MataKuliah.h"
#include "ui_helpers.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace UI;

std::map<std::string, MataKuliah> daftarMataKuliah;
std::string currentMataKuliah = "";

bool loadMataKuliah() {
    std::ifstream file("data/matakuliah.csv");
    
    if (!file.is_open()) return false;
    
    std::string line;
    std::getline(file, line);
    
    daftarMataKuliah.clear();
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        MataKuliah mk;
        
        std::getline(ss, mk.kode, ';');
        std::getline(ss, mk.nama, ';');
        std::string sks;
        std::getline(ss, sks, ';');

        mk.sks = std::stoi(sks);
        daftarMataKuliah[mk.kode] = mk;
    }
    
    file.close();
    return true;
}

MataKuliah* getCurrentMataKuliah() {
    if (currentMataKuliah.empty() || 
        daftarMataKuliah.find(currentMataKuliah) == daftarMataKuliah.end()) {
        return nullptr;
    }
    return &daftarMataKuliah[currentMataKuliah];
}

void pilihMataKuliah() {
    display_header("PILIH MATA KULIAH");
    
    std::vector<std::vector<std::string>> table_data;
    table_data.push_back({"NO", "KODE", "NAMA", "SKS"});
    
    std::vector<std::string> kodes;
    int i = 1;
    
    for (const auto& pair : daftarMataKuliah) {
        const MataKuliah& mk = pair.second;
        table_data.push_back({
            std::to_string(i++),
            mk.kode,
            mk.nama,
            std::to_string(mk.sks)
        });
        kodes.push_back(mk.kode);
    }
    
    draw_table(table_data, {5, 10, 30, 5});
    
    int pilihan;
    std::cout << "\nPilih nomor mata kuliah (0 untuk kembali): ";
    std::cin >> pilihan;
    
    if (std::cin.fail() || pilihan < 0 || pilihan > kodes.size()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        display_error("Pilihan tidak valid!");
        pause_input();
        return;
    }
    
    std::cin.ignore();
    
    if (pilihan == 0) return;
    
    currentMataKuliah = kodes[pilihan - 1];
    display_success("Anda memilih mata kuliah: " + daftarMataKuliah[currentMataKuliah].nama);
    pause_input();
}