//
// Created by anton on 2/23/20.
//

#ifndef META_ALGORITHMS_H
#define META_ALGORITHMS_H

#include <iostream>
#include <vector>
#include <sstream>

/**
 * Uses Eratosthenes sieve to find prime numbers up to `N`.
 * 
 * @param N The max number to search a prime number for.
 * 
 * @return A vector containing all the found prime numbers. 
 */
std::vector<int> find_primes(int N);

/**
 * Returns a string of prime numbers in the format
 * std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 29, 23, 29}
 * @return
 */
std::string hard_coded_primes();

/**
 * Operator overload for output streams.
 * @tparam T Any type with operator<< overload implemented.
 * @param ostream The stream to populate.
 * @param vector A vector containing elements of type T.
 * @return The populated ostream.
 */
template <class T>
std::ostream & operator<<(std::ostream & ostream, const std::vector<T> & vector) {
    for (auto obj : vector)
        ostream << obj << " ";
    return ostream;
}

template <int x>
struct Factorial {
    static const int nr = x * Factorial<x - 1>::nr;
};

template<> 
struct Factorial<1>
{
    static const int nr = 1;
};

template <int p, int i>
struct check_if_prime {
    enum { prim = (p == 2) ||  ((p%i) && check_if_prime<(i > 2 ? p : 0), i - 1>::prim) };
};

template <>
struct check_if_prime<0, 0> { enum {prim = 1};} ;

template<>
struct check_if_prime<0, 1> { enum {prim = 1}; };

template <unsigned int X>
struct is_prime {
    enum {prim = check_if_prime<X, X - 1>::prim };
};

template <int i>
struct D {
    D(void*);
    operator int();
};

inline constexpr bool is_prime_constexpr(size_t number, size_t c) {
    return (c * c > number ) ? true : (number % c == 0) ? false : is_prime_constexpr(number, c+1);
}

inline constexpr bool is_prime_func(size_t number) {
    return (number <= 1) ? false : is_prime_constexpr(number, 2);
}

template <int N>
struct find_constexpr_primes {
    constexpr find_constexpr_primes() : arr() {
        int counter = 0;
        for (auto i = 0; i != N; i++) {
            if (is_prime_func(i))
                arr[counter++] = i;
        }
        for (int j = counter; j < N; j++)
            arr[j] = 0;
    }
    int arr[N];
};

template <int x>
class nDimMatrix : std::vector<double> {
    public:
    constexpr nDimMatrix(int d)  {

    }
};

template<>
class nDimMatrix<1>  {
public:
    int x;
    nDimMatrix() : x(0) {}

};


#endif //META_ALGORITHMS_H
