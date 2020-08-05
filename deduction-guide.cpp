#include <iostream>
#include <vector>
#include <iterator>

template<typename T>
class Container {
public:
    Container(std::initializer_list<T>);

    template<typename Iter>
    Container(Iter, Iter);

private:
    std::vector<T> vector_;
};

template<typename T>
Container<T>::Container(std::initializer_list<T> il)
    : vector_(il)
{
}

template<typename T>
template<typename Iter>
Container<T>::Container(Iter beg, Iter end)
    : vector_(beg, end)
{
}

template<typename T>
Container(std::initializer_list<T>) -> Container<T>;

template<typename Iter>
Container(Iter, Iter)
    -> Container<typename std::iterator_traits<Iter>::value_type>;

int main()
{
    std::vector v{1, 2, 3};
    Container c{v.begin(), v.end()};    // no need to specify Container<int>
}