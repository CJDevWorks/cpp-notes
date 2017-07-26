//
// Created by Chandrajeet Singh on 24/7/17.
//
#include <iostream>
#include <vector>
#include <regex>

using std::endl;
struct A {
    A (int) { std::cout << " A constructor" << endl; }      // converting constructor
    A (int , int) { std::cout << " A constructor 2 parameters " << endl; } // converting constructor (C++11)
    operator bool () const {
        std::cout << " A conversion operator" << endl;
        return true;
    }
};

struct B {
    explicit B (double) { std::cout << " B constructor" << endl; }

    explicit B (int , int) { std::cout << " A constructor 2 parameters " << endl; }

    explicit operator bool () const {
        std::cout << " A conversion operator" << endl;
        return true;
    }
};

void fooB (B b) {
    std::cout << " fooB(B) " << endl;
}

void fooA(A a)
{
    std::cout << " fooA(A) " << endl;
}



int main (int argc , char **argv)
{
    A a1 = 1;      // OK: copy-initialization selects A::A(int)
    A a2 (2);       // OK: direct-initialization selects A::A(int)
    A a3{ 4 , 5 };   // OK: direct-list-initialization selects A::A(int, int)
    A a4 = { 4 , 5 }; // OK: copy-list-initialization selects A::A(int, int)
    A a5 = (A) 1;   // OK: explicit cast performs static_cast


    if (a1){}      // OK: A::operator bool()
    bool na1 = a1; // OK: copy-initialization selects A::operator bool()
    bool na2 = static_cast<bool>(a1); // OK: static_cast performs direct-initialization
    fooA(1);

    //  B b1 = 1;      // error: copy-initialization does not consider B::B(int)

    B b2 (2);       // OK: direct-initialization selects B::B(int)
    B b3{ 4 , 5 };   // OK: direct-list-initialization selects B::B(int, int)

    //  B b4 = {4, 5}; // error: copy-list-initialization does not consider B::B(int,int)

    B b5 = (B) 1;   // OK: explicit cast performs static_cast
    if (b2){}      // OK: B::operator bool()

    //  bool nb1 = b2; // error: copy-initialization does not consider B::operator bool()

    bool nb2 = static_cast<bool>(b2); // OK: static_cast performs direct-initialization
    // fooB(1); //   conversion not allowed.


    // curious case of std::regex
    std::vector<std::regex> regexs;
    // std::regex rx = nullptr;
    // regexs.push_back(nullptr); this doesn't work


    std::regex rx(nullptr);

    //regexs.emplace_back(nullptr); // this works

    // regex constructor : explicit regex(const char*) -- in first case copy initialization
    // in second case direct initialization


    return 0;
}

