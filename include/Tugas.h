#ifndef TUGAS_H
#define TUGAS_H

#include <string>
#include <map>
#include <vector>
#include "Queue.h"
#include "Stack.h"

struct JawabanTugas {
    std::string nim;
    std::string jawabanText;
    int nilai = -1;
    bool sudahDinilai = false;
};

struct Tugas {
    std::string id;
    std::string deskripsi;
    std::string deadline;
    std::string kodeMK;
    std::map<std::string, JawabanTugas> jawaban;
};

struct PenilaianTugas {
    std::string tugasId;
    std::string nim;
};

struct UndoPenilaian {
    std::string tugasId;
    std::string nim;
    int nilaiSebelumnya;
    bool sudahDinilaiSebelumnya;
};

struct TugasItem {
    std::string id, deskripsi, deadline, kodeMK, status, nilai;
    TugasItem() {}
    TugasItem(const Tugas& t) : id(t.id), deskripsi(t.deskripsi), deadline(t.deadline), kodeMK(t.kodeMK) {}
};

void loadTugas();
void saveTugas();
void menuKelolaTugas();
void menuTugasMahasiswa();
void tampilkanTugas(const std::string& sortMode = "");
void tampilkanStatistikTugas();

extern std::vector<Tugas> daftarTugas;
extern Queue<PenilaianTugas> antriPenilaian;
extern Stack<UndoPenilaian> undoStack;

#endif