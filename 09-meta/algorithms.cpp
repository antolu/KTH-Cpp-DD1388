//
// Created by anton on 2/23/20.
//

#define N_PRIMES 100

#include "algorithms.hpp"

#include <string>
#include <sstream>

std::vector<int> find_primes(int N) {
    std::vector<int> primes;

    int * sieve = new int[N + 1];

    for (int i = 0; i < N + 1; i++)
        sieve[i] = true;

    for (int p = 2; p < N + 1; p++) {
        if (sieve[p]) {
            primes.push_back(p);
            for (int i = p; i < N + 1; i += p)
                sieve[i] = false;
        }
    }

    return primes;
}

std::string hard_coded_primes() {
    std::vector<int> primes = find_primes(N_PRIMES);

    std::stringstream ss;

    ss << "std::vector<int> primes = ";
    ss << "{";
    for (int i = 0; i < (int) primes.size(); i++) {
        ss << primes[i];
        if (i != (int) primes.size() - 1)
            ss << ", ";
    }
    ss << "}";

    return ss.str();
}

