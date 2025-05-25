#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <string>
#include "../environment/comparator.h"

void mergeSort(std::vector<std::string>& arr, int left, int right, CharCompareCounter& cmp);

void quickRadixSort(std::vector<std::string> &arr, int l, int r, int d, std::vector<std::string> &aux, CharCompareCounter& cmp);

void quickSort(std::vector<std::string>& arr, int low, int high, CharCompareCounter& cmp);

void radixSort(std::vector<std::string> &arr, int l, int r, int d, std::vector<std::string> &aux, CharCompareCounter& cmp);

void strMergeSort(std::vector<std::string>& arr, int left, int right, CharCompareCounter& cmp);

void strQuickSort(std::vector<std::string>& arr, int l, int  r, int d, CharCompareCounter& cmp);

inline int charAt(const std::string &s, int d, CharCompareCounter& cmp) {
    ++cmp.count;
    return d < s.length() ? (unsigned char)s[d] : -1;
}

#endif