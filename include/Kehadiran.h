#ifndef KEHADIRAN_H
#define KEHADIRAN_H

#include <string>
#include <vector>
#include "HashTable.h"

// Info kehadiran yang sederhana
struct KehadiranInfo {
    int pertemuan;
    std::string kodeMK;
    bool aktif;
    std::vector<std::string> mahasiswaHadir;
};

// Function declarations
void loadKehadiran();
void saveKehadiran();
void menuKelolaKehadiran();
void menuKehadiranMahasiswa();

// Menggunakan HashTable untuk kehadiran dengan key: kode_mk_pertemuan (contoh: "KOM20H_1")
extern HashTable<std::string, KehadiranInfo> tableKehadiran;

// Fungsi sederhana untuk menghasilkan token absensi
std::string generateAbsenToken(const std::string& kodeMK, int pertemuan, const std::string& nim);

#endif