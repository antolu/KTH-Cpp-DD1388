#ifndef WATERMANAGER_HPP
#define WATERMANAGER_HPP

#include <iostream>
#include <memory>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <chrono>
#include <random>
#include <unordered_map>

class watermanager {
    std::condition_variable cv;
    std::mutex m;
    std::atomic<int> gnusInside;
    std::atomic<int> hyenasInside;
    bool b_log = false;

    public:
        void hyenaEnters();
        void hyenaLeaves();
        void gnuEnters();
        void gnuLeaves();
};


#endif