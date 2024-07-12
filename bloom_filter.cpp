#include "bloom_filter.h"

BloomFilter::BloomFilter(size_t size, int num_hashes)
    : size(size), num_hashes(num_hashes), bits(size, false) {
    initialize_hash_functions();
}

void BloomFilter::add(const std::string &data) {
    for (int i = 0; i < num_hashes; ++i) {
        size_t hash_value = hash(data, i);
        bits[hash_value % size] = true;
    }
}

bool BloomFilter::possibly_contains(const std::string &data) const {
    for (int i = 0; i < num_hashes; ++i) {
        size_t hash_value = hash(data, i);
        if (!bits[hash_value % size]) {
            return false;
        }
    }
    return true;
}

size_t BloomFilter::hash(const std::string &data, int index) const {
    return hash_functions[index](data);
}

void BloomFilter::initialize_hash_functions() {
    hash_functions.reserve(num_hashes);
    for (int i = 0; i < num_hashes; ++i) {
        hash_functions.push_back([i](const std::string &data) {
            std::hash<std::string> hasher;
            return hasher(data + std::to_string(i));
        });
    }
}
