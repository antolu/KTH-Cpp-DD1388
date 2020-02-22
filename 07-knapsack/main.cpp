#include <functional>
#include <set>

bool FANCY_PRINT= false;

#include "gold.hpp"
#include "algorithms.hpp"

#include "gtest/gtest.h"


TEST(print_map, 1)
{
    std::map<int, int> weight_and_values = {
        {16, 24},
        {19, 29},
        {15, 23},
        {14, 22},
        {13, 21},
        {17, 28},
    };

    for (auto it = weight_and_values.rbegin(); it != weight_and_values.rend(); it++)
        std::cout << "weight = " << (*it).first << ", value=" << (*it).second << std::endl;
}

TEST(greedy_solution_1, 1)
{
    std::vector<Gold> weight_and_values = {
        Gold(16, 24),
        Gold(19, 29),
        Gold(15, 23),
        Gold(14, 22),
        Gold(13, 21),
        Gold(17, 28),
    };

    std::sort(weight_and_values.begin(), weight_and_values.end());

    for (auto it = weight_and_values.rbegin(); it != weight_and_values.rend(); it++)
        std::cout << *it << std::endl;

    std::cout << greedytake(weight_and_values.rbegin(), weight_and_values.rend(), 32) << std::endl;
}

TEST(greedy_solution_1, 2)
{

    std::vector<Gold> weight_and_values = {
        Gold(16, 24),
        Gold(19, 29),
        Gold(15, 23),
        Gold(14, 22),
        Gold(13, 21),
        Gold(17, 28),
    };
    std::sort(weight_and_values.begin(), weight_and_values.end());

    auto densitycompare = [](Gold g1, Gold g2) -> bool {
        return g1.density > g2.density;
    };

    std::cout << std::endl;

    std::set<Gold, std::function<bool(Gold, Gold)>> valuedensities(weight_and_values.begin(), weight_and_values.end(), densitycompare);

    for (auto gold : valuedensities)
        std::cout << gold << std::endl;
    std::cout << greedytake(valuedensities.begin(), valuedensities.end(), 32) << std::endl;
}

TEST(dynamic_solution_1, 1) {
        std::vector<Gold> weight_and_values = {
        Gold(16, 24),
        Gold(19, 29),
        Gold(15, 23),
        Gold(14, 22),
        Gold(13, 21),
        Gold(17, 28),
    };

    std::sort(weight_and_values.begin(), weight_and_values.end());

    std::vector<Knapsack> memory;

    Knapsack dynamic = dynamictake(weight_and_values.rbegin(), weight_and_values.rend(), 50, memory);

    std::cout << dynamic << std::endl;

    for (auto knapsack : memory) {
        std::cout << " " << knapsack << std::endl;
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    // return 0;
}
