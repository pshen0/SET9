#ifndef SORTING_GENERATOR_H
#define SORTING_GENERATOR_H

#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

class StringGenerator
{
public:
    StringGenerator()
    {
        characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-.";
        rng.seed(std::random_device{}());
    }

    void generateAll()
    {
        generateRandomStrings();
        saveVariants("random", randomStrings);
        saveVariants("reverse_sort", getReverseSorted(randomStrings));
        saveVariants("almost_sort", getAlmostSorted(randomStrings));
    }

private:
    std::vector<std::string> randomStrings;
    std::string characters;
    std::mt19937 rng;

    std::string generateRandomString(int minLen = 10, int maxLen = 200)
    {
        std::uniform_int_distribution<int> lenDist(minLen, maxLen);
        std::uniform_int_distribution<int> charDist(0, characters.size() - 1);
        int len = lenDist(rng);
        std::string result;
        result.reserve(len);
        for (int i = 0; i < len; ++i)
            result += characters[charDist(rng)];
        return result;
    }

    void generateRandomStrings()
    {
        randomStrings.clear();
        for (int i = 0; i < 3000; ++i)
            randomStrings.push_back(generateRandomString());
    }

    std::vector<std::string> getReverseSorted(const std::vector<std::string> &base)
    {
        std::vector<std::string> reversed = base;
        std::sort(reversed.begin(), reversed.end(), std::greater<>());
        return reversed;
    }

    std::vector<std::string> getAlmostSorted(const std::vector<std::string> &base)
    {
        std::vector<std::string> almost = base;
        std::sort(almost.begin(), almost.end());

        int numSwaps = 30;
        std::uniform_int_distribution<int> dist(0, 2999);
        for (int i = 0; i < numSwaps; ++i)
        {
            int idx1 = dist(rng);
            int idx2 = dist(rng);
            if (idx1 != idx2)
                std::swap(almost[idx1], almost[idx2]);
        }
        return almost;
    }

    void saveVariants(const std::string &folder, const std::vector<std::string> &data)
    {

        fs::create_directories("../data/" + folder);

        for (int size = 100; size <= 3000; size += 100)
        {
            std::string filename = "../data/" + folder + "/" + folder + "_" + std::to_string(size) + ".txt";
            std::ofstream outFile(filename);
            if (!outFile.is_open())
            {
                std::cerr << "Failed to open file: " << filename << "\n";
                continue;
            }

            outFile << size << "\n";
            for (int i = 0; i < size; ++i)
                outFile << data[i] << "\n";

            outFile.close();
        }
    }
};

#endif