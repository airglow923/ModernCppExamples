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

// until C++03
template <typename I,
          typename = typename std::enable_if<std::is_same<I, int>::value>::type>
void sfinae_03(I i) {
  std::cout << i << '\n';
}

// since C++11
template <typename I>
void sfinae_11(I i) {
  static_assert(std::is_same<I, int>::value, "");
  std::cout << i << '\n';
}

// since C++14
// either way is fine
//    - use typename with std::enable_if_t
//    - static_assert
template <typename I, typename = std::enable_if_t<std::is_same<I, int>::value>>
void sfinae_14(I i) {
  static_assert(std::is_same<I, int>::value, "");
  std::cout << i << '\n';
}

// since C++17
// either way is fine
//    - use typename with std::enable_if_t and std::is_same_v
//    - static_assert without message
template <typename I, typename = std::enable_if_t<std::is_same_v<I, int>>>
void sfinae_17(I i) {
  // message is no longer mandatory
  static_assert(std::is_same_v<I, int>);
  std::cout << i << '\n';
}

// since C++20
#if defined(__cpp_lib_concepts)
template <std::integral I>
void sfinae_20(I i) {
  std::cout << i << '\n';
}
#endif

auto main() -> int {}
