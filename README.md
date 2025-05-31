# **CLI Program Pengolahan Data e-Learning**
# KOM120H - Struktur Data

---

## Daftar Isi

- [Deskripsi Proyek](#deskripsi-proyek)
- [Anggota Kelompok](#anggota-kelompok)
- [Struktur Data yang Digunakan](#struktur-data-yang-digunakan)
  - [Struktur Data Buatan Sendiri (~60%)](#struktur-data-buatan-sendiri-60)
  - [Struktur Data STL (~40%)](#struktur-data-stl-40)
- [Fitur dan Struktur Data yang Digunakan](#fitur-dan-struktur-data-yang-digunakan)
- [Pengguna Sistem](#pengguna-sistem)
- [Requirements](#requirements)
- [Cara Build dan Menjalankan Program](#cara-build-dan-menjalankan-program)
  - [Metode 1: Menggunakan g++ (Disarankan)](#metode-1-menggunakan-g-disarankan)
  - [Metode 2: Menggunakan CMake (Alternative)](#metode-2-menggunakan-cmake-alternative)
- [Catatan](#catatan)

---

## Deskripsi Proyek

Program Pengolahan Data e-Learning bertujuan untuk mempermudah pengelolaan materi, penugasan, dan pengumpulan tugas mahasiswa. Sistem ini dibangun sebagai aplikasi Command Line Interface (CLI), menggunakan berbagai struktur data untuk meningkatkan efisiensi dalam pengelolaan dan pemrosesan data.

Proyek ini merupakan Tugas Akhir dari mata kuliah **KOM120H - Struktur Data**, yang dikembangkan oleh **Kelompok 8 Paralel 1**.

---

## Anggota Kelompok

**Kelompok 8 Paralel 1:**
- **Fauzan Arif Tricahya** – G6401231040  
- **Husni Abdillah** – G6401231097  
- **Muhammad Abdullah** – G6401231104  

---

## Struktur Data yang Digunakan

### Struktur Data Buatan Sendiri (~60%)

1. **HashTable**  
   - Implementasi tabel hash dengan chaining untuk menangani collision  
   - Digunakan dalam: Sistem kehadiran, autentikasi user  
   - Kompleksitas pencarian: O(1) average case

2. **LinkedList**  
   - Implementasi linked list untuk penyimpanan sekuensial  
   - Digunakan dalam: Pengelolaan materi perkuliahan  
   - Kompleksitas pencarian: O(n)

3. **Queue**  
   - Implementasi antrian dengan prinsip FIFO  
   - Digunakan dalam: Antrian penilaian tugas  
   - Kompleksitas: O(1) untuk enqueue dan dequeue

4. **Stack**  
   - Implementasi tumpukan dengan prinsip LIFO  
   - Digunakan dalam: Fitur undo pada penilaian tugas  
   - Kompleksitas: O(1) untuk push dan pop

5. **PriorityQueue**  
   - Implementasi antrian prioritas  
   - Digunakan dalam: Pengurutan tugas berdasarkan deadline  
   - Kompleksitas: O(log n) untuk insert dan delete

6. **MergeSort**  
   - Implementasi algoritma pengurutan merge sort  
   - Digunakan dalam: Pengurutan tugas berdasarkan nilai  
   - Kompleksitas: O(n log n)

### Struktur Data STL (~40%)

1. **std::vector**  
   - Digunakan dalam: Penyimpanan daftar tugas, data kehadiran, tampilan tabel  
   - Fitur: Tampilan rekap kehadiran, daftar tugas, statistik nilai

2. **std::map**  
   - Digunakan dalam: Manajemen mata kuliah, mapping jawaban tugas  
   - Fitur: Pengelolaan jawaban tugas mahasiswa

3. **std::list**  
   - Digunakan dalam: Implementasi internal HashTable untuk collision handling  
   - Fitur: Penyimpanan data dengan key yang sama dalam tabel hash

4. **std::pair**  
   - Digunakan dalam: Penyimpanan pasangan key-value di HashTable  
   - Fitur: Manajemen data kehadiran dan autentikasi

5. **std::string**  
   - Digunakan sebagai tipe data utama untuk text storage  
   - Fitur: Semua fitur yang memerlukan manipulasi teks

---

## Fitur dan Struktur Data yang Digunakan

1. **Sistem Autentikasi (Login)**
   - HashTable<string, User> - Pencarian user dengan kompleksitas O(1)

2. **Pengelolaan Materi**
   - LinkedList - Penyimpanan dan traversal materi perkuliahan
   - std::vector - Tampilan tabel materi

3. **Sistem Kehadiran**
   - HashTable<string, KehadiranInfo> - Penyimpanan data kehadiran per pertemuan
   - HashTable<string, bool> - Verifikasi kehadiran mahasiswa dengan O(1)
   - std::vector - Rekap dan laporan kehadiran

4. **Pengelolaan Tugas**
   - std::vector<Tugas> - Penyimpanan data tugas
   - PriorityQueue<TugasItem> - Pengurutan berdasarkan deadline
   - MergeSort<TugasItemNilai> - Pengurutan berdasarkan nilai

5. **Sistem Penilaian**
   - Queue<PenilaianTugas> - Antrian tugas yang perlu dinilai
   - Stack<UndoPenilaian> - Riwayat perubahan untuk fitur undo
   - std::map - Penyimpanan jawaban tugas per mahasiswa

---

## Pengguna Sistem

- Dosen  
- Mahasiswa  

---

## Requirements
Untuk membangun dan menjalankan aplikasi ini, Anda memerlukan:

- MinGW-w64 (versi 8.0.0 atau lebih tinggi)
- CMake (versi 3.10 atau lebih tinggi) - opsional
- Dukungan compiler C++14 atau lebih baru

---

## Cara Build dan Menjalankan Program

### Metode 1: Menggunakan g++ (Disarankan)

Cara ini lebih sederhana dan cepat untuk compile program:

#### 1. Clone Repository
```bash
git clone https://github.com/HusniAbdillah/e-learning.git
cd e-learning
```

#### 2. Compile Program
```bash
g++ -std=c++17 -O2 -Iinclude -o e-learning src\*.cpp
```

#### 3. Jalankan Aplikasi
```bash
.\e-learning.exe
```

---

### Metode 2: Menggunakan CMake (Alternative)

Cara ini menggunakan CMake untuk build sistem yang lebih kompleks:

#### 1. Clone Repository
```bash
git clone https://github.com/HusniAbdillah/e-learning.git
cd e-learning
```

#### 2. Masuk Direktori Build
```bash
mkdir build_mingw
cd build_mingw
```

#### 3. Jalankan CMake
```bash
cmake -G "MinGW Makefiles" ..
```

#### 4. Build Proyek
```bash
mingw32-make
```

#### 5. Jalankan Aplikasi
```bash
./e-learning.exe
```

---

## Catatan

- **Metode 1** disarankan karena lebih cepat dan langsung.
- **Metode 2** berguna jika Anda ingin menggunakan CMake untuk manajemen build yang lebih advanced.
- Pastikan MinGW-w64 sudah terinstall dan ter-configure dengan benar di PATH sistem.
- File data akan otomatis di-copy ke direktori yang sama dengan executable.

---