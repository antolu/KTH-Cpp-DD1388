#include <iostream>
#include <string>

#include "hello.h"

void hello(const char *name, int count)
{
    if (count != 0)
    {
        std::cout << "Hello,";
        for (int i = 0; i < count; i++)
        {
            std::cout << " " << name;
        }
        std::cout << "!" << "\n";
    }
}

std::pair<const char *, int> parse_args(int argc, char *argv[])
{
    if (argc < 2)
    {
        return std::make_pair("world", 1);
    }
    else if (argc > 3)
    {
        std::cerr << "error: Too many arguments!" << "\n";
        return std::make_pair("error: Too many arguments!", -1);
    }
    else
    {
        int count = 0;
        try
        {
            if (argc > 2)
                count = std::stoi(argv[2]);
            else
                count = 1;
        }
        catch (const std::exception &e)
        {
            std::cerr << "error: 2nd argument must be an integral greater than zero!" << '\n';
        }
        return std::make_pair(argv[1], count);
    }
}
