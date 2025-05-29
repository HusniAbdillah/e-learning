#include "Kehadiran.h"
#include "ui_helpers.hpp"
#include "MataKuliah.h"
#include "Auth.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace UI;

// Inisialisasi HashTable untuk kehadiran
HashTable<string, KehadiranInfo> tableKehadiran;

// Fungsi baru dengan HashTable:
bool mahasiswaHadir(const KehadiranInfo* info, const string& nim) {
    return info->mahasiswaHadirTable.cari(nim) != nullptr;
}

// Fungsi untuk load data kehadiran dari file
void loadKehadiran() {
    ifstream file("data/kehadiran.csv");
    if (!file.is_open()) {
        ofstream createFile("data/kehadiran.csv");
        if (createFile.is_open()) {
            createFile << "PERTEMUAN;KODE_MK;AKTIF;NIM_HADIR\n"; 
            createFile.close();
            file.open("data/kehadiran.csv");
        }
    }
    
    if (!file.is_open()) return;
    
    string line;
    getline(file, line); 
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string pertemuanStr, kodeMK, aktifStr, nimList;
        
        getline(ss, pertemuanStr, ';'); 
        getline(ss, kodeMK, ';');
        getline(ss, aktifStr, ';');
        getline(ss, nimList);
        
        try {
            int pertemuan = stoi(pertemuanStr);
            bool aktif = (aktifStr == "1");
            
            // Buat key untuk HashTable
            string key = kodeMK + "_" + pertemuanStr;
            
            // Buat objek KehadiranInfo
            KehadiranInfo info;
            info.pertemuan = pertemuan;
            info.kodeMK = kodeMK;
            info.aktif = aktif;
            
            // Parse NIM hadir
            stringstream nimStream(nimList);
            string nim;
            while (getline(nimStream, nim, ',')) { 
                if (!nim.empty()) {
                    info.mahasiswaHadir.push_back(nim);
                    info.mahasiswaHadirTable.tambah(nim, true); // Tambah ke HashTable
                }
            }
            
            // Tambahkan ke HashTable
            tableKehadiran.tambah(key, info);
        } catch (...) {
            // Skip data invalid
        }
    }
    
    file.close();
}

// Fungsi untuk save data kehadiran ke file
void saveKehadiran() {
    ofstream file("data/kehadiran.csv");
    if (!file.is_open()) return;
    
    file << "PERTEMUAN;KODE_MK;AKTIF;NIM_HADIR\n"; 
    
    // Ambil data dari HashTable
    for (int i = 0; i < HashTable<string, KehadiranInfo>::TABLE_SIZE; i++) {
        const auto& bucket = tableKehadiran.getDataAtIndex(i);
        for (const auto& pair : bucket) {
            const auto& key = pair.first;
            const auto& info = pair.second;
            
            file << info.pertemuan << ";" 
                 << info.kodeMK << ";" 
                 << (info.aktif ? "1" : "0") << ";";
            
            // Tulis daftar NIM hadir
            for (size_t j = 0; j < info.mahasiswaHadir.size(); j++) {
                file << info.mahasiswaHadir[j];
                if (j < info.mahasiswaHadir.size() - 1) {
                    file << ",";
                }
            }
            
            file << "\n";
        }
    }
    
    file.close();
}

// Fungsi untuk buat sesi absensi baru (dosen)
void buatSesiAbsensi() {
    if (currentMataKuliah.empty()) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    int pertemuan;
    cout << "Pertemuan (1-14): ";
    cin >> pertemuan;
    cin.ignore();
    
    if (pertemuan < 1 || pertemuan > 14) {
        display_error("Nomor pertemuan tidak valid!");
        pause_input();
        return;
    }
    
    // Generate key untuk HashTable
    string key = currentMataKuliah + "_" + to_string(pertemuan);
    
    // Cek apakah sudah ada
    KehadiranInfo* infoPtr = tableKehadiran.cari(key);
    if (infoPtr) {
        infoPtr->aktif = true; 
        display_success("Sesi absensi untuk pertemuan " + to_string(pertemuan) + " berhasil diaktifkan!");
    } else {
        KehadiranInfo info;
        info.pertemuan = pertemuan;
        info.kodeMK = currentMataKuliah;
        info.aktif = true;
        tableKehadiran.tambah(key, info);
        display_success("Sesi absensi untuk pertemuan " + to_string(pertemuan) + " berhasil dibuat!");
    }
    
    saveKehadiran();
    pause_input();
}

// Fungsi untuk lihat rekap kehadiran (dosen)
void lihatRekapKehadiran() {
    if (currentMataKuliah.empty()) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    vector<vector<string>> table_data;
    table_data.push_back({"PERTEMUAN", "STATUS", "JUMLAH HADIR"});
    
    for (int i = 1; i <= 14; i++) {
        string key = currentMataKuliah + "_" + to_string(i);
        KehadiranInfo* infoPtr = tableKehadiran.cari(key);
        
        string status = "Belum Dibuat";
        int jumlah = 0;
        
        if (infoPtr) {
            status = infoPtr->aktif ? "Aktif" : "Nonaktif";
            jumlah = infoPtr->mahasiswaHadir.size();
        }
        
        table_data.push_back({
            "Pertemuan " + to_string(i),
            status,
            to_string(jumlah)
        });
    }
    
    draw_table(table_data, {15, 15, 15});
    pause_input();
}

vector<MataKuliah> getMataKuliahMahasiswa(const string& nim) {
    vector<MataKuliah> daftarMK;

    for (const auto& pair : daftarMataKuliah) {
        const MataKuliah& mk = pair.second;
        bool found = false;
        
        // Cek di 14 pertemuan
        for (int i = 1; i <= 14; i++) {
            string key = mk.kode + "_" + to_string(i);
            KehadiranInfo* info = tableKehadiran.cari(key);
            if (info && mahasiswaHadir(info, nim)) {
                found = true;
                break; // cukup ketemu sekali aja
            }
        }

        if (found) {
            daftarMK.push_back(mk);
        }
    }

    return daftarMK;
}

// Fungsi untuk menghitung kumulatif kehadiran seluruh mata kuliah untuk mahasiswa
void lihatKumulatifKehadiran() {
    string nim = Auth::getCurrentNIM();
    // Ambil semua mata kuliah yang diambil mahasiswa
    vector<MataKuliah> daftarMK = getMataKuliahMahasiswa(nim);
    
    if (daftarMK.empty()) {
        display_info("Anda belum mengambil mata kuliah apapun.");
        pause_input();
        return;
    }

    display_header("REKAP KEHADIRAN SELURUH MATA KULIAH");
    
    // Siapkan data tabel
    vector<vector<string>> table_data;
    table_data.push_back({"KODE MK", "NAMA MK", "KEHADIRAN", "PERSENTASE"});
    
    int totalKehadiran = 0;
    int totalPertemuan = 0;
    
    // Iterasi setiap mata kuliah
    for (const MataKuliah& mk : daftarMK) {
        int jumlahHadir = 0;
        int jumlahPertemuan = 0;
        
        // Cek kehadiran di setiap pertemuan
        for (int i = 1; i <= 14; i++) {
            string key = mk.kode + "_" + to_string(i);
            KehadiranInfo* info = tableKehadiran.cari(key);
            
            if (info) {
                jumlahPertemuan++;
                
                // Cek apakah mahasiswa hadir
                if (mahasiswaHadir(info, nim)) {
                    jumlahHadir++;
                }
            }
        }
        
        // Hitung persentase
        double persentase = 0;
        if (jumlahPertemuan > 0) {
            persentase = (double)jumlahHadir / 14 * 100; // Selalu dari 14 pertemuan total
        }
        
        // Tambahkan ke total
        totalKehadiran += jumlahHadir;
        totalPertemuan += 14; 
        
        // Tambahkan ke tabel
        table_data.push_back({
            mk.kode,
            mk.nama,
            to_string(jumlahHadir) + "/" + to_string(14),
            to_string((int)persentase) + "%"
        });
    }
    
    // Hitung persentase total
    double persentaseTotal = 0;
    if (totalPertemuan > 0) {
        persentaseTotal = (double)totalKehadiran / totalPertemuan * 100;
    }
    
    // Tambahkan baris total
    table_data.push_back({
        "",
        "TOTAL",
        to_string(totalKehadiran) + "/" + to_string(totalPertemuan),
        to_string((int)persentaseTotal) + "%"
    });
    
    draw_table(table_data, {10, 25, 12, 12});
    pause_input();
}

// Fungsi untuk mahasiswa mengisi absensi
void isiAbsensi() {
    if (currentMataKuliah.empty()) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    int pertemuan;
    cout << "Masukkan pertemuan (1-14): ";
    cin >> pertemuan;
    cin.ignore();
    
    if (pertemuan < 1 || pertemuan > 14) {
        display_error("Nomor pertemuan tidak valid!");
        pause_input();
        return;
    }
    
    // Generate key
    string key = currentMataKuliah + "_" + to_string(pertemuan);
    
    // Cari sesi absensi
    KehadiranInfo* infoPtr = tableKehadiran.cari(key);
    if (!infoPtr) {
        display_error("Belum ada sesi absensi untuk pertemuan ini!");
        pause_input();
        return;
    }
    
    if (!infoPtr->aktif) {
        display_error("Sesi absensi untuk pertemuan ini tidak aktif!");
        pause_input();
        return;
    }
    
    string nim = Auth::getCurrentNIM();
    
    // Cek apakah sudah absen
    if (mahasiswaHadir(infoPtr, nim)) {
        display_info("Anda sudah tercatat hadir pada pertemuan ini!");
        pause_input();
        return;
    }
    
    // Tambahkan ke daftar hadir
    infoPtr->mahasiswaHadir.push_back(nim);
    infoPtr->mahasiswaHadirTable.tambah(nim, true); 
    saveKehadiran();
    
    display_success("Kehadiran berhasil dicatat!");
    pause_input();
}

// Fungsi untuk mahasiswa melihat status kehadiran
void lihatStatusKehadiran() {
    if (currentMataKuliah.empty()) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    string nim = Auth::getCurrentNIM();
    
    vector<vector<string>> table_data;
    table_data.push_back({"PERTEMUAN", "STATUS"});
    
    for (int i = 1; i <= 14; i++) {
        string key = currentMataKuliah + "_" + to_string(i);
        KehadiranInfo* infoPtr = tableKehadiran.cari(key);
        
        string status = "Belum Dibuat";
        
        if (infoPtr) {
            status = "Tidak Hadir";
            if (mahasiswaHadir(infoPtr, nim)) {
                status = "Hadir";
            }
        }
        
        table_data.push_back({
            "Pertemuan " + to_string(i),
            status
        });
    }
    
    draw_table(table_data, {15, 15});
    pause_input();
}

// Menu untuk dosen
void menuKelolaKehadiran() {
    MataKuliah* mk = getCurrentMataKuliah();
    if (!mk) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    int pilihan = 0;
    do {
        display_header("KELOLA KEHADIRAN: " + mk->nama);
        vector<string> menu_items = {
            "1. Buat/Aktifkan Sesi Absensi",
            "2. Lihat Rekap Kehadiran",
            "3. Kembali"
        };
        
        display_menu(menu_items);
        
        cout << "\nPilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        switch(pilihan) {
            case 1: buatSesiAbsensi(); break;
            case 2: lihatRekapKehadiran(); break;
            case 3: break;
            default: display_error("Pilihan tidak valid!"); pause_input();
        }
    } while(pilihan != 3);
}

// Menu untuk mahasiswa
void menuKehadiranMahasiswa() {
    MataKuliah* mk = getCurrentMataKuliah();
    if (!mk) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    int pilihan = 0;
    do {
        display_header("KEHADIRAN MAHASISWA: " + mk->nama);
        vector<string> menu_items = {
            "1. Isi Absensi",
            "2. Lihat Status Kehadiran",
            "3. Rekap Kehadiran Seluruh Mata Kuliah",
            "4. Kembali"
        };
        
        display_menu(menu_items);
        
        cout << "\nPilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        switch(pilihan) {
            case 1: isiAbsensi(); break;
            case 2: lihatStatusKehadiran(); break;
            case 3: lihatKumulatifKehadiran(); break;
            case 4: break;
            default: display_error("Pilihan tidak valid!"); pause_input();
        }
    } while(pilihan != 4);
}