/*
 * std::regex is a library introduced in C++11.
 * 
 * Lazy in regex means to match the least number of characters.
 * Greedy in regex means to match the most number of characters.
 */

#include <iostream>
#include <regex>

int main()
{
    std::string target{"<em>Hello World</em>"};
    std::regex lazy{R"(<.+?>)"};
    std::regex greedy{R"(<.+>)"};
    std::smatch match;

    std::regex_search(target, match, lazy);
    std::cout << match[0] << '\n';  // <em>
    
    std::regex_search(target, match, greedy);
    std::cout << match[0] << '\n';  // <em>Hello World</em>
}