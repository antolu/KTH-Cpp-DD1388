#ifndef DD1388_ALGORITHMS_HPP
#define DD1388_ALGORITHMS_HPP

#include <map>
#include <string>
#include <sstream>

#include "knapsack.hpp"

/**
 * Generic function, takes two set iterators and a knapsack weight to return a string with information
 * on how much gold was taken using a greedy programming algorithm. 
 * 
 * @param start Begin iterator to iterable containing std::pair with weights and values
 * @param end End iterator to iterable containing std::pair with weights and values
 * @param N The weight of the knapsack
 * 
 * @return A string with information on how much gold one took, how much it weighs,
 * and which kind of gold bars were taken
 */
template <typename S>
Knapsack greedytake(S start, S end, int N)
{
    /* Greedily add gold to the knapsack, starting from the most valuable pieces */
    Knapsack knapsack(N);
    for (S it = start; it != end; it++)
    {
        while (knapsack.add_gold(*it))
            continue;
    }

    return knapsack;
}


/**
 * Wrapper for the function with the same name below.
 */
template <class T>
Knapsack dynamictake(const T & begin, const T & end, const int & knapsacksize) {
    std::vector<Knapsack> memory;
    return dynamictake(begin, end, knapsacksize, memory);
}

/**
 * Generic function. Takes begin and end iterator of container and iterates over the knapsack sizes to
 * determine the most valuable knapsack configurations based on the contents of the passed container.
 * Also takes a memory vector as argument that is filled with the most optimal knapsack at weight `i`.
 *
 * @tparam T Any valid container that implements the iterator interface AND gives a pointer to a Gold
 * object (ie. no maps with std::pair in a for each loop).
 * @param begin Begin iterator to iterable containing Gold bars.
 * @param end End iterator to iterable containing Gold bars.
 * @param knapsacksize The knapsack size to find the most optimal configuration for.
 * @param memory A vector that will be filled with the most optimal knapsack configurations up to a
 * weight `knapsacksize`. This vector will be erased before usage.
 * @return The most optimal knapsack at weight `knapsacksize`.
 */
template <class T>
Knapsack dynamictake(const T & begin, const T & end, const int & knapsacksize, std::vector<Knapsack> &memory)
{
    /* Vector to store the highest accumulated value at weight i */
    int * values = new int[knapsacksize + 1];

    /* Initialise the vector to prevent segfaults */
    memory.clear();
    for (int i = 0; i <= knapsacksize; i++) {
        memory.push_back(Knapsack(i));
        values[i] = 0;
    }

    Gold optimal;
    for (int i = 1; i <= knapsacksize; i++) {
        optimal = Gold();
        for (auto it = begin; it != end; it++) {
            /* If gold bar weight greater than knapsack size, no possible action. */
            if (it->weight > i)
                continue;

            /* Get the current best knapsack at the weight - the new gold bar */
            Knapsack current_best = memory[i - it->weight];
            current_best.set_max_weight(i);

            if (current_best.can_fit(*it)) {
                /* If value + current best is greater than the accumulated value at the new weight + the current best new gold bar */
                int new_value = current_best.get_value() + it->value;
                int new_weight = current_best.get_weight() + it->weight;
                if (new_value >= values[new_weight] + optimal.value) {
                    optimal = *it;

                    /* Save new best accumulated weight */
                    values[new_weight] = new_value;
                    current_best.add_gold(optimal);
                    memory[i] = current_best;
                }
            }
        }
    }

    return memory[knapsacksize];
}

#endif