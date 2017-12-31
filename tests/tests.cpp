//
// Created by ahoma on 12/31/17.
//

#include "gtest/gtest.h"
#include "../korselt.h"

#include <unordered_set>
#include <fstream>

std::unordered_set<uint64_t> get_korselt_num() {
    std::fstream input_file("korselt.txt", std::ios_base::in);
    std::unordered_set<uint64_t> res;
    uint64_t num;
    while (input_file >> num)
        res.insert(num);
    input_file.close();
    return res;
}

const uint64_t kMaxKorseltNum = 1713045574801, kKorseltCount = 10000; // look inside korselt.txt


TEST(BasicTest, All_korselt) {
    std::unordered_set<uint64_t> korselt = get_korselt_num();
    for (uint64_t num:korselt) {
        EXPECT_EQ(korselt_criterion(num), true);
    }
}


TEST(BasicTest, First_million) {
    std::unordered_set<uint64_t> korselt = get_korselt_num();
    for (uint64_t i = 1; i <= uint64_t(1e6); i++) {
        bool result = korselt.count(i) > 0;
        EXPECT_EQ(korselt_criterion(i), result);
    }
}

TEST(BasicTest, Random_not_korselt) {
    std::unordered_set<uint64_t> korselt = get_korselt_num();

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<uint64_t> uniform_dist(1, kMaxKorseltNum);

    std::unordered_set<uint64_t> not_korselt;
    while (not_korselt.size() < kKorseltCount) {
        uint64_t num = uniform_dist(generator);
        if (!korselt.count(num))
            not_korselt.insert(num);
    }

    for (uint64_t num:not_korselt) {
        EXPECT_EQ(korselt_criterion(num), false);
    }
}
