#include "sorts.h"
#include "../comparator.h"


void quickSort(std::vector<std::string>& arr, int l, int r, int d, CharCompareCounter& cmp) {
    if (l >= r) return;

    int less = l, greater = r;
    int pivot = charAt(arr[l], d, cmp);
    int i = l + 1;

    while (i <= greater) {
        int cur = charAt(arr[i], d, cmp);
        if (cur < pivot) {
            std::swap(arr[less], arr[i]);
            less++; i++;
        } else if (cur > pivot) {
            std::swap(arr[i], arr[greater]);
            greater--;
        } else {
            i++;
        }
    }

    quickSort(arr, l, less - 1, d, cmp);
    if (pivot >= 0) {
        quickSort(arr, less, greater, d + 1, cmp);
    }
    quickSort(arr, greater + 1, r, d, cmp);
}


void quickRadixSort(std::vector<std::string> &arr, int l, int r, int d, std::vector<std::string> &aux, CharCompareCounter& cmp) {
    if (r <= l) return;

    if (r - l + 1 < 74) {
        quickSort(arr, l, r, d, cmp);
        return;
    }

    std::vector<int> count(256 + 2, 0);

    for (int i = l; i <= r; ++i) {
        count[charAt(arr[i], d, cmp) + 2]++;
    }

    for (int i = 0; i < 256 + 1; ++i) {
        count[i + 1] += count[i];
    }

    for (int i = l; i <= r; ++i) {
        aux[count[charAt(arr[i], d, cmp) + 1]++] = arr[i];
    }

    for (int i = l; i <= r; ++i) {
        arr[i] = aux[i - l];
    }

    for (int i = 0; i < 256; ++i) {
        quickRadixSort(arr, l + count[i], l + count[i + 1] - 1, d + 1, aux, cmp);
    }
}
