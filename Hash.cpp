#include "Hash.h"
#include <random>
#include <stdexcept>

HashFunctions::HashFunctions(int k, int m, int p) : k_(k), m_(m), p_(p), generators_(k), a_values_(k), b_values_(k) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_b(0, p - 1);
    std::uniform_int_distribution<> dis_a(1, p - 1);
    
    for (int i = 0; i < k_; ++i) {
        b_values_[i] = dis_b(gen);
        // Initially reserve space for a small number of coefficients
        a_values_[i].reserve(10);
        for (int j = 0; j < 10; ++j) {
            a_values_[i].push_back(dis_a(gen));
        }
    }

    for (int i = 0; i < k_; ++i) {
        generators_[i] = [this, i, p, m](const std::string& x) {
            this->ensure_a_size(x.size());
            int hash = this->b_values_[i];
            for (size_t j = 0; j < x.size(); ++j) {
                hash = (hash + this->a_values_[i][j] * x[j]) % p;
            }
            return hash % m;
        };
    }
}

void HashFunctions::ensure_a_size(int length) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_a(1, p_ - 1);

    for (auto& a : a_values_) {
        while (a.size() < length) {
            a.push_back(dis_a(gen));
        }
    }
}

int HashFunctions::get_hash(int index, const std::string& x) const {
    if (index < 0 || index >= k_) {
        throw std::out_of_range("Invalid hash function index");
    }
    return generators_[index](x);
}
