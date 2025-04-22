#include "Tugas.h"
#include "ui_helpers.hpp"

void kirimTugasUI() {
    display_header("KIRIM TUGAS");
    std::string id_tugas, jawaban;
    std::cout << "ID Tugas: ";
    std::cin >> id_tugas;
    std::cin.ignore();
    std::cout << "File Jawaban: ";
    std::getline(std::cin, jawaban);
    
    if (!daftarTugas.cekKeyExist(id_tugas)) {
        display_error("Tugas tidak ditemukan!");
    } else {
        antrianPenilaian.push(jawaban);
        display_success("Tugas berhasil dikirim ke antrian!");
    }
    pause_input();
}

void menuBuatTugas() {
    display_header("BUAT TUGAS");
    std::string id, deskripsi, deadline;
    std::cout << "ID Tugas: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Deskripsi: ";
    std::getline(std::cin, deskripsi);
    std::cout << "Deadline (YYYY-MM-DD): ";
    std::getline(std::cin, deadline);
    
    daftarTugas.tambah(id, make_pair(deskripsi, deadline));
    display_success("Tugas berhasil dibuat!");
    pause_input();
}

void menuNilaiTugas() {
    display_header("NILAI TUGAS");
    if(antrianPenilaian.empty()) {
        display_error("Tidak ada tugas yang perlu dinilai!");
    } else {
        std::string jawaban = antrianPenilaian.front();
        antrianPenilaian.pop();
        int nilai;
        std::cout << "Masukkan nilai untuk tugas: " << jawaban << endl;
        std::cout << "Nilai: ";
        std::cin >> nilai;
        
        undoStack.push(make_pair(jawaban, nilai));
        display_success("Tugas berhasil dinilai!");
    }
    pause_input();
}