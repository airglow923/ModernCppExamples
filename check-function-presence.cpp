#include <ios>
#include <iostream>
#include <type_traits>
#include <functional>

// can specify return type and arguments, meaning it can pinpoint a specific
// overloading functions

#define HAS_FUNCTION_RET(name) \
    template<typename T, typename Ret = void, typename... Args> \
    class has_function_ret##name { \
        template<typename U, U> \
        struct TypeCheck; \
\
        using Yes = char; \
        using No = long; \
\
        template<typename U> \
        struct function_holder { \
            using pfunc = Ret (U::*)(Args...); \
        }; \
\
        template<typename U> \
        static constexpr Yes& has_function_ret_impl( \
            TypeCheck<typename function_holder<U>::pfunc, &U::name>*); \
\
        template<typename U> \
        static constexpr No& has_function_ret_impl(...); \
\
    public: \
        static constexpr bool value = \
            (sizeof(has_function_ret_impl<T>(0)) == sizeof(Yes)); \
    }; \
\
    template<typename T, typename Ret = void, typename... Args> \
    inline constexpr bool has_function_ret_ ## name ## _v = \
        has_function_ret##name<T, Ret, Args...>::value;

// detect the presence of member function
// error occurs at compile-time when the type of arguments do not match

template<typename T>
struct sfinae_true : std::true_type{};

#define HAS_FUNCTION(name) \
    template<typename T, typename... Args> \
    static constexpr auto check_function_##name(int) -> \
        sfinae_true<decltype(std::declval<T>().name(std::declval<Args>()...))>; \
\
    template<typename T> \
    static constexpr auto check_function_##name(long) -> std::false_type; \
\
    template<typename T, typename... Args> \
    struct has_function_##name : decltype(check_function_##name<T, Args...>(0)){}; \
\
    template<typename T, typename... Args> \
    inline constexpr bool has_function_ ## name ## _v = has_function_##name<T, Args...>::value;

HAS_FUNCTION(func)
HAS_FUNCTION_RET(func)

struct Sample {
    void func(int) {}
};

struct Foo {
    int func() {}
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << has_function_ret_func_v<Sample, int> << '\n'
              << has_function_ret_func_v<Foo, int> << '\n'
              << has_function_ret_func_v<Sample, void, int> << '\n'
              << has_function_ret_func_v<Foo, void, int>;
}