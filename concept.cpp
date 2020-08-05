/*
 * Concept is a feature introduced since C++20.
 */

#include <iostream>
#include <concepts>
#include <ranges>
#include <iterator>
#include <initializer_list>

template<typename T>
using value_type_v = typename T::value_type;

template<typename T>
using iterator_type_v = typename T::iterator;

template<typename S>
concept Sequence = requires(S a) {
    typename value_type_v<S>;
    typename iterator_type_v<S>;

    {begin(a)} -> std::same_as<iterator_type_v<S>>;
    {end(a)} -> std::same_as<iterator_type_v<S>>;

    requires std::same_as<
        value_type_v<S>,
        value_type_v<std::iterator_traits<iterator_type_v<S>>>>;
    requires std::input_iterator<iterator_type_v<S>>;
};

template<typename T, typename U = T>
concept Arithmetic = requires(T a, U b) {
    {a + b} -> std::same_as<T>;
    {a - b} -> std::same_as<T>;
    {a * b} -> std::same_as<T>;
    {a / b} -> std::same_as<T>;
};

template<Sequence Seq, Arithmetic<value_type_v<Seq>> Num>
Num sum(Seq s, Num v)
{
    for (const auto& x : s)
        v += x;
    return v;
}

template<Arithmetic Num>
Num sum(const std::initializer_list<Num>& il, Num v)
{
    for (const auto& x : il)
        v += x;
    return v;
}

int main()
{
    std::cout << sum({1,2,3,4}, 0);
}