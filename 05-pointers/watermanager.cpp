#include "watermanager.hpp"

extern bool LOG;

void watermanager::hyenaEnters()
{
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [this] { return gnusInside == 0; });

    hyenasInside += 1;

    if (LOG)
        std::cout << "A hyena enters \t # hyenas: " << hyenasInside << "\t # gnus: " << gnusInside << std::endl;

    lk.unlock();
}

void watermanager::hyenaLeaves()
{
    std::unique_lock<std::mutex> lk(m);

    hyenasInside -= 1;
    if (LOG)
        std::cout << "A hyena leaves \t # hyenas: " << hyenasInside << "\t # gnus: " << gnusInside << std::endl;
    lk.unlock();

    cv.notify_all();
}

void watermanager::gnuEnters()
{
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, [this] { return hyenasInside == 0; });

    gnusInside += 1;
    if (LOG)
        std::cout << "A gnu enters \t # hyenas: " << hyenasInside << "\t # gnus: " << gnusInside << std::endl;

    lk.unlock();
}
void watermanager::gnuLeaves()
{
    std::unique_lock<std::mutex> lk(m);

    gnusInside -= 1;
    if (LOG)
        std::cout << "A gnu leaves \t # hyenas: " << hyenasInside << "\t # gnus: " << gnusInside << std::endl;
    lk.unlock();

    cv.notify_all();
}