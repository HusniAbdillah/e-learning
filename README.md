# **CLI Program Pengolahan Data e-Learning**
# KOM120H - Struktur Data


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

## Pengguna Sistem

- Dosen  
- Mahasiswa  

---

## Requirements
Untuk membangun dan menjalankan aplikasi ini, Anda memerlukan:

- MinGW-w64 (versi 8.0.0 atau lebih tinggi)
- CMake (versi 3.10 atau lebih tinggi)
- C++14 compiler support

---

## Cara Build dari Source

### 1. Clone Repository
```bash
git clone https://github.com/HusniAbdillah/e-learning.git
cd e-learning
```

### 2. Masuk Direktori Build
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

- **Metode 1** disarankan karena lebih cepat dan langsung
- **Metode 2** berguna jika Anda ingin menggunakan CMake untuk manajemen build yang lebih advanced
- Pastikan MinGW-w64 sudah terinstall dan ter-configure dengan benar di PATH sistem
- File data akan otomatis di-copy ke direktori yang sama dengan executable

---