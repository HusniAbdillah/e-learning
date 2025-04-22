#include <iostream>
#include <fstream>
#include <sstream>
#include "ui_helpers.hpp"
#include "LinkedList.h"
#include "HashTable.h"
#include "Materi.h"
#include "Tugas.h"
#include "Kehadiran.h"

using namespace std;
using namespace UI;

// Variabel global
LinkedList daftarMateri;
HashTable<string, pair<string, string>> daftarTugas;
HashTable<string, string> daftarKehadiran;
queue<string> antrianPenilaian;
stack<pair<string, int>> undoStack;

// Prototipe fungsi
void loadAllData();
void saveAllData();

// Menu Dosen
void menuDosen() {
    int pilihan;
    do {
        display_header("MENU DOSEN");
        vector<string> menu_items = {
            "1. Kelola Materi",
            "2. Buat Tugas",
            "3. Nilai Tugas",
            "4. Undo Penilaian",
            "5. Logout"
        };
        draw_table({menu_items}, {30});
        
        cout << "\nPilih menu: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1: menuKelolaMateri(); break;
            case 2: menuBuatTugas(); break;
            case 3: menuNilaiTugas(); break;
            case 4: 
                if(undoStack.empty()) {
                    display_error("Tidak ada penilaian yang bisa di-undo!");
                } else {
                    auto last = undoStack.top();
                    undoStack.pop();
                    display_success("Penilaian untuk tugas " + last.first + " dibatalkan!");
                }
                pause_input();
                break;
        }
    } while(pilihan != 5);
}

// Menu Mahasiswa
void menuMahasiswa() {
    int pilihan;
    do {
        display_header("MENU MAHASISWA");
        vector<string> menu_items = {
            "1. Lihat Materi",
            "2. Kirim Tugas",
            "3. Lihat Nilai",
            "4. Kehadiran",
            "5. Logout"
        };
        draw_table({menu_items}, {30});
        
        cout << "\nPilih menu: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1: 
                display_header("DAFTAR MATERI");
                daftarMateri.tampilkanSemuaMateri();
                pause_input();
                break;
            case 2: kirimTugasUI(); break;
            case 4: menuKehadiran(); break;
        }
    } while(pilihan != 5);
}

int main() {
    loadAllData();
    
    int pilihan;
    do {
        display_header("SISTEM E-LEARNING");
        vector<string> menu_items = {
            "1. Login sebagai Dosen",
            "2. Login sebagai Mahasiswa",
            "3. Keluar"
        };
        draw_table({menu_items}, {30});
        
        cout << "\nPilih menu: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1: menuDosen(); break;
            case 2: menuMahasiswa(); break;
        }
        pause_input();
    } while(pilihan != 3);
    
    saveAllData();
    return 0;
}