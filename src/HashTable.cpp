#include "HashTable.h"
#include "Kehadiran.h"
#include "Auth.h"
#include <functional>

template <typename K, typename V>
int HashTable<K, V>::hashFunction(const K& key) const {
    return std::hash<K>{}(key) % TABLE_SIZE;
}

template <typename K, typename V>
void HashTable<K, V>::tambah(const K& key, const V& value) {
    int index = hashFunction(key);
    for (auto& pair : table[index]) {
        if (pair.first == key) {
            pair.second = value; 
            return;
        }
    }
    table[index].push_back(std::make_pair(key, value));
}

template <typename K, typename V>
bool HashTable<K, V>::hapus(const K& key) {
    int index = hashFunction(key);
    auto& list = table[index];
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->first == key) {
            list.erase(it);
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
const V* HashTable<K, V>::cari(const K& key) const { 
    int index = hashFunction(key);
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->first == key) {
            return &(it->second);
        }
    }
    return nullptr;
}

template <typename K, typename V>
V* HashTable<K, V>::cari(const K& key) {
    const V* result = static_cast<const HashTable<K, V>*>(this)->cari(key);
    return const_cast<V*>(result);
}

template <typename K, typename V>
bool HashTable<K, V>::cekKeyExist(const K& key) const {
    int index = hashFunction(key);
    for (const auto& pair : table[index]) {
        if (pair.first == key) {
            return true;
        }
    }
    return false;
}

template class HashTable<std::string, std::string>;
template class HashTable<std::string, std::pair<std::string, std::string>>;
template class HashTable<std::string, KehadiranInfo>; 
template class HashTable<std::string, bool>;
template class HashTable<std::string, User>;
