#include <cmath>
#include <map>

#include "knapsack.hpp"
#include "gold.hpp"

extern bool FANCY_PRINT;

Knapsack::Knapsack()
{
    max_weight = 0;
}

Knapsack::~Knapsack() {}

Knapsack::Knapsack(int max_weight)
{
    this->max_weight = max_weight;
}

Knapsack::Knapsack(const Knapsack & other) : Knapsack(other.max_weight) {    
    contents = other.contents;

    current_weight = other.current_weight;
    current_value = other.current_value;
}

Knapsack &Knapsack::operator=(const Knapsack &other)
{
    contents = other.contents;

    max_weight = other.max_weight;
    current_weight = other.current_weight;
    current_value = other.current_value;

    return *this;
}

bool Knapsack::add_gold(const Gold gold)
{
    if (can_fit(gold))
    {
        if (contents.count(gold) > 0)
            contents[gold]++;
        else
            contents[gold] = 1;

        current_weight += gold.weight;
        current_value += gold.value;

        return true;
    }
    else
        return false;
}

bool Knapsack::can_fit(const Gold & gold) const {
    return gold.weight <= max_weight - current_weight;
}

void Knapsack::set_max_weight(int weight) {
    max_weight = weight;
}

int Knapsack::get_value() const
{
    double value = 0.0;

    for (auto content : contents)
        value += content.first.value;

    return value;
}

int Knapsack::get_weight() const
{
    return current_weight;
}

int Knapsack::get_free_weight() const {
    return max_weight - current_weight;
}

double Knapsack::get_load_factor() const {
    return current_weight/max_weight;
}

std::ostream& operator<<(std::ostream & ostream, const Knapsack & knapsack) {
    if (FANCY_PRINT) {
        ostream << "Knapsack size = " << knapsack.max_weight << std::endl;

        int knapsack_value = knapsack.get_value();
        std::string whitespace(10 + std::ceil(std::log10(knapsack_value <= 0 ? 1 : knapsack_value)),
                               ' ');
        ostream << "Has value " << knapsack_value << std::endl;
        for (auto gold : knapsack.contents)
            ostream << whitespace << "\u02E7 " << gold.second << " * " << gold.first.value << std::endl;

        int knapsack_weight = knapsack.get_weight();
        whitespace = std::string(10 + std::ceil(std::log10(knapsack_weight <= 0 ? 1 : knapsack_weight)),
                                 ' ');
        ostream << "Has weight " << knapsack_weight << "/" << knapsack.max_weight << std::endl;
        for (auto gold : knapsack.contents)
            ostream << whitespace << "\u02E7 " << gold.second << " * " << gold.first.weight << std::endl;
    } else {
        ostream << "Size: " << knapsack.max_weight << ", value: " << knapsack.current_value;
        for (auto gold : knapsack.contents)
            ostream << ", " << gold.second << "*" << gold.first.weight << "@" << gold.first.value << "=" << gold.second * gold.first.value;
    }
    return ostream;
}

bool operator<(const Knapsack & lhs, const Knapsack & rhs) {
    double this_val = lhs.get_value();
    double other_val = rhs.get_value();

    return this_val * lhs.get_load_factor() < other_val * rhs.get_load_factor();
}