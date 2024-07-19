#ifndef HASH_H
#define HASH_H

#include <vector>
#include <functional>
#include <string>

class HashFunctions {
public:
    HashFunctions(int k, int m, int p);

    int get_hash(int index, const std::string& x) const; // Marked as const

private:
    void ensure_a_size(int length, const std::string& x) const; // Marked as const

    int k_, m_, p_;
    std::vector<std::function<int(const std::string&)>> generators_;
    mutable std::vector<std::vector<int>> a_values_; // Marked as mutable
    std::vector<int> b_values_;
};

#endif // HASH_H
