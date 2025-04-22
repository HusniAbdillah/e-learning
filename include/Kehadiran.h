#ifndef KEHADIRAN_H
#define KEHADIRAN_H

#include "HashTable.h"
#include <string>

extern HashTable<std::string, std::string> daftarKehadiran;

bool verifikasiKehadiran(const std::string& token);

#endif