/*
 * Tag dispatch is a technique to call a function implemented based on
 * the provided tag.
 */

#include <type_traits>
#include <iterator>
#include <vector>
#include <iostream>

namespace hyundeok {
    template<typename Iter, typename BinaryOperation>
    void func(Iter beg, Iter end, BinaryOperation binary_op,
        std::random_access_iterator_tag)
    {
        std::cout << "std::random_access_iterator\n";
    }

    template<typename Iter, typename BinaryOperation>
    void func(Iter beg, Iter end, BinaryOperation binary_op,
        std::forward_iterator_tag)
    {
        std::cout << "std::forward_access_iterator\n";
    }

    template<typename Iter, typename BinaryOperation>
    void func(Iter beg, Iter end, BinaryOperation binary_op)
    {
        func(beg, end, binary_op,
            typename std::iterator_traits<Iter>::iterator_category{});
    }
}

int main()
{
    using namespace hyundeok;

    std::vector<int> v{0, 1, 2, 3, 4, 5};
    func(v.begin(), v.end(), []{});
}