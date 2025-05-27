#ifndef MATAKULIAH_H
#define MATAKULIAH_H

#include <string>
#include <map>

// Struktur data sederhana untuk mata kuliah
struct MataKuliah {
    std::string kode;
    std::string nama;
    int sks;
};

// Variabel global
extern std::map<std::string, MataKuliah> daftarMataKuliah;
extern std::string currentMataKuliah;

// Fungsi-fungsi
bool loadMataKuliah();
MataKuliah* getCurrentMataKuliah();
void pilihMataKuliah();

#endif