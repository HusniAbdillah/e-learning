#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <utility> 

template <typename K, typename V>
class HashTable {
public: 
    static const int TABLE_SIZE = 10;
    
private:
    std::list<std::pair<K, V>> table[TABLE_SIZE];
    int hashFunction(const K& key) const;
    
public:
    void tambah(const K& key, const V& value);
    bool hapus(const K& key);
    const V* cari(const K& key) const; 
    V* cari(const K& key);
    bool cekKeyExist(const K& key) const;
    
    const std::list<std::pair<K, V>>& getDataAtIndex(int index) const {
        if (index >= 0 && index < TABLE_SIZE) {
            return table[index];
        }
        static std::list<std::pair<K, V>> empty;
        return empty;
    }
};

#endif