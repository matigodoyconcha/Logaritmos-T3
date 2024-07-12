#include "Testing.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;

void Testing(int N, double p, BloomFilter &filter, vector<string> &baby_names, vector<string> &movie_names, string &filename) {
    vector<string> search_names;
    int num_baby_names = static_cast<int>(N * p);
    int num_movie_names = N - num_baby_names;
    cout << "N: "<< N << " movie_name :" << num_movie_names << endl;
    
    // Initialize a random number generator
    random_device rd;
    mt19937 gen(rd());
    
    // Select random elements from baby_names
    if (num_baby_names > 0) {
        sample(baby_names.begin(), baby_names.end(), back_inserter(search_names), num_baby_names, gen);
    }
    
    // Select random elements from movie_names
    if (num_movie_names > movie_names.size()) {
        cout << "N es muy grande" << N << p << endl;
        while (search_names.size() < N) {
            int remaining = N - search_names.size();
            int count = min(static_cast<int>(movie_names.size()), remaining);
            sample(movie_names.begin(), movie_names.end(), back_inserter(search_names), count, gen);
        }
    } else {
        sample(movie_names.begin(), movie_names.end(), back_inserter(search_names), num_movie_names, gen);
    }
    ofstream file;

    // Open the file in append mode
    file.open(filename, ios::app);
    file << N << ";" << p << ";";
    
    // Measure search time without Bloom filter
    auto start = chrono::high_resolution_clock::now();
    for (const auto &name : search_names) {
        bool found = (find(baby_names.begin(), baby_names.end(), name) != baby_names.end());
    }
    auto duration = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();
    file << duration << ";";

    // Measure search time with Bloom filter
    start = chrono::high_resolution_clock::now();
    long long count1 = 0;
    long long count2 = 0;
    for (const auto &name : search_names) {
        if (filter.possibly_contains(name)) {
            bool found = (find(baby_names.begin(), baby_names.end(), name) != baby_names.end());
            count1++;
        } else {
            count2++;
        }
    }
    duration = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();
    file << duration << ";";
   
    // Calculate error rate
    file << (count1 - N*p)/(N) << ";";
    file << endl;
}
