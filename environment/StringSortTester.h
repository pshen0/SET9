#ifndef STRING_SORT_TESTER_H
#define STRING_SORT_TESTER_H

#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <functional>
#include <iostream>
#include "sorting/sorts.h"
#include "comparator.h"

namespace fs = std::filesystem;

class StringSortTester {
public:
    using SortFunction = std::function<void(std::vector<std::string>&, CharCompareCounter&)>;

    void runTests() {
        std::vector<std::string> types = {"random", "almost_sort", "reverse_sort"};
        std::vector<std::pair<std::string, SortFunction>> sorters = {
            {"merge_sort_result.txt", mergeSortWrapper},
            {"quick_sort_result.txt", quickSortWrapper},
            {"radix_sort_result.txt", radixSortWrapper},
            {"quick_radix_sort_result.txt", quickRadixSortWrapper},
            {"str_merge_sort_result.txt", strMergeSortWrapper},
            {"str_quick_sort_result.txt", strQuickSortWrapper}
        };

        std::filesystem::create_directories("../results");

        for (const auto& type : types) {
            std::filesystem::create_directories("../results/" + type);
            for (const auto& [filename, sortFunc] : sorters) {
                std::ofstream out("../results/" + type + "/" + filename);
                for (int n = 100; n <= 3000; n += 100) {
                    std::vector<std::string> data = loadData("../data/" + type + "/" + type + "_" + std::to_string(n) + ".txt");

                    CharCompareCounter cmp;
                    double avgTime = 0.0;
                    const int reps = 5;

                    for (int i = 0; i < reps; ++i) {
                        std::vector<std::string> copy = data;
                        cmp.reset();
                        auto start = std::chrono::high_resolution_clock::now();
                        sortFunc(copy, cmp);
                        auto end = std::chrono::high_resolution_clock::now();
                        avgTime += std::chrono::duration<double, std::milli>(end - start).count();
                    }

                    avgTime /= reps;
                    out << n << " " << avgTime << " " << cmp.count << "\n";
                    std::cout << "Done: " << type << " " << filename << " " << n << "\n";
                }
                out.close();
            }
        }
    }

private:
    std::vector<std::string> loadData(const std::string& filepath) {
        std::ifstream in(filepath);
        std::vector<std::string> data;
        if (!in.is_open()) {
            std::cerr << "Failed to open: " << filepath << "\n";
            return data;
        }

        int n;
        in >> n;
        std::string s;
        std::getline(in, s);
        while (std::getline(in, s)) {
            data.push_back(s);
        }

        return data;
    }

    static void mergeSortWrapper(std::vector<std::string>& arr, CharCompareCounter& cmp) {
        mergeSort(arr, 0, arr.size() - 1, cmp);
    }

    static void quickSortWrapper(std::vector<std::string>& arr, CharCompareCounter& cmp) {
        quickSort(arr, 0, arr.size() - 1, cmp);
    }

    static void radixSortWrapper(std::vector<std::string>& arr, CharCompareCounter& cmp) {
        std::vector<std::string> aux(arr.size());
        radixSort(arr, 0, arr.size() - 1, 0, aux, cmp);
    }

    static void quickRadixSortWrapper(std::vector<std::string>& arr, CharCompareCounter& cmp) {
        std::vector<std::string> aux(arr.size());
        quickRadixSort(arr, 0, arr.size() - 1, 0, aux, cmp);
    }

    static void strMergeSortWrapper(std::vector<std::string>& arr, CharCompareCounter& cmp) {
        strMergeSort(arr, 0, arr.size() - 1, cmp);
    }

    static void strQuickSortWrapper(std::vector<std::string>& arr, CharCompareCounter& cmp) {
        strQuickSort(arr, 0, arr.size() - 1, 0, cmp);
    }
};

#endif
