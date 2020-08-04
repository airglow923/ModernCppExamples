/*
 * Module is a library handling method introduced in C++20.
 */

module;     // define module

export module sample_module;

export class Foo {  
public:
    Foo() = default;
    Foo(int i): i__(i) {}
    Foo(double d): d__(d) {}
    Foo(int i, double d): i__(i), d__(d) {}
    ~Foo() = default;

    int get_i() {return i__;}
    double get_d() {return d__;}
    double multiply();
private:
    int i__;
    double d__;
};

// member functions are automatically exported if class is exported
double Foo::multiply()
{
    return i__ * d__;
}

export int return_42()
{
    return 42;
}

int not_exported()
{
    return -1;
}