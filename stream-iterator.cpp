#include <iostream>
#include <iterator>
#include <string>

int main()
{
    std::ostream_iterator<std::string> oi{std::cout};
    *oi = "Henlo ";
    ++oi;
    *oi = "Shibe";

    // Henlo Shibe printed to std::cout
}