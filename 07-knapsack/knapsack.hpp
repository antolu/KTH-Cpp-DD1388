#ifndef DD1388_KNAPSACK_HPP
#define DD1388_KNAPSACK_HPP

#include <iostream>
#include <vector>
#include <map>

struct Gold;

/**
 * Represents a knapsack in this assignment. Keeps track of the number of gold bars, as well
 * the quantities of each weight, the value of the knapsack, and the weight (current/max).
 */
class Knapsack
{
    std::map<const Gold, int> contents;
    int max_weight = 0;
    int current_weight = 0;
    int current_value = 0;

public:
    /**
     * Default constructor. Should not be used as `max_weight` is initialised to 0.
     */
    Knapsack();

    /**
     * Destructor. Not used.
     */
    ~Knapsack();

    /**
     * Constructor, with max weight initialisation.
     * 
     * @param max_weight The maximum weight of this knapsack.
     */
    Knapsack(int max_weight);

    /**
     * Copy constructor.
     * 
     * @param other The knapsack to copy.
     */
    Knapsack(const Knapsack &other);

    /**
     * Assignment operator. 
     * 
     * @param other The knapsack whose contents to copy here.
     * 
     * @return A reference to `this`.
     */
    Knapsack &operator=(const Knapsack &other);

    /**
     * Adds gold to the knapsack if the weight of the gold fits into the bag.
     * 
     * @param The piece of gold to be added to the knapsack.
     * @return Whether the addition was successful (if the gold fit).
     */
    bool add_gold(const Gold gold);

    /**
     * Determines whether `gold` can fit into the knapsack.
     * 
     * @param gold The gold bar whose size is queried for availability.
     * 
     * @return True if the `gold` bar fits into the knapsack, else false.
     */
    bool can_fit(const Gold &gold) const;

    /**
     * Sets the weight capacity of the knapsack to `weight`.
     *
     * @param weight Sets the weight capacity to `weight`.
     */
    void set_max_weight(int weight);

    /**
     * Returns the current value of all the gold in the knapsack.
     * 
     * @return The total value of the knapsack.
     */
    int get_value() const;

    /**
     * Returns the current weight of the backpack.
     * 
     * @return The current weight of the knapsack.
     */
    int get_weight() const;

    /**
     * Calculates the load factor of the bag, i.e. current weight / max weight.
     *
     * @return The calculated load factor current / max weight.
     */
    double get_load_factor() const;

    /**
     * Returns the weight available in the knapsack.
     * 
     * @return The space available in the knapsack.
     */
    int get_free_weight() const;

    friend std::ostream &operator<<(std::ostream &ostream, const Knapsack &knapsack);
};

/**
 * Operator overload. Determines which is bigger based on weighted
 * value against load factor.
 *
 * @param lhs The first knapsack.
 * @param rhs The second knapsack.
 * @return Whether `lhs` is less valuable than `rhs`.
 */
bool operator<(const Knapsack & lhs, const Knapsack & rhs);

#endif