#include "bloom_filter.h"

BloomFilter::BloomFilter(size_t size, int num_hashes, int prime)
    : size(size), num_hashes(num_hashes), bits(size, false), hash_functions(num_hashes, size, prime) {}

void BloomFilter::add(const std::string &data) {
    for (int i = 0; i < num_hashes; ++i) {
        size_t hash_value = hash_functions.get_hash(i, data);
        bits[hash_value % size] = true;
    }
}

bool BloomFilter::possibly_contains(const std::string &data) const {
    for (int i = 0; i < num_hashes; ++i) {
        size_t hash_value = hash_functions.get_hash(i, data);
        if (!bits[hash_value % size]) {
            return false;
        }
    }
    return true;
}
