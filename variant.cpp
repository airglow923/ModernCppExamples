/*
 * std::variant is a library introduced in C++17.
 */

#include <iostream>
#include <variant>
#include <string>

struct Entry {
    std::string name;
    std::variant<const char*, int> value;
};

int main()
{
    Entry entry{"shibe", "jumps"};
    
    // surprisingly, if I enter floating-point value, this qualifies to int.
    // maybe this is not considered as list initialization.

    if (std::holds_alternative<int>(entry.value)) {
        std::cout << std::get<int>(entry.value) << ": int\n";
    } else if (std::holds_alternative<const char*>(entry.value)) {
        std::cout << std::get<const char*>(entry.value) << ": char*\n";
    } else {
        std::cout << "nothing\n";
    }
}