#include "sorts.h"
#include "../environment/comparator.h"

void merge(std::vector<std::string>& arr, int left, int mid, int right, CharCompareCounter& cmp) {
    std::vector<std::string> leftPart(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<std::string> rightPart(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < leftPart.size() && j < rightPart.size()) {
        if (cmp.compare(leftPart[i], rightPart[j]) <= 0) {
            arr[k++] = leftPart[i++];
        } else {
            arr[k++] = rightPart[j++];
        }
    }

    while (i < leftPart.size()) {
        arr[k++] = leftPart[i++];
    }

    while (j < rightPart.size()) {
        arr[k++] = rightPart[j++];
    }
}

void mergeSort(std::vector<std::string>& arr, int left, int right, CharCompareCounter& cmp) {
    if (left >= right) {
        return;
    }

    int mid = (left + right) / 2;
    mergeSort(arr, left, mid, cmp);
    mergeSort(arr, mid + 1, right, cmp);
    merge(arr, left, mid, right, cmp);
}
