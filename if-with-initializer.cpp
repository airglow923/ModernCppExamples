/*
 * If statements with initializer are introduced in C++17.
 */

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v;

    if (auto size = v.size(); size == 0)
        std::cout << "Empty\n";
    else
        std::cout << "Not empty\n";
}