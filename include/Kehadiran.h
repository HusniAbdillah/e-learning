#ifndef KEHADIRAN_H
#define KEHADIRAN_H

#include <string>
#include <vector>
#include "HashTable.h"

struct KehadiranInfo {
    int pertemuan;
    std::string kodeMK;
    bool aktif;
    //HashTable untuk pencarian cepat
    HashTable<std::string, bool> mahasiswaHadirTable; // Key: NIM, Value: true
    // Vector untuk iterasi dan export ke file
    std::vector<std::string> mahasiswaHadir;
};

// Function declarations
void loadKehadiran();
void saveKehadiran();
void menuKelolaKehadiran();
void menuKehadiranMahasiswa();
void lihatKumulatifKehadiran();

// Menggunakan HashTable untuk kehadiran dengan key: kode_mk_pertemuan (contoh: "KOM20H_1")
extern HashTable<std::string, KehadiranInfo> tableKehadiran;


#endif