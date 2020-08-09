/*
 * The requires clause is introduced in C++20 along with concepts.
 */

#include <type_traits>
#include <string>

template<typename N>
concept Numeric = requires(N n) {
    requires std::is_integral_v<N> || std::is_floating_point_v<N>;
};

template<Numeric N>
void numeric_only_0(N n)
{
}

// The concept can be directly applied to a function with the requires clause.

template<typename T>
requires std::is_integral_v<T> || std::is_floating_point_v<T>
void numeric_only_1(T n)
{
}

int main()
{
    numeric_only_0(1);
    numeric_only_1(3.14);
    // numeric_only_0(std::string{});   // error
}