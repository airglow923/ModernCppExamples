#include <type_traits>
#include <concepts>
#include <memory>
#include <iterator>

template<typename A, typename B = A>
concept Allocator = requires(A a, B b) {
    typename A::value_type;

    // Erasable
    {std::allocator_traits<A>::destroy(
        a, std::declval(
            std::allocator_traits<A>::pointer))} -> std::same_as<void>;

    {*std::declval(std::allocator_traits<A>::pointer)} ->
        std::same_as<typename A::value_type&>;
    {*std::declval(std::allocator_traits<A>::const_pointer)} ->
        std::same_as<const typename A::value_type&>;

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
concept Container = requires(C a, C b) {
    typename C::value_type;
    typename C::reference;
    typename C::const_refernce;
    typename C::iterator;
    typename C::const_iterater;
    typename C::difference_type;
    typename C::size_type;

    requires LegacyForwardIterator<typename C::iterator>;
    requires LegacyForwardIterator<typename C::const_iterator>;

    requires std::same_as<
        typename C::difference_type,
        typename std::iterator_traits<typename C::iterator>::difference_type>;

    requires std::same_as<
        typename C::difference_type,
        typename std::iterator_traits<typename C::const_iterator>::difference_type>;

    {C()} -> std::same_as<C>;
    {C(a)} -> std::same_as<C>;
    {C(std::move(a))} -> std::same_as<C>;
    {a = b} -> std::same_as<C&>;
    {a = std::move(b)} -> std::same_as<C&>;
    {a.~C()} -> std::same_as<void>;
    
    // will be fixed in the future
    {a.begin()} ->
        std::same_as<typename C::iterator> ||
        std::same_as<typename C::const_iterator>;
};

int main()
{
}