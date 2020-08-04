#include <iostream>

class Base {};

class Derived : public Base {};

class DDerived : public Derived {};

class AnotherDerived : public Base {};

int main()
{
    Base base;
    DDerived dd;
    AnotherDerived ad;

    Base* bp = &base;
    DDerived* ddp = &dd;
    AnotherDerived* adp = &ad;

    if (auto p = dynamic_cast<Base*>(adp)) {
        std::cout << "Derived\n";
    } else {
        std::cout << "Not derived\n";
    }
}