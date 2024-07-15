#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Testing.h"

using namespace std;

std::vector<std::string> load_csv(const std::string &filename) {
    std::vector<std::string> data;
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream line_stream(line);
        std::string word;
        
        while (line_stream >> word) {
            data.push_back(word);
        }
    }
    
    return data;
}

std::vector<std::string> filter_movies(const std::vector<std::string>& movies, const std::vector<std::string>& baby_names) {
    std::vector<std::string> filtered_movies;
    for (const auto& movie : movies) {
        if (find(baby_names.begin(), baby_names.end(), movie) == baby_names.end()) {
            filtered_movies.push_back(movie);
        }
    }
    return filtered_movies;
}

int main() {
    const size_t bloom_filter_size = 93890*10;
    const int num_hashes = 7;
    const int prime = 908521; 
    BloomFilter bloom_filter(bloom_filter_size, num_hashes, prime);

    vector<string> baby_names = load_csv("Popular-Baby-Names-Final.csv");
    for (const auto &name : baby_names) {
        bloom_filter.add(name);
    }

    cout << baby_names.size() << " baby names loaded." << endl;

    vector<string> movie_names = load_csv("Film-Names.csv");
    vector<string> search_names = filter_movies(movie_names, baby_names);
    cout << search_names.size() << " movie names loaded." << endl;

    string filename = "Results.txt";
    ofstream file;
    file.open(filename);
    file << "N;p;Time without Bloom filter;Time with Bloom filter;Error rate" << endl;
    file.close();
    for (int i = 10; i < 17; i += 2) {
        for (double p = 0; p <= 1.0; p += 0.25) {
            Testing(pow(2, i), p, bloom_filter, baby_names, search_names, filename);
        }
    }

    return 0;
}
