#include "korselt.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./korselt <input_number>" << std::endl;
        throw std::runtime_error("Wrong usage");
    }

    uint64_t num_to_check = std::stoull(argv[1]);

    if (korselt_criterion(num_to_check))
        std::cout << "It's Carmichael number" << std::endl;
    else std::cout << "It's not Carmichael number" << std::endl;
    return 0;
}