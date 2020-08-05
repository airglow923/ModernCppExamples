#include <iostream>
#include <regex>
#include <string>

int main()
{
    std::string input{"the quick brown fox jumps over the lazy dog"};
    std::regex pattern{R"((\w+))"};

    for (std::sregex_iterator p(input.begin(), input.end(), pattern);
            p != std::sregex_iterator{}; ++p)
        std::cout << (*p)[1] << '\n';
}