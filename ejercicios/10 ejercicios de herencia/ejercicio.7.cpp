#include <iostream>
using namespace std;

class A
{
public:
    void f() { cout << "A\n"; }
};
class B
{
public:
    void g() { cout << "B\n"; }
};

class C : public A, public B
{
};

int main()
{
    C obj;
    obj.f();
    obj.g();
}