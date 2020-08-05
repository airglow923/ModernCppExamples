/*
 * std::filesystem is a library introduced in C++17.
 */

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void print_directory(fs::path p)
try
{
     if (is_directory(p)) {
        std::cout << p << ":\n";
        for (const auto& entry : fs::recursive_directory_iterator{p})
            std::cout << '\t' << entry.path() << '\n';
     }
}
catch (const fs::filesystem_error& ex) {
    std::cerr << ex.what() << '\n';
}

int main()
{
    print_directory(".");
}