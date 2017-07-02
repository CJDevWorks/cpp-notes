### Name hidding:

** Reasons for hidding :**

- First, it looks in the immediate scope, in this case the scope of class D, and makes a list of all functions it can
find that are named g (regardless of whether they're accessible or even take the right number of parameters).

- Only if it doesn't does it then continue "outward" into the next enclosing scope and repeat--in this case, the
scope of the base class B--until eventually it either runs out of scopes without having found a function with the
right name or else finds a scope that contains at least one candidate function.

- If a scope is found that has one or more candidate functions, the compiler then stops searching and works with the
candidates that it's found, performing overload resolution and applying access rules.

Examples :
 Virtual function name hidding (also add const/non const and reference qualifiers - lvalue, rvalue)

```
struct B {
  int f( int );
  int f( double );
  int g( int );
};

struct D : public B {
private:
  int g( std::string, bool );
};

D   d;
int i;
d.f(i);    // ok, means B::f(int)
d.g(i);    // error: g takes 2 args
```

Solution :

```
d.B::g(i); // ok, asks for B::g(int)
// OR

struct D : public B {
  using B::g;
private:
  int g( std::string, bool );
};
```

Name hidding in namespace :

```
// in some library header
namespace N { class C {}; }
int operator+(int i, N::C) { return i+1; }

// a mainline to exercise it
#include <numeric>
int main() {
  N::C a[10];
  std::accumulate(a, a+10, 0);
}
```
The code in Example 1 actually calls std::accumulate<N::C*,int>.
The problem is that the compiler may or may not be able to see the operator+(int,N::C) at global scope,
depending on what other functions have already been seen to be declared in namespace std at the point
where std::accumulate<N::C*,int> is instantiated.

Solution:

Making sure that the class and the interface stay together is The Right Thing To Do in any case,
and is a simple way of avoiding complex name lookup problems later on when other people try to use your class.