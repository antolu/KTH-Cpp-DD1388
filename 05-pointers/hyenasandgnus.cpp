bool LOG = true;

#include "hyenasandgnus.hpp"
#include "watermanager.hpp"
#include "gnu.hpp"

#define nrGnus 4
#define nrHyenas 3

std::unordered_map<std::thread::id, int> id_map;
int hyena_idx = 0;
std::mutex m;
watermanager wm;

std::mt19937_64 eng{std::random_device{}()};  
std::uniform_int_distribution<> sleep_dist{10, 100};
std::uniform_int_distribution<> iter_dist{1, 5};


auto id = []()->int {return id_map[std::this_thread::get_id()];};

void hyena()
{
    std::unique_lock<std::mutex> lk(m);
    id_map[std::this_thread::get_id()] = ++hyena_idx;
    lk.unlock();

    for (int i = 0; i < iter_dist(eng); i++)
    { // run a number of simulations
        // sleep for a while
        std::this_thread::sleep_for(std::chrono::milliseconds{sleep_dist(eng)});
        if (LOG)
            std::cout << "Hyena " << id() << " is thirsty." << std::endl;
        wm.hyenaEnters(); // see monitoring class below
        std::this_thread::sleep_for(std::chrono::milliseconds{sleep_dist(eng)});
                                  // drink water for a while i.e. sleep for a short while
        if (LOG)
            std::cout << "Hyena " << id() << " finished drinking and exits the watercave." << std::endl;
        wm.hyenaLeaves();
    }
}


int main(int argc, char const *argv[])
{
    std::vector<std::thread> threadvec;
    for (int i = 0; i < nrGnus; i++) {
        std::function<void(void)> threadjob = Gnu(i, iter_dist(eng));
        threadvec.push_back(std::thread(threadjob));
    }
    for (int i = 0; i < nrHyenas; i++)
        threadvec.push_back(std::thread(hyena));

    for (auto &thread: threadvec)
        thread.join();

    for (auto & it : id_map)
        std::cout << it.first << ": " << it.second << std::endl;

    return 0;
}
