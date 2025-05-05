#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <utility> // std::pair

template <typename K, typename V>
class HashTable {
public:  // Pindahkan ini ke public agar bisa diakses dari luar
    static const int TABLE_SIZE = 10;
    
private:
    std::list<std::pair<K, V>> table[TABLE_SIZE];
    int hashFunction(const K& key) const;
    
public:
    void tambah(const K& key, const V& value);
    bool hapus(const K& key);
    V* cari(const K& key);
    bool cekKeyExist(const K& key) const;
    
    // Tambahkan metode untuk mengakses data di indeks tertentu
    const std::list<std::pair<K, V>>& getDataAtIndex(int index) const {
        if (index >= 0 && index < TABLE_SIZE) {
            return table[index];
        }
        static std::list<std::pair<K, V>> empty;
        return empty;
    }
};

#endif