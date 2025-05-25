#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <string>

struct CharCompareCounter {
    long long count = 0;

    int compare(const std::string& a, const std::string& b) {
        size_t len = std::min(a.size(), b.size());
        for (size_t i = 0; i < len; ++i) {
            ++count;
            if (a[i] != b[i]) return (a[i] < b[i]) ? -1 : 1;
        }
        ++count;
        if (a.size() == b.size()) return 0;
        return (a.size() < b.size()) ? -1 : 1;
    }

    bool less(const std::string& a, const std::string& b) {
        return compare(a, b) < 0;
    }

    void reset() { count = 0; }
};

#endif
