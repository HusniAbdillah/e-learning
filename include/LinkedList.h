#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Materi.h"

struct Node {
    Materi data;
    Node* next;
    Node(const Materi& m) : data(m), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList();
    
    void tambahMateri(const Materi& materi);
    bool hapusMateri(const std::string& id);
    Node* getHead() const { return head; }
    Node* cariMateri(const std::string& id) const;
    void tampilkanMateri(const std::string& kodeMK) const;
};

extern LinkedList daftarMateri;

#endif