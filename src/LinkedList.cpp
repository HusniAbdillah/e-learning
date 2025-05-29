#include "LinkedList.h"
#include "MataKuliah.h"
#include "ui_helpers.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace UI;

LinkedList daftarMateri;

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::tambahMateri(const Materi& materi) {
    Node* newNode = new Node(materi);
    
    if (head == nullptr) {
        head = newNode;
        return;
    }
    
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}

bool LinkedList::hapusMateri(const std::string& id) {
    if (head == nullptr) return false;
    
    if (head->data.id == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    
    Node* current = head;
    while (current->next != nullptr && current->next->data.id != id) {
        current = current->next;
    }
    
    if (current->next == nullptr) return false;
    
    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
    return true;
}

Node* LinkedList::cariMateri(const std::string& id) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void LinkedList::tampilkanMateri(const std::string& kodeMK) const {
    display_header("DAFTAR MATERI");
    
    vector<vector<string>> table_data;
    table_data.push_back({"ID", "JUDUL", "DESKRIPSI", "FILE"});
    
    Node* current = head;
    bool ada_materi = false;
    
    while (current != nullptr) {
        if (current->data.kodeMK == kodeMK) {
            ada_materi = true;
            table_data.push_back({
                current->data.id,
                current->data.judul,
                current->data.deskripsi,
                current->data.filePath
            });
        }
        current = current->next;
    }
    
    if (!ada_materi) {
        display_info("Belum ada materi untuk mata kuliah ini.");
    } else {
        draw_table(table_data, {10, 20, 30, 20});
    }
}