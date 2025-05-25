#include "sorts.h"
#include "../comparator.h"

void radixSort(std::vector<std::string> &arr, int l, int r, int d, std::vector<std::string> &aux, CharCompareCounter& cmp) {
    if (r <= l) return;

    std::vector<int> count(256 + 2, 0);

    for (int i = l; i <= r; ++i) {
        int c = charAt(arr[i], d, cmp);
        count[c + 2]++;
    }

    for (int i = 0; i < 256 + 1; ++i) {
        count[i + 1] += count[i];
    }

    for (int i = l; i <= r; ++i) {
        int c = charAt(arr[i], d, cmp);
        aux[count[c + 1]++] = arr[i];
    }

    for (int i = l; i <= r; ++i) {
        arr[i] = aux[i - l];
    }

    for (int i = 0; i < 256; ++i) {
        radixSort(arr, l + count[i], l + count[i + 1] - 1, d + 1, aux, cmp);
    }
}