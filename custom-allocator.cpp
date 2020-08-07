#include <cstddef>
#include <memory>
#include <type_traits>
#include <iostream>
#include <vector>

namespace hyundeok {

template<typename T>
struct Allocator {
public:
    using value_type                             = T;
    using size_type                              = std::size_t;
    using difference_type                        = std::ptrdiff_t;
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal                        = std::true_type;

    [[nodiscard]] constexpr T* allocate(std::size_t n);

    constexpr void deallocate(T* p, std::size_t n);
};

template<typename T>
[[nodiscard]] constexpr T* Allocator<T>::allocate(std::size_t n)
{
    return static_cast<T*>(::operator new(n * sizeof(T)));
}

template<typename T>
constexpr void Allocator<T>::deallocate(T* p, std::size_t n)
{
    ::operator delete(p, n * sizeof(T));
}

}

int main()
{
    using namespace hyundeok;

    std::vector<int, Allocator<int>> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (const auto& elem : v)
        std::cout << elem << ' ';
}