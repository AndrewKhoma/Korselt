//
// Created by ahoma on 12/31/17.
//

#include "korselt.h"
#include <vector>
#include <cmath>

std::vector<uint32_t> atkin_sieve(uint32_t limit) {
    std::vector<bool> is_prime(limit + 1, false);
    is_prime[2] = is_prime[3] = true;

    auto sqr_lim = static_cast<uint32_t>(sqrt(limit));

    uint64_t x2 = 0, y2, num;
    for (uint32_t fs_square = 1; fs_square <= sqr_lim; fs_square++) {
        x2 += 2 * fs_square - 1;
        y2 = 0;
        for (uint32_t sd_square = 1; sd_square <= sqr_lim; sd_square++) {
            y2 += 2 * sd_square - 1;
            num = 4 * x2 + y2;
            if ((num <= limit) && (num % 12 == 1 || num % 12 == 5))
                is_prime[num] = !is_prime[num];

            // num = 3 * x2 + y2;
            num -= x2; // Optimization
            if ((num <= limit) && (num % 12 == 7))
                is_prime[num] = !is_prime[num];

            // num = 3 * x2 - y2;
            num -= 2 * y2; // Optimization
            if ((fs_square > sd_square) && (num <= limit) && (num % 12 == 11))
                is_prime[num] = !is_prime[num];
        }
    }

    for (uint32_t square = 5; square <= sqr_lim; square++) {
        if (is_prime[square]) {
            num = square * square;
            for (auto index = static_cast<uint32_t>(num); index <= limit; index += num) {
                is_prime[index] = false;
            }
        }
    }

    std::vector<uint32_t> primes = {2, 3, 5};

    for (uint32_t index = 6; index <= limit; index++) {
        // Due to optimization need additional divisibility check on 3 and 5
        if ((is_prime[index]) && (index % 3 != 0) && (index % 5 != 0)) {
            primes.push_back(index);
        }
    }

    return primes;
}

bool is_prime(const uint64_t &num, const std::vector<uint32_t> &all_primes) {
    for (uint64_t prime:all_primes) {
        if (!(num % prime) && num != prime)
            return false;

        if (prime * prime > num)
            break;
    }
    return true;
}

bool korselt_criterion(uint64_t number) {
    std::vector<uint32_t> all_primes = atkin_sieve(static_cast<uint32_t>(sqrt(number)));

    bool composite = false, square_free = true;
    for (uint64_t prime:all_primes) {
        if (!(number % prime) && number != prime)
            composite = true;
        if (!(number % (prime * prime)))
            square_free = false;
    }

    if (!composite || !square_free)
        return false;

    std::vector<uint64_t> divisors;
    uint64_t second_divisor;
    for (uint64_t divisor = 2; divisor*divisor<=number;divisor++) {
        if (!(number % divisor)) {
            if (is_prime(divisor, all_primes))
                divisors.push_back(divisor);
            
            if (divisor * divisor != number) {
                second_divisor = number / divisor;
                if (is_prime(second_divisor, all_primes))
                    divisors.push_back(second_divisor);
            }
        }
    }

    bool criterion = true;
    for (uint64_t divisor:divisors) {
        if ((number - 1) % (divisor - 1))
            criterion = false;
    }

    return criterion;
}