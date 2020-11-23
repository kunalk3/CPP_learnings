/**
 * ---------------------------------------------------------------------------------------
 * Author  : Kunal K.
 * Title   : Bridge design pattern
 * Purpose : To demonstrate the concepts of design patterns
 * Version : 1.0
 * ---------------------------------------------------------------------------------------
**/

#include <iostream>
#include <memory>

struct Interface {
    virtual void A() = 0;
    virtual void B() = 0;
    virtual ~Interface() = default;
};

// first implementation
struct Impl1 : Interface {
    void A() override { std::cout << "Impl1::A()\n"; }

    void B() override { std::cout << "Impl1::B()\n"; }
};

// second implementation
struct Impl2 : Interface {
    void A() override { std::cout << "Impl2::A()\n"; }

    void B() override { std::cout << "Impl2::B()\n"; }
};

// concrete class that can change its interface
class Foo {
    std::unique_ptr<Interface> _ptr_impl;

  public:
    explicit Foo(std::unique_ptr<Interface> ptr_impl)
        : _ptr_impl{std::move(ptr_impl)} {}
    void set_interface(std::unique_ptr<Interface> ptr_impl) {
        _ptr_impl = std::move(ptr_impl);
    }
    void A() { _ptr_impl->A(); }
    void B() { _ptr_impl->B(); }
};

int main() {
    // default interface
    Foo foo{std::make_unique<Impl1>()};
    foo.A();
    foo.B();

    // "switch" the interface
    foo.set_interface(std::make_unique<Impl2>());
    foo.A();
    foo.B();
}
