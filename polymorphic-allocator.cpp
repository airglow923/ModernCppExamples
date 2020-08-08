/*
 * In C++17, polymorphic memory management is introduced with the following
 * classes in the namespace pmr:
 * 
 *      - std::pmr::polymorphic_allocator
 *      - std::pmr::memory_resource
 *      - std::pmr::pool_options
 *      - std::pmr::synchronized_pool_resource
 *      - std::pmr::unsynchronized_pool_resource
 *      - std::pmr::monotonic_buffer_resource
 * 
 * Before C++17,
 * An object declared with an allocator cannot be assigned to another declared
 * with a different allocator.
 * 
 * To resolve such a problem,  a class can now use
 * std::pmr::polymorphic_allocator for high-level memory management and
 * std::pmr::memory_resource for low-level memory_management so that instances
 * of a class that adopt different memory management policies are compatible
 * one another.
 * 
 * Note that the implementation of std::pmr::vector is as follows:
 * 
 * namespace pmr {
 *      template<class T>
 *      using vector = std::vector<T, std::pmr::polymorphic_allocator<T>>;
 * }
 */

#include <iostream>
#include <memory_resource>
#include <vector>

int main()
{
    std::pmr::synchronized_pool_resource sync_pool;
    std::pmr::unsynchronized_pool_resource unsync_pool;

    std::pmr::vector<int> v0{{0, 1, 2, 3, 4}, &sync_pool};
    std::pmr::vector<int> v1{{5, 6, 7, 8, 9}, &unsync_pool};

    for (const auto& elem : v0)
        std::cout << elem << ' ';

    std::cout << '\n';

    v0 = v1;

    for (const auto& elem : v0)
        std::cout << elem << ' ';
}