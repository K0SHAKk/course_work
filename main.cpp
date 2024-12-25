#include <iostream>
#include <vector>
#include <random>
#include "merge_sort.h"


int main() {
    // Устанавливаем количество потоков OpenMP
    omp_set_num_threads(4);
    
    const int SIZE = 100000;
    std::vector<int> array(SIZE);

    // Инициализация случайного массива
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand();
    }

    // Копия массива для последовательной сортировки
    std::vector<int> sequentialArray = array;

    // Последовательная сортировка
    double start = omp_get_wtime();
    mergeSort(sequentialArray, 0, SIZE - 1);
    double sequentialTime = omp_get_wtime() - start;

    // Параллельная сортировка
    start = omp_get_wtime();
    parallelMergeSort(array, 0, SIZE - 1);
    double parallelTime = omp_get_wtime() - start;

    // Вывод результатов
    std::cout << "\nВремя последовательной сортировки: " << sequentialTime << " секунд\n";
    std::cout << "Время параллельной сортировки: " << parallelTime << " секунд\n";
    std::cout << "Ускорение: " << sequentialTime / parallelTime << "\n";

    return 0;
}   