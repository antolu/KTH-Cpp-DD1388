#ifndef DD1388_GOLD_HPP
#define DD1388_GOLD_HPP

#include <iostream>
#include "knapsack.hpp"

/**
 * Class to replace std::pair<int, int> for a gold bar for this assigmnent.
 * Also contains operator overloads to be compatible with std::map, and printable
 * object using std::ostream overload.
 */
struct Gold {
    int weight = 0;
    int value = 0;
    double density = 0;

    Gold() {};

    /**
     * Constructor that should be used. Calculates the material density as well.
     *
     * @param weight The weight of the gold bar.
     * @param value The value of the gold bar.
     */
    Gold(int weight, int value) {
        this->weight = weight;
        this->value = value;
        density = (double) value / weight;
    }

    /**
     * Copy constructor.
     * @param other The gold bar to copy.
     */
    Gold(const Gold & other) {
        weight = other.weight;
        value = other.value;
        density = other.density;
    }
};

/**
 * Operator overload. Compares Gold bars based on their weight.
 *
 * @param lhs  Left hand side object.
 * @param rhs Right hand side object.
 * @return Whether `lhs` weights less than `rhs`.
 */
inline bool operator<(const Gold & lhs, const Gold & rhs) {
    return lhs.weight < rhs.weight;
}

/**
 * std::ostream overload to print gold bar information
 * 
 * @param ostream The ostream to pass information to.
 * @param gold The gold object to print.
 * @return A std::ostream with information about the `gold` object. 
 */
inline std::ostream& operator<<(std::ostream & ostream, const Gold & gold) {
    ostream << "Weight: " << gold.weight << ", value: " << gold.value << ", density: " << gold.density << " value/kg";

    return ostream;
}

#endif