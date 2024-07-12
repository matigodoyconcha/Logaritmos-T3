#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
#include "bloom_filter.h"

using namespace std;

void Testing(int N, double p, BloomFilter &filter, vector<string> &baby_names, vector<string> &movie_names, string &filename){

    vector<string> search_names;
    int num_baby_names = static_cast<int>(N * p);
    int num_movie_names = N - num_baby_names;
    
    // Inicializa un motor de generación de números aleatorios
    random_device rd;
    mt19937 gen(rd());
    
    // Selecciona elementos aleatorios de baby_names
    if(num_baby_names > 0) {
        sample(baby_names.begin(), baby_names.end(), back_inserter(search_names), num_baby_names, gen);
    }
    
    // Selecciona elementos aleatorios de movie_names
    if(num_movie_names > 0) {
        sample(movie_names.begin(), movie_names.end(), back_inserter(search_names), num_movie_names, gen);
    }

    ofstream file;

    // Abre el archivo en modo append
    file.open(filename, ios::app);
    file << N << ";" << p << ";";
    // Medir el tiempo de búsqueda sin Bloom filter
    auto start = chrono::high_resolution_clock::now();
    for (const auto &name : search_names) {
        bool found = (find(baby_names.begin(), baby_names.end(), name) != baby_names.end());
    }
    auto duration = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();
    file << duration  << ";";

    // Medir el tiempo de búsqueda con Bloom filter
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
    file << duration  << ";";
   // Calcular tasa de error
    file << (count1 - N*p)/(N) << ";";
    file << endl;
}
