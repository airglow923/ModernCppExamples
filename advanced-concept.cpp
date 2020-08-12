#include <type_traits>
#include <concepts>
#include <memory>
#include <iterator>
#include <ranges>
#include <iostream>
#include <vector>

template<typename A, typename T>
concept is_allocator = requires(A a, A b, T t) {
    typename A::value_type;

    {std::allocator_traits<A>::destroy(a, &t)} -> std::same_as<void>;

    {*&t} -> std::same_as<T&>;

    {*std::declval<typename std::allocator_traits<A>::const_pointer>()} ->
        std::same_as<const T&>;

    requires std::same_as<decltype(static_cast<T*>(
            std::declval<typename std::allocator_traits<A>::void_pointer>())),
        T*>;

    requires std::same_as<decltype(
        static_cast<typename std::allocator_traits<A>::const_pointer>(
            std::declval<
                typename std::allocator_traits<A>::const_void_pointer>())),
        typename std::allocator_traits<A>::const_pointer>;

    {std::pointer_traits<T*>::pointer_to(*&t)} -> std::same_as<T*>;

    {a.allocate(
        std::declval<typename std::allocator_traits<A>::size_type>())} ->
        std::same_as<T*>;

    {a.deallocate(
        &t, std::declval<typename std::allocator_traits<A>::size_type>())} ->
        std::same_as<void>;

    {a == b} -> std::same_as<bool>;
    {a != b} -> std::same_as<bool>;

    requires std::is_nothrow_copy_constructible_v<A>;
    requires std::is_nothrow_copy_assignable_v<A>;
    requires std::is_nothrow_move_constructible_v<A>;
    requires std::is_nothrow_move_assignable_v<A>;
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

template<typename Type_, typename Alloc_>
concept is_erasable = requires(Type_ t, Alloc_ a) {
    {std::allocator_traits<Alloc_>::destroy(a, &t)} -> std::same_as<void>;
};

template<typename Type_, typename Alloc_>
concept is_move_insertable = requires(Type_ t, Alloc_ a) {
    {std::allocator_traits<Alloc_>::construct(a, &t, t)} -> std::same_as<void>;
};

template<typename Type_, typename Alloc_>
concept is_copy_insertable =
    is_move_insertable<Type_, Alloc_> &&
    requires (Type_ t, Alloc_ a) {
        {std::allocator_traits<Alloc_>::construct(a, &t, std::move(t))} ->
            std::same_as<void>;
    };

template<typename Iter, typename Container>
concept is_container_iterator =
    std::same_as<Iter, typename Container::iterator> ||
    std::same_as<Iter, typename Container::const_iterator>;

template<typename C, typename Type_, typename Alloc_>
concept is_container = requires(C a, C b, Type_ t, Alloc_ alloc) {
    typename C::value_type;
    typename C::reference;
    typename C::const_reference;
    typename C::iterator;
    typename C::const_iterator;
    typename C::difference_type;
    typename C::size_type;

    // Erasable type
    requires is_erasable<Type_, Alloc_>;

    requires std::default_initializable<C>;
    requires std::copy_constructible<C>;
    requires std::equality_comparable<C>;
    requires std::swappable<C>;

    requires is_copy_insertable<Type_, Alloc_>;
    requires std::equality_comparable<typename C::value_type>;
    requires std::destructible<typename C::value_type>;

    requires std::forward_iterator<typename C::iterator>;
    requires std::forward_iterator<typename C::const_iterator>;

    requires std::same_as<
        typename C::difference_type,
        typename std::iterator_traits<typename C::iterator>::difference_type>;

    requires std::same_as<
        typename C::difference_type,
        typename std::iterator_traits<
            typename C::const_iterator>::difference_type>;

    {C()}              -> std::same_as<C>;
    {C(a)}             -> std::same_as<C>;
    {C(std::move(a))}  -> std::same_as<C>;
    {a = b}            -> std::same_as<C&>;
    {a = std::move(b)} -> std::same_as<C&>;
    {a.~C()}           -> std::same_as<void>;
    {a.begin()}        -> is_container_iterator<C>;
    {a.end()}          -> is_container_iterator<C>;
    {a.cbegin()}       -> std::same_as<typename C::const_iterator>;
    {a.cend()}         -> std::same_as<typename C::const_iterator>;
    {a == b}           -> std::convertible_to<bool>;
    {a != b}           -> std::convertible_to<bool>;
    {a.swap(b)}        -> std::same_as<void>;
    {std::swap(a, b)}  -> std::same_as<void>;
    {a.size()}         -> std::same_as<typename C::size_type>;
    {a.max_size()}     -> std::same_as<typename C::size_type>;  
    {a.empty()}        -> std::convertible_to<bool>;
};

template<
    typename T,
    is_allocator<T> Alloc = std::allocator<T>,
    template<typename, typename> typename Container
> requires is_container<Container<T, Alloc>, T, Alloc>
void print_container(const Container<T, Alloc>& container)
{
    for (const auto& elem : container)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::vector iv{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print_container(iv);
}