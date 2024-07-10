#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <functional>
#include <string>

class BloomFilter {
public:
    BloomFilter(size_t size, int num_hashes);
    void add(const std::string &data);
    bool possibly_contains(const std::string &data) const;

private:
    size_t size;
    int num_hashes;
    std::vector<bool> bits;
    std::vector<std::function<size_t(const std::string&)>> hash_functions;

    size_t hash(const std::string &data, int index) const;
    void initialize_hash_functions();
};

#endif // BLOOM_FILTER_H
