/*
 * std::any is a feature introduced in C++17.
 * 
 * It is a type-safe class used to store any types in replacement of a unsafe
 * void pointer (void*).
 */

#include <iostream>
#include <any>

int main()
{
    std::any val1{65};
    std::any val2{'A'};

    std::cout << std::any_cast<int>(val1) << '\n'
              << std::any_cast<char>(val2) << '\n';
}