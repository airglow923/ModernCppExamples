/*
 * Tag dispatch is a technique to call a function implemented based on
 * the provided tag.
 */

#include <type_traits>
#include <iterator>

namespace hyundeok {
    template<typename Iter, typename BinaryOperation>
    void func(Iter beg, Iter end, BinaryOperation binary_op,
        std::random_access_iterator_tag);

    template<typename Iter, typename BinaryOperation>
    void func(Iter beg, Iter end, BinaryOperation binary_op,
        std::forward_iterator_tag);

    template<typename Iter, typename BinaryOperation>
    void func(Iter beg, Iter end, BinaryOperation binary_op)
    {
        func(beg, end, binary_op,
            typename std::iterator_traits<Iter>::iterator_category{});
    }
}