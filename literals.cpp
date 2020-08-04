/*
 * User-defined literals are introduced in C++11.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <chrono>
#include <complex>

// system-defined literals
// equivalent to using namespace std::literals;
using namespace std::literals::string_literals;         // C++14
using namespace std::literals::string_view_literals;    // C++17
using namespace std::literals::chrono_literals;         // C++14
// std::chrono::year::operator""y                       // C++20
// std::chrono::day::operator""d                        // C++20
using namespace std::literals::complex_literals;        // C++14

// user-defined literals
// must precede with underscore _
constexpr unsigned long long operator""_llu(unsigned long long n)
{
    return n;
}

int main()
{
    std::string s("String Literal"s);
    std::string_view sv("String View Literal"sv);
    auto seconds = 60s;
    auto imaginary = 1i;
}