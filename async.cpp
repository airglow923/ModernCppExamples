#include <iostream>
#include <future>
#include <random>
#include <type_traits>
#include <vector>
#include <limits>
#include <numeric>

using ull = unsigned long long;

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

template<
    typename T,
    typename Alloc = std::allocator<T>,
    template<typename, typename> typename Container
>
ull async_accumulate(const Container<T, Alloc>& container)
{
    auto func = std::accumulate<
        typename Container<T, Alloc>::const_iterator, T>;

    auto beg = container.cbegin();
    std::size_t sz = container.size();

    auto thread0 = std::async(func, beg, beg + sz / 4, 0);
    auto thread1 = std::async(func, beg + sz / 4, beg + sz / 2, 0);
    auto thread2 = std::async(func, beg + sz / 2, beg + sz * 3 / 4, 0);
    auto thread3 = std::async(func, beg + sz * 3 / 4, beg + sz, 0);

    return thread0.get() + thread1.get() + thread2.get() + thread3.get();
}

int main()
{
    std::vector<short> iv;
    iv.reserve(std::numeric_limits<short>::max());
    fill_random(iv);
    
    std::cout << "Sum: " << async_accumulate(iv) << '\n';
}