#include "sorts.h"
#include "../comparator.h"

int partition(std::vector<std::string>& arr, int low, int high, CharCompareCounter& cmp) {
    std::string pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (cmp.compare(arr[j], pivot) <= 0) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<std::string>& arr, int low, int high, CharCompareCounter& cmp) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high, cmp);
        quickSort(arr, low, pivotIndex - 1, cmp);
        quickSort(arr, pivotIndex + 1, high, cmp);
    }
}

