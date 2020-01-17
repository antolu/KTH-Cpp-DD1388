#ifndef GNU_HPP
#define GNU_HPP

#include <thread>
#include <chrono>
#include <iostream>
#include <random>

class Gnu {
    int id = 0;
    int iters = 0;

    std::mt19937_64 eng{std::random_device{}()};  
    std::uniform_int_distribution<> sleep_dist{10, 100};

    public:
    Gnu(int id, int iters);
    void operator() ();
    friend std::ostream & operator<<(std::ostream & os, const Gnu & g);
};

#endif