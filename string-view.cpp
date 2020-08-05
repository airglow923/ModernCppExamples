/*
 * std::string_view is a library introduced in C++17.
 * 
 * It is an immutable view of a sequence of characters created at compile-time.
 * 
 * string_view can accept various types of strings such as
 *      - string by value
 *      - string by reference
 *      - null-terminated string
 *      - user-defined string
 */

#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>

std::string concat_string(std::string_view lhs, std::string_view rhs)
{
    std::string s;
    s.resize(lhs.length() + rhs.length());
    std::copy(lhs.begin(), lhs.end(), s.begin());
    std::copy(rhs.begin(), rhs.end(), s.begin() + lhs.size());
    return s;
}

int main()
{
    std::cout << concat_string("henlo ", "shibe") << '\n';
}