#include "Materi.h"
#include "LinkedList.h"
#include "ui_helpers.hpp"
#include "MataKuliah.h"
#include <iostream>

using namespace std;
using namespace UI;

void tambahMateriUI() {
    MataKuliah* mk = getCurrentMataKuliah();
    if (!mk) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    Materi m;
    cout << "ID Materi: ";
    getline(cin, m.id);
    
    if (daftarMateri.cariMateri(m.id) != nullptr) {
        display_error("ID materi sudah digunakan!");
        pause_input();
        return;
    }
    
    cout << "Judul: ";
    getline(cin, m.judul);
    cout << "Deskripsi: ";
    getline(cin, m.deskripsi);
    cout << "File Path: ";
    getline(cin, m.filePath);
    
    m.kodeMK = currentMataKuliah;
    
    daftarMateri.tambahMateri(m);
    display_success("Materi berhasil ditambahkan!");
    pause_input();
}

void hapusMateriUI() {
    if (currentMataKuliah.empty()) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    daftarMateri.tampilkanMateri(currentMataKuliah);
    
    string id;
    cout << "ID materi yang akan dihapus: ";
    getline(cin, id);
    
    Node* node = daftarMateri.cariMateri(id);
    if (!node || node->data.kodeMK != currentMataKuliah) {
        display_error("Materi tidak ditemukan dalam mata kuliah ini!");
        pause_input();
        return;
    }
    
    char konfirmasi;
    cout << "Hapus materi '" << node->data.judul << "'? (y/n): ";
    cin >> konfirmasi;
    cin.ignore();
    
    if (tolower(konfirmasi) == 'y') {
        if (daftarMateri.hapusMateri(id)) {
            display_success("Materi berhasil dihapus!");
        } else {
            display_error("Gagal menghapus materi!");
        }
    }
    
    pause_input();
}

void menuKelolaMateri() {
    MataKuliah* mk = getCurrentMataKuliah();
    if (!mk) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    int pilihan = 0;
    do {
        display_header("KELOLA MATERI: " + mk->nama);
        vector<string> menu_items = {
            "1. Tambah Materi",
            "2. Hapus Materi",
            "3. Lihat Materi",
            "4. Kembali"
        };
        
        vector<vector<string>> table_data;
        for (const auto& item : menu_items) {
            table_data.push_back({item});
        }
        draw_table(table_data, {30});
        
        cout << "\nPilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        switch(pilihan) {
            case 1: tambahMateriUI(); break;
            case 2: hapusMateriUI(); break;
            case 3: daftarMateri.tampilkanMateri(currentMataKuliah); pause_input(); break;
            case 4: break;
            default: display_error("Pilihan tidak valid!"); pause_input();
        }
    } while(pilihan != 4);
}