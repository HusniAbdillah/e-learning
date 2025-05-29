#ifndef MATAKULIAH_H
#define MATAKULIAH_H

#include <string>
#include <map>

struct MataKuliah {
    std::string kode;
    std::string nama;
    int sks;
};

extern std::map<std::string, MataKuliah> daftarMataKuliah;
extern std::string currentMataKuliah;

bool loadMataKuliah();
MataKuliah* getCurrentMataKuliah();
void pilihMataKuliah();

#endif