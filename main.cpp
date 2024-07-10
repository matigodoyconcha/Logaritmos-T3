#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include "bloom_filter.h"

using namespace std;

vector<string> load_csv(const string &filename) {
    vector<string> data;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        data.push_back(line);
    }
    return data;
}

int main() {
    const size_t bloom_filter_size = 93890*10;
    const int num_hashes = 7;
    BloomFilter bloom_filter(bloom_filter_size, num_hashes);

    vector<string> baby_names = load_csv("Popular-Baby-Names-Final.csv");
    for (const auto &name : baby_names) {
        bloom_filter.add(name);
    }

    vector<string> search_names = load_csv("Film-Names.csv");
    chrono::high_resolution_clock::time_point start;
    double duration;

    // Search without Bloom filter
    start = chrono::high_resolution_clock::now();
    for (const auto &name : search_names) {
        bool found = (find(baby_names.begin(), baby_names.end(), name) != baby_names.end());
    }
    duration = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();
    cout << "Search without Bloom filter took " << duration << " microseconds." << endl;

    // Search with Bloom filter
    start = chrono::high_resolution_clock::now();
    long long count1 = 0;
    long long count2 = 0;
    for (const auto &name : search_names) {
        if (bloom_filter.possibly_contains(name)) {
            bool found = (find(baby_names.begin(), baby_names.end(), name) != baby_names.end());
            count1++;
        }
        else{
            count2++;
        }
    }
    duration = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();
    cout << "Search with Bloom filter took " << duration << " microseconds." << endl;

    return 0;
}
