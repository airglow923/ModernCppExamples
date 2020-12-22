/*
 * SFINAE - Substitution Failure Is Not An Error
 *
 * is a term referring to a compiler-time type checking using substitution
 * during compilation.
 */

#include <iostream>
#include <type_traits>

// C++20 feature
#if defined(__cpp_lib_concepts)
#include <concepts>
#endif

// check whether a parameter type is int

/********************************* until C++03 ********************************/
template <typename I,
          typename = typename std::enable_if<std::is_same<I, int>::value>::type>
void sfinae_03(I i) {
  std::cout << i << '\n';
}

// or use return type

// trailing return type was introduced in C++11
template <typename I>
typename std::enable_if<std::is_same<I, int>::value>::type sfinae_03_r(I i) {
  std::cout << i << '\n';
}

/********************************* since C++11 ********************************/
// either way is fine
//
// Note that SFINAE and static_assesrt are evaluated at different timings.
// SFINAE is checked during overload resolution while static_assert checks type
// after overload resolution.
//
// Simply put, SFINAE checks the signature of a function whereas static_assert
// checks assertion inside implementation.

template <typename I>
auto sfinae_11(I i) ->
    typename std::enable_if<std::is_same<I, int>::value>::type {
  std::cout << i << '\n';
}

template <typename I>
auto sfinae_11_sa(I i) -> void {
  static_assert(std::is_same<I, int>::value, "");
  std::cout << i << '\n';
}

/********************************* since C++14 ********************************/
// either way is fine
//    - use typename with std::enable_if_t
//    - static_assert

template <typename I>
auto sfinae_14(I i) -> std::enable_if_t<std::is_same<I, int>::value> {
  std::cout << i << '\n';
}

template <typename I>
auto sfinae_14_sa(I i) -> void {
  static_assert(std::is_same<I, int>::value, "");
  std::cout << i << '\n';
}

/********************************* since C++17 ********************************/
// either way is fine
//    - use typename with std::enable_if_t and std::is_same_v
//    - static_assert without message

template <typename I>
auto sfinae_17(I i) -> std::enable_if_t<std::is_same_v<I, int>> {
  // message is no longer mandatory
  static_assert(std::is_same_v<I, int>);
  std::cout << i << '\n';
}

template <typename I>
auto sfinae_17_sa(I i) -> void {
  // message is no longer mandatory
  static_assert(std::is_same_v<I, int>);
  std::cout << i << '\n';
}

/********************************* since C++20 ********************************/
#if defined(__cpp_lib_concepts)
template <std::integral I>
void sfinae_20(I i) {
  std::cout << i << '\n';
}
#endif

auto main() -> int {}
