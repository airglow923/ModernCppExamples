/*
 * The mutable specifier is used primarily on a class data member declared as
 * const to make its member modifiable. It can only be used with non-static
 * class members and non-reference non-const type.
 */

struct Foo {
    Foo(int i, double d)
        : i_(i), d_(d) {}
    mutable int i_;
    double d_;
};

int main()
{
    const Foo foo{1, 3.14};
    foo.i_ = 42;
    // foo.d_ = 7.2562;     // error
}