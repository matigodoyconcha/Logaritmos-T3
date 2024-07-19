#ifndef TESTING_H
#define TESTING_H

#include <vector>
#include <string>
#include "bloom_filter.h"

void Testing(int N, double p, BloomFilter &filter, std::vector<std::string> &baby_names, std::vector<std::string> &movie_names, std::string &filename);

#endif // TESTING_H
