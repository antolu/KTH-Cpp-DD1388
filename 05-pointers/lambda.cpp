#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

void print(std::vector<int> v) {
    for (auto x : v) { std::cout << x << " ";};
}

int main(int argc, char const *argv[])
{
    std::vector<int> v = {1, 3, 4, 5, 6, 7, 8, 9};
    // printing v
    std::cout << "Original algorithm: " << std::endl;
    std::cout << "vector v:" << std::endl;
    print(v);
    std::cout << std::endl;

    std::cout << "Odd lambda: " << std::endl;
    // auto lambda = [](auto v) {for (auto x : v) if (x % 2 != 0) std::cout << x << " ";};
    auto lambda = [](auto i) {if (i % 2) std::cout << i << " ";};
    std::for_each(v.cbegin(), v.cend(), lambda);
    std::cout << std::endl;

    std::cout << "Multiply by 2" << std::endl;
    std::for_each(v.begin(), v.end(), [](int & i) {if (i % 2) i *= 2;});
    print(v);
    std::cout << std::endl;

    std::cout << "Add vector length" << std::endl;
    std::for_each(v.begin(), v.end(), [&v](int & i) {i += v.size();});
    print(v);
    std::cout << std::endl;

    std::cout << "Change first element to -1" << std::endl;
    auto lambda_mutate = [&v] () {v[0] = -1;};
    lambda_mutate();
    print(v);


    return 0;
}
