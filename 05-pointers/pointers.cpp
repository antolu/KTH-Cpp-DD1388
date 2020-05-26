#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>


struct A {
    int data;

};

struct B {
    B() { b = new int[4]; }

    int * b;
    ~B() { delete [] b; }
    B(const B &) = delete;
    void operator= (const B & ) = delete;
};

struct BhasA;

struct AhasB {
    AhasB(std::shared_ptr<BhasA> b) : m_b(b)  {
        resource = new int[4];
    };

    std::shared_ptr<BhasA> m_b;
    int * resource;

    ~AhasB() {delete [] resource;}
    AhasB(const AhasB &) = delete;
    void operator=(const AhasB &) = delete;
};

struct BhasA {
    BhasA() {resource = new int[4];};

    std::weak_ptr<AhasB> m_a;
    int * resource;

    ~BhasA() {delete [] resource;}
    BhasA(const BhasA &) = delete;
    void operator=(const BhasA &) = delete;
};

void foo(std::unique_ptr<A> p) {
    std::cout << p->data << std::endl;
}

void foo2(std::shared_ptr<A> p) {
    std::cout << p->data << std::endl;
}

int main(int argc, char const *argv[])
{
    std::cout << "Unique ptr: " << std::endl;
    std::unique_ptr<A> ptr(new A {4});
    std::cout << ptr->data << std::endl;

    foo(std::move(ptr));

    std::cout << "Shared ptr: " << std::endl;
    std::shared_ptr<A> sptr(new A {5});
    std::cout << sptr->data << std::endl;

    foo2(sptr);
    // foo2(std::move(sptr));
    // no memory leak

    std::cout << "Weak ptr: " << std::endl;
    // std::weak_ptr<A> wa(new A {6});
    std::weak_ptr<A> wptr = sptr;
    std::cout << wptr.lock()->data << std::endl;

    std::cout << "Circular dependencies" << std::endl;
    std::shared_ptr<BhasA> bptr(new BhasA);
    std::shared_ptr<AhasB> aptr(new AhasB(bptr));

    bptr->m_a=aptr;

    std::cout << "Using a deleter" << std::endl;
    // auto deleter = [](auto * B) {delete[] B;};
    std::unique_ptr<B, std::function<void(B*)>> pb(new B[2], [](B* b) {delete[] b;});

    return 0;
}
