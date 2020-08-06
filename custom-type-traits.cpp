/*
 * type_traits is a header introduced in C++11.
 * 
 * It is used for type-checking and type modification.
 */

#include <iostream>
#include <type_traits>

namespace hyundeok {
    template<typename T>
    struct is_numeric
        : std::integral_constant<
            bool, std::is_integral_v<T> || std::is_floating_point_v<T>> {};

    template<typename T>
    inline constexpr bool is_numeric_v = is_numeric<T>::value;
}

int main()
{
    using namespace hyundeok;

    if (is_numeric_v<int>)
        std::cout << "int is numeric\n";
    
    if (is_numeric_v<double>)
        std::cout << "double is numeric\n";
}