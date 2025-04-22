#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

struct Materi {
    std::string id;
    std::string judul;
    std::string deskripsi;
    std::string filePath;
};

struct Node {
    Materi data;
    Node* next;
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList();
    ~LinkedList();
    void tambahMateri(const Materi& materi);
    bool hapusMateri(const std::string& id);
    void tampilkanSemuaMateri() const;
    bool cekIdExist(const std::string& id) const;
    Node* getHead() const { return head; }
};

#endif