#include <vector>
#include <algorithm>
#include <random>
#include <omp.h>

// Функция для слияния двух отсортированных подмассивов
void merge(std::vector<int>& array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = array[left + i];
    for (int i = 0; i < n2; i++) R[i] = array[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k++] = L[i++];
        } else {
            array[k++] = R[j++];
        }
    }

    while (i < n1) array[k++] = L[i++];
    while (j < n2) array[k++] = R[j++];
}

// Последовательная сортировка слиянием
void mergeSort(std::vector<int>& array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

// Параллельная сортировка слиянием
void parallelMergeSort(std::vector<int>& array, int left, int right, int depth = 0) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        if (depth <= 3) { // Ограничиваем глубину параллелизма
#pragma omp parallel sections
            {
#pragma omp section
                parallelMergeSort(array, left, mid, depth + 1);
#pragma omp section
                parallelMergeSort(array, mid + 1, right, depth + 1);
            }
        } else {
            mergeSort(array, left, mid);
            mergeSort(array, mid + 1, right);
        }

        merge(array, left, mid, right);
    }
}