#ifndef MATERI_H
#define MATERI_H

#include <string>

// Struktur data Materi
struct Materi {
    std::string id;
    std::string judul;
    std::string deskripsi;
    std::string filePath;
    std::string kodeMK;
};

void menuKelolaMateri();

#endif