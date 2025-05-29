#ifndef KEHADIRAN_H
#define KEHADIRAN_H

#include <string>
#include <vector>
#include "HashTable.h"

struct KehadiranInfo {
    int pertemuan;
    std::string kodeMK;
    bool aktif;
    
    HashTable<std::string, bool> mahasiswaHadirTable;
    
    std::vector<std::string> mahasiswaHadir;
};

void loadKehadiran();
void saveKehadiran();
void menuKelolaKehadiran();
void menuKehadiranMahasiswa();
void lihatKumulatifKehadiran();

extern HashTable<std::string, KehadiranInfo> tableKehadiran;


#endif