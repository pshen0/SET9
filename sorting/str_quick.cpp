#include "sorts.h"
#include "../comparator.h"

void strQuickSort(std::vector<std::string>& arr, int l, int  r, int d, CharCompareCounter& cmp) {
    if (l >= r) return;

    int less = l, greater = r;
    int pivot = charAt(arr[l], d, cmp);
    int i = l + 1;

    while (i <= greater) {
        int cur = charAt(arr[i], d, cmp);
        if (cur < pivot) {
            swap(arr[less], arr[i]);
            less++; i++;
        } else if (cur > pivot) {
            swap(arr[i], arr[greater]);
            greater--;
        } else {
            i++;
        }
    }

    strQuickSort(arr, l, less - 1, d, cmp);

    if (pivot >= 0) {
        strQuickSort(arr, less, greater, d + 1, cmp);
    }
        
    strQuickSort(arr, greater + 1, r, d, cmp);
}
