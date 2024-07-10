#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include "bloom_filter.h"

std::vector<std::string> load_csv(const std::string &filename) {
    std::vector<std::string> data;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }
    return data;
}

int main() {
    const size_t bloom_filter_size = 10000;
    const int num_hashes = 7;
    BloomFilter bloom_filter(bloom_filter_size, num_hashes);

    std::vector<std::string> baby_names = load_csv("Popular-Baby-Names.csv");
    for (const auto &name : baby_names) {
        bloom_filter.add(name);
    }

    std::vector<std::string> search_names = load_csv("Film-Names.csv");
    std::clock_t start;
    double duration;

    // Search without Bloom filter
    start = std::clock();
    for (const auto &name : search_names) {
        bool found = (std::find(baby_names.begin(), baby_names.end(), name) != baby_names.end());
    }
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    std::cout << "Search without Bloom filter took " << duration << " seconds." << std::endl;

    // Search with Bloom filter
    start = std::clock();
    for (const auto &name : search_names) {
        if (bloom_filter.possibly_contains(name)) {
            bool found = (std::find(baby_names.begin(), baby_names.end(), name) != baby_names.end());
        }
    }
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    std::cout << "Search with Bloom filter took " << duration << " seconds." << std::endl;

    return 0;
}
