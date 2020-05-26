#include "gnu.hpp"
#include "watermanager.hpp"

extern bool LOG;
extern watermanager wm;

Gnu::Gnu(int id, int iters) {this->id = id; this->iters = iters;}

void Gnu::operator() () {

    for (int i = 0; i < iters; i++)
    { // run a number of simulations
        // sleep for a while
        std::this_thread::sleep_for(std::chrono::milliseconds{sleep_dist(eng)});
        if (LOG)
            std::cout << "Gnu " << id << " is thirsty." << std::endl;
        wm.gnuEnters(); // see monitoring class below
        std::this_thread::sleep_for(std::chrono::milliseconds{sleep_dist(eng)});
                                  // drink water for a while i.e. sleep for a short while
        if (LOG)
            std::cout << "Gnu " << id << " finished drinking and exits the watercave." << std::endl;
        wm.gnuLeaves();
    }
}

std::ostream & operator<<(std::ostream & os, const Gnu & g) {
    os << "Gnu " << g.id;
    return os;
}