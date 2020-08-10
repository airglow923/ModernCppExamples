#include <type_traits>
#include <concepts>
#include <memory>
#include <iterator>

template<typename A, typename B = A>
concept Allocator = requires(A a, B b) {
    typename A::value_type;

    {*std::declval(std::allocator_traits<A>::pointer)} ->
        std::same_as<typename A::value_type&>;
    {*std::declval(std::allocator_traits<A>::const_pointer)} ->
        std::same_as<const typename A::value_type&>;
    {std::declval(std::allocator_traits<A>::pointer)->()} ->
        *std::declval(std::allocator_traits<A>::pointer);

    requires std::is_convertible_v<
        typename std::allocator_traits<A>::void_pointer,
        typename std::allocator_traits<A>::pointer>;

    requires std::is_convertible_v<
        typename std::allocator_traits<A>::void_pointer,
        typename std::allocator_traits<A>::const_pointer>;

    {std::pointer_traits<
        typename std::allocator_traits<A>::pointer>::pointer_to(
            *std::declval(std::allocator_traits<A>::pointer))} ->
        std::same_as<typename std::allocator_traits<A>::pointer>;

    {a.allocate()} -> std::same_as<typename std::allocator_traits<A>::pointer>;
    {a.deallocate()} -> std::same_as<void>;

    {a == b} -> std::same_as<bool>;
    {a != b} -> std::same_as<bool>;

    requires std::is_nothrow_copy_constructible_v<A>;
    requires std::is_nothrow_copy_assignable_v<A>;

    {typename A::rebind_traitsc<B>(a)} -> std::same_as<B>;   
    {typename A::rebind_traitsc<A>(a)} -> std::same_as<A>;
    
    requires std::is_nothrow_move_constructible_v<A>;
    requires std::is_nothrow_move_assignable_v<A>;
    requires A(std::move(b)) == A(b);
};

template<typename S>
concept Sequence = requires(S s) {
    typename S::value_type;
    typename S::iterator_type;

    {std::begin(s)} -> std::same_as<typename S::iterator_type>;
    {std::end(s)} -> std::same_as<typename S::iterator_type>;

    requires std::same_as<
        typename S::value_type,
        typename std::iterator_traits<typename S::iterator_type>::value_type>;
    requires std::input_iterator<typename S::iterator_type>;
};

template<typename C>
concept Container = requires(C c) {
    typename C::value_type;
};

int main()
{
}