#include <iostream>
#include <random>
#include <vector>
#include <limits>
#include <type_traits>

template<
    typename T,
    typename U = T,
    template<typename, typename = std::allocator<T>> typename Container
>
void fill_random(
    Container<T>& container,
    U start = 0, U end = std::numeric_limits<T>::max())
{
    std::random_device rd;
    std::mt19937 engine{rd()};
    
    if (std::is_integral_v<T>) {
        std::uniform_int_distribution<U> dist{start, end};
        for (; start <= end; --end)
            container.push_back(dist(engine));
    }
}

int main()
{
    std::vector<char> iv;
    iv.reserve(std::numeric_limits<char>::max());

    fill_random(iv);

    for (const auto& i : iv)
        std::cout << i << ' ';
    std::cout << '\n' << "size: " << iv.size() << '\n';
}