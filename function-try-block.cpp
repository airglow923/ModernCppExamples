#include <cstdlib>
#include <iostream>
#include <stdexcept>

void print_something()
try {
    std::cout << "something\n";
} catch (std::runtime_error e) {
    std::cerr << e.what() << '\n';
    exit(EXIT_FAILURE);
}

class Foo {
public:
    Foo() = default;
    Foo(int i) try
        : i_(i) {
            // do stuff
        } catch (std::exception e) {
            // catch exception
        }
    Foo(double d) try
        : d_(d) {
            // do stuff
        } catch (std::exception e) {
            // catch exception
        }
    Foo(int i, double d) try
        : i_(i), d_(d) {
            // do stuff
        } catch (std::exception e) {
            // catch exception
        }
    ~Foo() = default;

private:
    int i_;
    double d_;
};

int main()
{
    print_something();
}