#include <iostream>
#include <fstream>
#include <string>
#include "ui_helpers.hpp"
#include "Materi.h"
#include "LinkedList.h"
#include "Tugas.h"
#include "Kehadiran.h"
#include "Auth.h"
#include "MataKuliah.h"
#include "Validator.h"

using namespace std;
using namespace UI;

void loadAllData() {

    Auth::loadUsers();
    
    loadMataKuliah();
    
    ifstream file("data/materi.csv");
    
    if (file.is_open()) {
        string line;
        getline(file, line);
        
        while (getline(file, line)) {
            stringstream ss(line);
            Materi m;
            
            getline(ss, m.id, ';');
            getline(ss, m.judul, ';');
            getline(ss, m.deskripsi, ';');
            getline(ss, m.filePath, ';');
            getline(ss, m.kodeMK, ';');

            daftarMateri.tambahMateri(m);
        }
        file.close();
    }
    
    loadTugas();
    
    loadKehadiran();
}

void saveAllData() {
    ofstream file("data/materi.csv");
    if (file.is_open()) {
        file << "ID;JUDUL;DESKRIPSI;FILE_PATH;KODE_MK\n";
        
        Node* current = daftarMateri.getHead();
        while (current != nullptr) {
            file << current->data.id << ";"
                << current->data.judul << ";"
                << current->data.deskripsi << ";"
                << current->data.filePath << ";"
                << current->data.kodeMK << endl;
            current = current->next;
        }
        
        file.close();
    }
    
    saveTugas();
    
    saveKehadiran();
}

void PilihanMataKuliah() {

    pilihMataKuliah();
    
    if (currentMataKuliah.empty()) return;
    
    MataKuliah* mk = getCurrentMataKuliah();
    if (!mk) return;
    
    int pilihan = 0;
    do {
        clrscr();
        display_header("E-LEARNING: " + mk->nama);
        cout << "Kode MK: " << mk->kode << " | SKS: " << mk->sks << endl;
        cout << "Mahasiswa: " << Auth::getCurrentNIM() << " - " << Auth::getCurrentUser().nama << endl;
        
        vector<string> menu_items = {
            "1. Materi",
            "2. Tugas",
            "3. Kehadiran",
            "4. Ganti Mata Kuliah",
            "5. Logout Mata Kuliah"
        };
        
        display_menu(menu_items);
        
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        switch(pilihan) {
            case 1: daftarMateri.tampilkanMateri(currentMataKuliah); pause_input(); break;
            case 2: menuTugasMahasiswa(); break;
            case 3: menuKehadiranMahasiswa(); break;
            case 4: 
                pilihMataKuliah();
                if (currentMataKuliah.empty()) {
                    pilihan = 5;
                } else {
                    mk = getCurrentMataKuliah();
                }
                break;
            case 5: break;
            default: display_error("Pilihan tidak valid!"); pause_input();
        }
    } while(pilihan != 5);
}

void menuMahasiswa(){
    int pilihan = 0;
    do {
        clrscr();
        display_header("E-LEARNING MAHASISWA");

        vector<string> menu_items = {
            "1. Pilih Mata Kuliah",
            "2. Lihat Akumulasi Tugas",
            "3. Lihat Akumulasi Kehadiran",
            "4. Logout"
        };
        
        display_menu(menu_items);
        
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        switch(pilihan) {
            case 1: PilihanMataKuliah(); pause_input(); break;
            case 2: tampilkanStatistikTugas(); break;
            case 3: lihatKumulatifKehadiran(); break;
            case 4: break;
            default: display_error("Pilihan tidak valid!"); pause_input();
        }
    } while(pilihan != 4);

}

void menuDosen() {
    pilihMataKuliah();
    
    if (currentMataKuliah.empty()) return;
    
    MataKuliah* mk = getCurrentMataKuliah();
    if (!mk) return;
    
    int pilihan = 0;
    do {
        clrscr();
        display_header("E-LEARNING DOSEN: " + mk->nama);
        cout << "Kode MK: " << mk->kode << " | SKS: " << mk->sks << endl;
        cout << "Dosen: " << Auth::getCurrentNIM() << " - " << Auth::getCurrentUser().nama << endl;
        
        vector<string> menu_items = {
            "1. Kelola Materi",
            "2. Kelola Tugas",
            "3. Kelola Kehadiran",
            "4. Ganti Mata Kuliah",
            "5. Logout"
        };
        
        display_menu(menu_items);
        
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        switch(pilihan) {
            case 1: menuKelolaMateri(); break;
            case 2: menuKelolaTugas(); break;
            case 3: menuKelolaKehadiran(); break;
            case 4: 
                pilihMataKuliah();
                if (currentMataKuliah.empty()) {
                    pilihan = 5;
                } else {
                    mk = getCurrentMataKuliah();
                }
                break;
            case 5: break;
            default: display_error("Pilihan tidak valid!"); pause_input();
        }
    } while(pilihan != 5);
}

bool login() {
    display_header("LOGIN");
    string nim;
    cout << "Masukkan NIM/NIP: ";
    cin >> nim;
    cin.ignore();
    
    if (Auth::login(nim)) {
        User user = Auth::getCurrentUser();
        display_success("Login berhasil!");
        cout << "Selamat datang, " << user.nama << endl;
        cout << "Role: " << user.role << endl;
        pause_input();
        return true;
    } else {
        display_error("NIM/NIP tidak ditemukan!");
        pause_input();
        return false;
    }
}

int main() {
    UI::enableANSIColors();
    
    loadAllData();
    
    int pilihan = 0;
    do {
        clrscr();
        display_header("SISTEM E-LEARNING");
        
        vector<string> menu_items = {
            "1. Login sebagai Dosen",
            "2. Login sebagai Mahasiswa",
            "3. Keluar"
        };
        
        display_menu(menu_items);
        
        cout << "Pilih menu: ";
        cin >> pilihan;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore();
        
        switch(pilihan) {
            case 1: 
                if (login()) {
                    if (Auth::isDosen()) {
                        menuDosen();
                        Auth::logout();
                    } else {
                        display_error("Akun ini bukan dosen!");
                        pause_input();
                    }
                }
                break;
            case 2:
                if (login()) {
                    if (Auth::isMahasiswa()) {
                        menuMahasiswa();
                        Auth::logout();
                    } else {
                        display_error("Akun ini bukan mahasiswa!");
                        pause_input();
                    }
                }
                break;
            case 3: break;
            default: display_error("Pilihan tidak valid!"); pause_input();
        }
    } while(pilihan != 3);
    
    saveAllData();
    cout << "Program selesai. Terima kasih!" << endl;
    
    return 0;
}