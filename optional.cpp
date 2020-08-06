/*
 * std::optional is a feature introduced in C++17.
 * 
 * It contains an optional value, meaning that it handles a situation when
 * the object is not assigned to any value.
 */

#include <ios>
#include <iostream>
#include <optional>
#include <string>

namespace hyundeok {
    template<typename T>
    struct is_numeric
        : std::integral_constant<
            bool, std::is_integral_v<T> || std::is_floating_point_v<T>> {};

    template<typename T>
    inline constexpr bool is_numeric_v = is_numeric<T>::value;
}

template<typename T>
constexpr std::optional<double> convert_to_double(T val)
{
    using namespace hyundeok;

    if constexpr (is_numeric_v<T>)
        return std::optional<double>{val};
    else
        return std::optional<double>{};
}

int main()
{
    std::cout << std::boolalpha
              << convert_to_double(1).has_value() << '\n'
              << convert_to_double(std::string{"string"}).has_value() << '\n';
}