//
// Created by Chandrajeet Singh on 18/7/17.
//
#include <utility>

struct Widget{};


void authenticateUser() {}

bool f(const Widget& w) { return true;}

void normal_decltype_rules()
{
    int x = 5;
    decltype(x); // int

    Widget w;
    decltype (w);
    const Widget& cw = w;
    auto myWidget1 = cw;            // auto type deduction:
    // myWidget1's type is Widget

    decltype(auto) myWidget2 = cw;  // decltype type deduction:
    // myWidget2's type is
    //   const Widget&

    decltype(f);
    decltype(f(w));
}

void exception_decltype_rules()
{
    int x = 5;
    decltype(x); // int
    decltype((x)); // int
}

// auto return type problem

//C++11
template<typename Container, typename Index>  // C++14 only, and
auto authAndAccess(Container& c, Index i) -> decltype (c[i])
{
    authenticateUser();
    return c[i];              // return type deduced from c[i] using template value deduction
}

//C++14 not quiet right
template<typename Container, typename Index>  // C++14 only, and
auto authAndAccess(Container& c, Index i)
{
    authenticateUser();
    return c[i];              // return type deduced from c[i] using template value deduction
}

// authAndAccess(d, 5) = 10; problem

// decltype(auto) solution
template<typename Container, typename Index>  // C++14 only, and
decltype(auto) authAndAccess(Container& c, Index i)
{
    authenticateUser();
    return c[i];              // return type deduced from c[i] using template value deduction
}

// using it with uniform reference

template<typename Container, typename Index>            // final
auto                                                    // C++11
authAndAccess(Container&& c, Index i)                   // version
-> decltype(std::forward<Container>(c)[i])
{
    authenticateUser();
    return std::forward<Container>(c)[i];
}

// C++14
template<typename Container, typename Index>            // final
decltype(auto)                                          // C++14
authAndAccess(Container&& c, Index i)                   // version
{
    authenticateUser();
    return std::forward<Container>(c)[i];
}

// decltype(auto) problem
//
decltype(auto) f2()
{
    int x = 10;

    return x;
}

// int& and dangling
decltype(auto) f2()
{
    int x = 10;

    return (x);
}

// int&
template <class T, class U>
auto min(T x, U y) -> decltype(y < x ? y : x)
{
    return y < x ? y : x;
}