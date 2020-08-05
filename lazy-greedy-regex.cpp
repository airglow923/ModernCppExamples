/*
 * std::regex is a library introduced in C++11.
 * 
 * Lazy in regex means to capture as less characters as possible.
 * Greedy in regex means to capture as much characters as possible.
 */

#include <iostream>
#include <regex>

int main()
{
    std::string target{"<em>Hello World</em>"};
    std::regex lazy{R"(<.+?>)"};    // raw string literal since C++11
    std::regex greedy{R"(<.+>)"};
    std::smatch match;

    std::regex_search(target, match, lazy);
    std::cout << match[0] << '\n';  // <em>
    
    std::regex_search(target, match, greedy);
    std::cout << match[0] << '\n';  // <em>Hello World</em>
}