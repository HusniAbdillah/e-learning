#ifndef MATERI_H
#define MATERI_H

#include <string>

struct Materi {
    std::string id;
    std::string judul;
    std::string deskripsi;
    std::string filePath;
    std::string kodeMK;
};

void menuKelolaMateri();

#endif