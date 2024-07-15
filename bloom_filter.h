#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <string>
#include "Hash.h"

class BloomFilter {
public:
    BloomFilter(size_t size, int num_hashes, int prime);
    void add(const std::string &data);
    bool possibly_contains(const std::string &data) const;
    void amount_of_true();

private:
    size_t size;
    int num_hashes;
    std::vector<bool> bits;
    HashFunctions hash_functions;
};

#endif // BLOOM_FILTER_H
