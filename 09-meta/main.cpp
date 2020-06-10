#include "algorithms.hpp"
#include <iostream>

#include "gtest/gtest.h"

TEST(sieve, test1) {
    std::vector<int> primes = find_primes(100);

    std::cout << primes << std::endl;
}

TEST(hardcoded_primes, test1) {
    std::string primes_100 = "std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}";
    EXPECT_EQ(hard_coded_primes(), primes_100);
    std::cout << hard_coded_primes() << std::endl;
}

TEST(factorial, test1) {
    std::cout << Factorial<5>::nr << std::endl;
}

TEST(meta_primes, test1) {
    auto bool_to_string = [](bool b)->std::string { return b ? "true" : "false"; };
    std::cout << bool_to_string(is_prime<5>::prim) << std::endl;
}

TEST(constexpr_primes, test1) {
    constexpr int N = 100;

    constexpr auto a = find_constexpr_primes<N>();
    for (int i = 0; i < N; i++)
        if (a.arr[i] != 0)
            std::cout << a.arr[i]  << " ";
    std::cout << std::endl;
}

TEST(ndim_matrix, test1) {
    nDimMatrix<3> n(9);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
