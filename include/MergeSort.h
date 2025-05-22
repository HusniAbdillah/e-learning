#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>

template <typename T>
class MergeSort {
private:
    // Fungsi merge untuk menggabungkan dua array terurut
    static void merge(std::vector<T>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        // Buat array temporary
        std::vector<T> L(n1), R(n2);
        
        // Copy data ke array temporary
        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];
        
        // Gabungkan array kembali
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            // Gunakan operator > yang sudah didefinisikan
            if (L[i] > R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        
        // Copy sisa elemen jika ada
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
    
    // Fungsi merge sort rekursif
    static void mergeSort(std::vector<T>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            
            // Sort bagian pertama dan kedua
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            
            // Gabungkan bagian yang sudah disort
            merge(arr, left, mid, right);
        }
    }

public:
    // Fungsi publik untuk menjalankan merge sort
    static void sort(std::vector<T>& arr) {
        if (arr.size() <= 1) return; // Tidak perlu sort jika ukuran ≤ 1
        
        mergeSort(arr, 0, arr.size() - 1);
    }
};

#endif