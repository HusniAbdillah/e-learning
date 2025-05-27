#include "Tugas.h"
#include "ui_helpers.hpp"
#include "MataKuliah.h"
#include "Auth.h"
#include "PriorityQueue.h"
#include "MergeSort.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <map>
#include <tuple>

using namespace std;
using namespace UI;

vector<Tugas> daftarTugas;
Queue<PenilaianTugas> antriPenilaian;
Stack<UndoPenilaian> undoStack;

// Struktur untuk sorting berdasarkan nilai
struct TugasItemNilai {
    string id, deskripsi, deadline, kodeMK, status, nilai;
    bool sudahDinilai;
    
    TugasItemNilai() {}
    TugasItemNilai(const Tugas& t, const string& s, const string& n, bool sd) : 
        id(t.id), deskripsi(t.deskripsi), deadline(t.deadline), 
        kodeMK(t.kodeMK), status(s), nilai(n), sudahDinilai(sd) {}
};

// Operator untuk sorting
bool operator>(const TugasItemNilai& a, const TugasItemNilai& b) {
    if (a.sudahDinilai != b.sudahDinilai) return a.sudahDinilai;
    
    // Parse dan bandingkan deadline
    int ya, ma, da, yb, mb, db;
    sscanf(a.deadline.c_str(), "%d-%d-%d", &ya, &ma, &da);
    sscanf(b.deadline.c_str(), "%d-%d-%d", &yb, &mb, &db);
    
    if (ya != yb) return ya < yb;
    if (ma != mb) return ma < mb;
    return da < db;
}

void loadTugas() {
    // Buka file tugas.csv
    ifstream file("data/tugas.csv");
    
    if (!file.is_open()) return;
    
    // Baca file tugas
    string line;
    getline(file, line); // Skip header
    
    daftarTugas.clear();
    while (getline(file, line)) {
        stringstream ss(line);
        Tugas t;
        
        getline(ss, t.id, ',');
        getline(ss, t.deskripsi, ',');
        getline(ss, t.deadline, ',');
        getline(ss, t.kodeMK, ',');
        
        daftarTugas.push_back(t);
    }
    file.close();
    
    // Baca file jawaban
    ifstream jawabanFile("data/jawaban.csv");
    if (!jawabanFile.is_open()) {
        ofstream createFile("data/jawaban.csv");
        if (createFile.is_open()) {
            createFile << "TUGAS_ID,NIM,JAWABAN,NILAI,DINILAI\n";
            createFile.close();
            jawabanFile.open("data/jawaban.csv");
        }
    }
    
    if (jawabanFile.is_open()) {
        getline(jawabanFile, line); // Skip header
        
        while (getline(jawabanFile, line)) {
            stringstream ss(line);
            string tugasId, nim, jawaban, nilaiStr, dinilaiStr;
            
            getline(ss, tugasId, ',');
            getline(ss, nim, ',');
            getline(ss, jawaban, ',');
            getline(ss, nilaiStr, ',');
            getline(ss, dinilaiStr);
            
            // Tambahkan jawaban ke tugas
            for (auto& tugas : daftarTugas) {
                if (tugas.id == tugasId) {
                    JawabanTugas jt;
                    jt.nim = nim;
                    jt.jawabanText = jawaban;
                    jt.nilai = stoi(nilaiStr);
                    jt.sudahDinilai = (dinilaiStr == "1");
                    
                    tugas.jawaban[nim] = jt;
                    
                    // Tambahkan ke antrian jika belum dinilai
                    if (!jt.sudahDinilai) {
                        PenilaianTugas pt = {tugasId, nim};
                        antriPenilaian.enqueue(pt);
                    }
                    break;
                }
            }
        }
        jawabanFile.close();
    }
}

void saveTugas() {
    // Simpan tugas ke file
    ofstream file("data/tugas.csv");
    if (!file.is_open()) return;
    
    file << "ID,DESKRIPSI,DEADLINE,KODE_MK\n";
    for (const auto& t : daftarTugas) {
        file << t.id << "," << t.deskripsi << "," << t.deadline << "," << t.kodeMK << "\n";
    }
    file.close();
    
    // Simpan jawaban ke file
    ofstream jawabanFile("data/jawaban.csv");
    if (!jawabanFile.is_open()) return;
    
    jawabanFile << "TUGAS_ID,NIM,JAWABAN,NILAI,DINILAI\n";
    for (const auto& tugas : daftarTugas) {
        for (const auto& [nim, jawaban] : tugas.jawaban) {
            jawabanFile << tugas.id << ","
                      << nim << ","
                      << jawaban.jawabanText << ","
                      << jawaban.nilai << ","
                      << (jawaban.sudahDinilai ? "1" : "0") << "\n";
        }
    }
    jawabanFile.close();
}

void tampilkanTugas(const string& sortMode) {
    if (currentMataKuliah.empty()) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        return;
    }
    
    // Filter tugas berdasarkan mata kuliah
    vector<Tugas> filteredTugas;
    for (const auto& t : daftarTugas) {
        if (t.kodeMK == currentMataKuliah) {
            filteredTugas.push_back(t);
        }
    }
    
    if (filteredTugas.empty()) {
        display_info("Belum ada tugas untuk mata kuliah ini.");
        return;
    }
    
    // UNTUK DOSEN
    if (Auth::isDosen()) {
        vector<vector<string>> table_data = {{"ID", "DESKRIPSI", "DEADLINE", "JAWABAN"}};
        
        // Sort by deadline jika diminta
        if (sortMode == "deadline") {
            PriorityQueue<TugasItem> pq;
            for (const auto& t : filteredTugas) {
                pq.tambah(TugasItem(t));
            }
            
            filteredTugas.clear();
            while (!pq.isEmpty()) {
                TugasItem item = pq.ambil();
                for (const auto& t : daftarTugas) {
                    if (t.id == item.id && t.kodeMK == currentMataKuliah) {
                        filteredTugas.push_back(t);
                        break;
                    }
                }
            }
        }
        
        // Tampilkan tugas ke tabel
        for (const auto& t : filteredTugas) {
            table_data.push_back({t.id, t.deskripsi, t.deadline, to_string(t.jawaban.size())});
        }
        draw_table(table_data, {10, 30, 15, 10});
    }
    // UNTUK MAHASISWA
    else {
        vector<vector<string>> table_data = {{"ID", "DESKRIPSI", "DEADLINE", "STATUS", "NILAI"}};
        string nim = Auth::getCurrentNIM();
        
        vector<TugasItemNilai> items;
        for (const auto& t : filteredTugas) {
            string status = "Belum Mengumpulkan";
            string nilai = "-";
            bool sudahDinilai = false;
            
            auto it = t.jawaban.find(nim);
            if (it != t.jawaban.end()) {
                status = "Sudah Mengumpulkan";
                sudahDinilai = it->second.sudahDinilai;
                nilai = sudahDinilai ? to_string(it->second.nilai) : "Belum Dinilai";
            }
            
            items.push_back(TugasItemNilai(t, status, nilai, sudahDinilai));
        }
        
        // Sort berdasarkan mode
        if (sortMode == "deadline") {
            PriorityQueue<TugasItem> pq;
            for (const auto& t : filteredTugas) {
                string status = "Belum Mengumpulkan";
                string nilai = "-";
                
                auto it = t.jawaban.find(nim);
                if (it != t.jawaban.end()) {
                    status = "Sudah Mengumpulkan";
                    nilai = it->second.sudahDinilai ? to_string(it->second.nilai) : "Belum Dinilai";
                }
                
                pq.tambah(TugasItem(t));
            }
            
            items.clear();
            while (!pq.isEmpty()) {
                TugasItem item = pq.ambil();
                for (const auto& t : daftarTugas) {
                    if (t.id == item.id && t.kodeMK == currentMataKuliah) {
                        string status = "Belum Mengumpulkan";
                        string nilai = "-";
                        bool sudahDinilai = false;
                        
                        auto it = t.jawaban.find(nim);
                        if (it != t.jawaban.end()) {
                            status = "Sudah Mengumpulkan";
                            sudahDinilai = it->second.sudahDinilai;
                            nilai = sudahDinilai ? to_string(it->second.nilai) : "Belum Dinilai";
                        }
                        
                        items.push_back(TugasItemNilai(t, status, nilai, sudahDinilai));
                        break;
                    }
                }
            }
        } 
        else if (sortMode == "nilai") {
            // Sort berdasarkan nilai
            MergeSort<TugasItemNilai>::sort(items);
        }
        
        // Tampilkan hasil ke tabel
        for (const auto& item : items) {
            table_data.push_back({item.id, item.deskripsi, item.deadline, item.status, item.nilai});
        }
        draw_table(table_data, {10, 25, 15, 20, 10});
    }
}

void tambahTugasUI() {
    if (currentMataKuliah.empty()) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    Tugas t;
    cout << "ID Tugas: "; getline(cin, t.id);
    
    // Cek duplikat
    for (const auto& tugas : daftarTugas) {
        if (tugas.id == t.id) {
            display_error("ID tugas sudah digunakan!");
            pause_input();
            return;
        }
    }
    
    cout << "Deskripsi: "; getline(cin, t.deskripsi);
    cout << "Deadline (YYYY-MM-DD): "; getline(cin, t.deadline);
    t.kodeMK = currentMataKuliah;
    
    daftarTugas.push_back(t);
    saveTugas();
    
    display_success("Tugas berhasil ditambahkan!");
    pause_input();
}

void kirimTugasUI() {
    if (currentMataKuliah.empty()) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    tampilkanTugas();
    
    string id;
    cout << "\nID Tugas: ";
    cin >> id;
    cin.ignore();
    
    // Cari tugas
    Tugas* tugas = nullptr;
    for (auto& t : daftarTugas) {
        if (t.id == id && t.kodeMK == currentMataKuliah) {
            tugas = &t;
            break;
        }
    }
    
    if (!tugas) {
        display_error("Tugas tidak ditemukan!");
        pause_input();
        return;
    }
    
    // Input jawaban
    string jawaban;
    cout << "Jawaban Anda: ";
    getline(cin, jawaban);
    
    // Simpan jawaban
    JawabanTugas jt;
    jt.nim = Auth::getCurrentNIM();
    jt.jawabanText = jawaban;
    jt.nilai = -1;
    jt.sudahDinilai = false;
    
    // Tambah ke queue penilaian
    PenilaianTugas pt = {tugas->id, jt.nim};
    antriPenilaian.enqueue(pt);
    
    tugas->jawaban[jt.nim] = jt;
    saveTugas();
    
    display_success("Jawaban berhasil dikirim!");
    pause_input();
}

void nilaiDariAntrianUI() {
    if (antriPenilaian.isEmpty()) {
        display_info("Tidak ada tugas dalam antrian penilaian");
        pause_input();
        return;
    }
    
    // Ambil dari antrian
    PenilaianTugas pt = antriPenilaian.dequeue();
    
    // Cari tugas
    Tugas* tugas = nullptr;
    for (auto& t : daftarTugas) {
        if (t.id == pt.tugasId) {
            tugas = &t;
            break;
        }
    }
    
    if (!tugas || tugas->jawaban.find(pt.nim) == tugas->jawaban.end()) {
        display_error("Tugas atau jawaban tidak ditemukan!");
        pause_input();
        return;
    }
    
    auto& jawaban = tugas->jawaban[pt.nim];
    
    // Tampilkan info
    display_header("PENILAIAN TUGAS");
    cout << "ID Tugas: " << tugas->id << endl;
    cout << "Deskripsi: " << tugas->deskripsi << endl;
    cout << "NIM: " << pt.nim << endl;
    cout << "Jawaban:\n" << jawaban.jawabanText << endl << endl;
    
    // Input nilai
    int nilai;
    cout << "Nilai (0-100): ";
    cin >> nilai;
    cin.ignore();
    
    if (cin.fail() || nilai < 0 || nilai > 100) {
        cin.clear(); cin.ignore();
        display_error("Nilai tidak valid!");
        pause_input();
        return;
    }
    
    // Simpan untuk undo
    UndoPenilaian undoData = {pt.tugasId, pt.nim, jawaban.nilai, jawaban.sudahDinilai};
    undoStack.push(undoData);
    
    // Update nilai
    jawaban.nilai = nilai;
    jawaban.sudahDinilai = true;
    saveTugas();
    
    display_success("Nilai berhasil disimpan!");
    pause_input();
}

// Function to calculate and display student's assignment submission statistics
void tampilkanStatistikTugas() {
    if (!Auth::isMahasiswa()) {
        display_error("Fitur ini hanya untuk mahasiswa!");
        pause_input();
        return;
    }
    
    string nim = Auth::getCurrentNIM();
    
    // Variables to track assignments
    int totalTugas = 0;
    int sudahDikumpulkan = 0;
    int sudahDinilai = 0;
    double totalNilai = 0;
    
    // Map to store per-course statistics
    map<string, tuple<int, int, int, double>> statsMK; // kodeMK -> {total, submitted, graded, avgScore}
    
    // Group assignments by course and count statistics
    for (const auto& tugas : daftarTugas) {
        // Initialize course stats if needed
        if (statsMK.find(tugas.kodeMK) == statsMK.end()) {
            statsMK[tugas.kodeMK] = make_tuple(0, 0, 0, 0.0);
        }
        
        auto& [mkTotal, mkSubmitted, mkGraded, mkAvgScore] = statsMK[tugas.kodeMK];
        mkTotal++;
        totalTugas++;
        
        auto it = tugas.jawaban.find(nim);
        if (it != tugas.jawaban.end()) {
            sudahDikumpulkan++;
            mkSubmitted++;
            
            if (it->second.sudahDinilai) {
                sudahDinilai++;
                mkGraded++;
                totalNilai += it->second.nilai;
                mkAvgScore += it->second.nilai;
            }
        }
    }
    
    // Calculate averages for courses with graded assignments
    for (auto& [kodeMK, stats] : statsMK) {
        auto& [total, submitted, graded, avgScore] = stats;
        if (graded > 0) {
            avgScore /= graded;
        }
    }
    
    double persentaseKumpul = (totalTugas > 0) ? 
        (static_cast<double>(sudahDikumpulkan) / totalTugas) * 100 : 0;
    double rataRataNilai = (sudahDinilai > 0) ? 
        (totalNilai / sudahDinilai) : 0;
    
    // Display overall statistics
    display_header("STATISTIK PENGUMPULAN TUGAS");
    
    cout << "Statistik Keseluruhan:" << endl;
    cout << "Total Tugas: " << totalTugas << endl;
    cout << "Sudah Dikumpulkan: " << sudahDikumpulkan << " (" 
         << fixed << setprecision(2) << persentaseKumpul << "%)" << endl;
    cout << "Sudah Dinilai: " << sudahDinilai << endl;
    cout << "Rata-rata Nilai: " << fixed << setprecision(2) << rataRataNilai << endl;
    cout << "\n";
    
    // Display statistics per course
    cout << "Statistik per Mata Kuliah:" << endl;
    
    vector<vector<string>> table_data = {{"KODE MK", "NAMA MK", "TOTAL", "DIKUMPULKAN", "PERSENTASE", "RATA-RATA NILAI"}};
    
    for (const auto& [kodeMK, stats] : statsMK) {
        auto& [total, submitted, graded, avgScore] = stats;
        
        // Skip courses with no assignments
        if (total == 0) continue;
        
        // Get course name using the daftarMataKuliah map
        string namaMK = "Unknown";
        auto mkIter = daftarMataKuliah.find(kodeMK);
        if (mkIter != daftarMataKuliah.end()) {
            namaMK = mkIter->second.nama;
        }
        
        double persentaseMK = (static_cast<double>(submitted) / total) * 100;
        
        table_data.push_back({
            kodeMK,
            namaMK,
            to_string(total),
            to_string(submitted),
            to_string(static_cast<int>(persentaseMK)) + "%",
            (graded > 0) ? to_string(static_cast<int>(avgScore)) : "-"
        });
    }
    
    draw_table(table_data, {10, 25, 10, 15, 15, 15});
    
    pause_input();
}

void undoNilaiTugas() {
    if (undoStack.isEmpty()) {
        display_info("Tidak ada penilaian yang dapat di-undo");
        pause_input();
        return;
    }
    
    // Ambil data undo
    UndoPenilaian undoData = undoStack.pop();
    
    // Cari tugas
    for (auto& tugas : daftarTugas) {
        if (tugas.id == undoData.tugasId && 
            tugas.jawaban.find(undoData.nim) != tugas.jawaban.end()) {
            
            // Kembalikan nilai sebelumnya
            auto& jawaban = tugas.jawaban[undoData.nim];
            jawaban.nilai = undoData.nilaiSebelumnya;
            jawaban.sudahDinilai = undoData.sudahDinilaiSebelumnya;
            
            // Jika kembali ke belum dinilai, masukkan kembali ke antrian
            if (!undoData.sudahDinilaiSebelumnya) {
                PenilaianTugas pt = {undoData.tugasId, undoData.nim};
                antriPenilaian.enqueue(pt);
            }
            
            saveTugas();
            
            display_success("Penilaian berhasil di-undo!");
            pause_input();
            return;
        }
    }
    
    display_error("Tugas atau jawaban tidak ditemukan!");
    pause_input();
}

void menuKelolaTugas() {
    if (!getCurrentMataKuliah()) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    int pilihan;
    do {
        display_header("KELOLA TUGAS: " + getCurrentMataKuliah()->nama);
        
        // Gunakan display_menu yang lebih sederhana untuk menu
        vector<string> menu_items = {
            "1. Tambah Tugas",
            "2. Lihat Tugas (Default)",
            "3. Lihat Tugas (Sort by Deadline)",
            "4. Nilai Tugas dari Antrian",
            "5. Undo Penilaian Terakhir",
            "6. Kembali"
        };
        
        display_menu(menu_items);
        
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        if (cin.fail()) {
            cin.clear(); cin.ignore();
            continue;
        }
        
        switch(pilihan) {
            case 1: tambahTugasUI(); break;
            case 2: tampilkanTugas(); pause_input(); break;
            case 3: tampilkanTugas("deadline"); pause_input(); break;
            case 4: nilaiDariAntrianUI(); break;
            case 5: undoNilaiTugas(); break;
            case 6: break;
            default: display_error("Pilihan tidak valid!"); pause_input();
        }
    } while(pilihan != 6);
}

void menuTugasMahasiswa() {
    if (!getCurrentMataKuliah()) {
        display_error("Pilih mata kuliah terlebih dahulu!");
        pause_input();
        return;
    }
    
    int pilihan;
    do {
        display_header("TUGAS MAHASISWA: " + getCurrentMataKuliah()->nama);
        
        // Gunakan display_menu yang lebih sederhana untuk menu
        vector<string> menu_items = {
            "1. Lihat Tugas (Default)",
            "2. Lihat Tugas (Sort by Deadline)",
            "3. Lihat Statistik Pengumpulan Tugas",
            "4. Lihat Tugas (Sort by Status Nilai)",
            "5. Kirim Tugas",
            "6. Kembali"
        };
        
        display_menu(menu_items);
        
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        if (cin.fail()) {
            cin.clear(); cin.ignore();
            continue;
        }
        
        switch(pilihan) {
            case 1: tampilkanTugas(); pause_input(); break;
            case 2: tampilkanTugas("deadline"); pause_input(); break;
            case 3: tampilkanStatistikTugas();break;
            case 4: tampilkanTugas("nilai"); pause_input(); break;
            case 5: kirimTugasUI(); break;
            case 6: break;
            default: display_error("Pilihan tidak valid!"); pause_input();
        }
    } while(pilihan != 6);
}