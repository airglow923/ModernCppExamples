#include <iostream>
#include <vector>
#include <utility>      // pair

int main()
{
    std::vector<std::pair<int, int>> pv{
        {0, 9}, {1, 8},
        {2, 7}, {3, 6},
        {4, 5}, {5, 4},
        {6, 3}, {7, 2},
        {8, 1}, {9, 0},
    };
    std::vector<int> iv(10);

    // C++17: structured binding declaration
    for (auto&& [key, value] : pv)
        std::cout << "key: " << key << ", value: " << value << '\n';

    // C++20: temporary range expression
    for (auto&& elem : std::vector{0, 1, 2, 3, 4, 5})
        std::cout << elem << ' ';

    // C++20: init-statement
    for (auto n = iv.size(); auto&& val : iv) {
        int i = iv.size() - n--;
        std::cout << "Element at " << i << ": " << val << '\n';
    }
}