#include <functional>
#include <set>

bool FANCY_PRINT= false;

#include "gold.hpp"
#include "algorithms.hpp"

#include "gtest/gtest.h"

std::vector<Gold> get_gold_bars() {
    std::vector<Gold> weight_and_values = {
            Gold(16, 24),
            Gold(19, 29),
            Gold(15, 23),
            Gold(14, 22),
            Gold(13, 21),
            Gold(17, 28),
    };
    std::sort(weight_and_values.begin(), weight_and_values.end());

    return weight_and_values;
}


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
    std::vector<Gold> weight_and_values = get_gold_bars();

    for (auto it = weight_and_values.rbegin(); it != weight_and_values.rend(); it++)
        std::cout << *it << std::endl;

    std::cout << greedytake(weight_and_values.rbegin(), weight_and_values.rend(), 32) << std::endl;
}

TEST(greedy_solution_2, 1)
{
    std::vector<Gold> weight_and_values = get_gold_bars();

    auto densitycompare = [](Gold g1, Gold g2) -> bool {
        return g1.density > g2.density;
    };

    std::cout << std::endl;

    std::set<Gold, std::function<bool(Gold, Gold)>> valuedensities(weight_and_values.begin(), weight_and_values.end(), densitycompare);

    for (auto gold : valuedensities)
        std::cout << gold << std::endl;
    std::cout << greedytake(valuedensities.begin(), valuedensities.end(), 32) << std::endl;
}

TEST(greedy_comparison, 1) {
    std::vector<Gold> weight_and_values = get_gold_bars();

    auto densitycompare = [](Gold g1, Gold g2) -> bool {
        return g1.density > g2.density;
    };

    std::set<Gold, std::function<bool(Gold, Gold)>> valuedensities(weight_and_values.begin(), weight_and_values.end(), densitycompare);

    for (int i = 0; i < 100; i++) {
        Knapsack greedy_1 = greedytake(weight_and_values.rbegin(), weight_and_values.rend(), i);
        Knapsack greedy_2 = greedytake(valuedensities.begin(), valuedensities.end(), i);

        if (greedy_2.get_value() > greedy_1.get_value()) {
            std::cout << "Greedy algorithm 2 is better than 1 at knapsacksize " << i << "." << std::endl;
            std::cout << "Greedy 2: " << greedy_2 << std::endl;
            std::cout << "Greedy 1: " << greedy_1 << std::endl;
        }
    }
}

TEST(greedy1_vs_dynamic, 1) {
    std::vector<Gold> weight_and_values = get_gold_bars();

    int max_weight = 100;

    std::vector<Knapsack> memory;
    Knapsack dymanic = dynamictake(weight_and_values.begin(), weight_and_values.end(), max_weight, memory);

    std::vector<Knapsack> greedy_matches;
    int count = 0;
    for (int knapsacksize = weight_and_values[0].weight; knapsacksize < max_weight; knapsacksize++) {
        Knapsack greedy = greedytake(weight_and_values.rbegin(), weight_and_values.rend(), knapsacksize);
        if (greedy == memory[knapsacksize]) {
            greedy_matches.push_back(greedy);
            if(++count >= 5)
                break;
        }
    }

    std::cout << "The following knapsacks have the same solution, whether greedy1 or dynamically programmed" << std::endl;
    for (Knapsack knapsack : greedy_matches) {
        std::cout << knapsack << std::endl;
    }
}
TEST(greedy2_vs_dynamic, 1) {
    std::vector<Gold> weight_and_values = get_gold_bars();

    auto densitycompare = [](Gold g1, Gold g2) -> bool {
        return g1.density > g2.density;
    };

    std::set<Gold, std::function<bool(Gold, Gold)>> valuedensities(weight_and_values.begin(), weight_and_values.end(), densitycompare);

    int max_weight = 100;

    std::vector<Knapsack> memory;
    Knapsack dymanic = dynamictake(valuedensities.begin(), valuedensities.end(), max_weight, memory);

    std::vector<Knapsack> greedy_matches;
    int count = 0;
    for (int knapsacksize = weight_and_values[0].weight; knapsacksize < max_weight; knapsacksize++) {
        Knapsack greedy = greedytake(valuedensities.rbegin(), valuedensities.rend(), knapsacksize);
        if (greedy == memory[knapsacksize]) {
            greedy_matches.push_back(greedy);
            if(++count > 5)
                break;
        }
    }

    std::cout << "The following knapsacks have the same solution, whether greedy2 or dynamically programmed" << std::endl;
    for (Knapsack knapsack : greedy_matches) {
        std::cout << knapsack << std::endl;
    }
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
