#include "Materi.h"
#include "ui_helpers.hpp"

void tambahMateriUI() {
    display_header("TAMBAH MATERI");
    Materi m;
    std::cout << "ID Materi: ";
    std::cin >> m.id;
    std::cin.ignore();
    std::cout << "Judul: ";
    std::getline(std::cin, m.judul);
    std::cout << "Deskripsi: ";
    std::getline(std::cin, m.deskripsi);
    std::cout << "File Path: ";
    std::getline(std::cin, m.filePath);
    
    if (daftarMateri.cekIdExist(m.id)) {
        display_error("ID materi sudah ada!");
    } else {
        daftarMateri.tambahMateri(m);
        display_success("Materi berhasil ditambahkan!");
    }
    pause_input();
}

void hapusMateriUI() {
    display_header("HAPUS MATERI");
    std::string id;
    std::cout << "Masukkan ID materi: ";
    std::cin >> id;
    
    if (daftarMateri.hapusMateri(id)) {
        display_success("Materi berhasil dihapus!");
    } else {
        display_error("Materi tidak ditemukan!");
    }
    pause_input();
}

void menuKelolaMateri() {
    int pilihan;
    do {
        display_header("KELOLA MATERI");
        vector<string> menu_items = {
            "1. Tambah Materi",
            "2. Hapus Materi",
            "3. Lihat Semua Materi",
            "4. Kembali"
        };
        draw_table({menu_items}, {30});
        
        cout << "\nPilih menu: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1: tambahMateriUI(); break;
            case 2: hapusMateriUI(); break;
            case 3: 
                display_header("DAFTAR MATERI");
                daftarMateri.tampilkanSemuaMateri();
                pause_input();
                break;
        }
    } while(pilihan != 4);
}