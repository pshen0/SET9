#include "sorts.h"
#include "../environment/comparator.h"

bool cmpLess(const std::string& s, const std::string& t, CharCompareCounter& cmp) {
    return cmp.less(s, t);
}

void strMerge(std::vector<std::string>& arr, int left, int mid, int right, CharCompareCounter& cmp) {
    std::vector<std::string> temp(right - left + 1);

    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right) {
        if (cmpLess(arr[i], arr[j], cmp)) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int idx = 0; idx < (int)temp.size(); ++idx) {
        arr[left + idx] = temp[idx];
    }
}

void strMergeSort(std::vector<std::string>& arr, int left, int right, CharCompareCounter& cmp) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    strMergeSort(arr, left, mid, cmp);
    strMergeSort(arr, mid + 1, right, cmp);
    strMerge(arr, left, mid, right, cmp);
}
