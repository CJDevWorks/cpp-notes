
#include <utility>
#include <iostream>

struct SampleClass{
    SampleClass(){}
    SampleClass(int i) : mem(i){}
    void someMemberFunction() {}
    int mem{0};

    int print() {return mem;}
};

SampleClass fooNotReference() {return SampleClass(0);}
SampleClass& fooReference() { static SampleClass value = 41; return value;}
SampleClass&& fooRvalueReference() { static SampleClass value = 43; return std::move(value);}

int main(int argc, char * argv [])
{
    // x = lvalue, 5 = rvalue
    // other rvalues: 'c', true etc.
    int&& i =5;
    //creates a temporary, initialized with 5, whose lifetime is extended to the end of the block.
    i = 10;
    // changes the value of the still living temporary.


    SampleClass t; // lvalue

    // 1. lvalue assigned by lvalue
    // Constructors return rvalues!
    SampleClass x = t; //lvalue

    // 2. lvalue assigned by rvalue
    // fooNotReference() = rvalue because
    // it returns a non-reference
    x = fooNotReference();
    std::cout << x.print()<< std::endl;

    // 3. lvalue assigned by lvalue reference
    // fooReference() = lvalue because
    // it returns a reference
    x = fooReference();
    std::cout << x.print() << std::endl;

    // 4. lvalue assigned by rvalue reference
    x = fooRvalueReference();
    std::cout << x.print() << std::endl;

    // 5. rvalues getting assigned by lvalue/lvalue ref/rvalue ref - this happens temporary
    fooNotReference() = t;
    fooNotReference() = fooReference();
    fooNotReference() = fooRvalueReference();

    fooNotReference().someMemberFunction();

    /* NOW references */
    // Because fooReference() returns a reference
    // to an object which has an identity and can
    // be referred to, r can be a new reference to
    // this object
    SampleClass& r = fooReference();

    // Error! Because fooNotReference() returns a
    // non-reference temporary rvalue, this object
    // has no identity and can not be referred to
    // by a non-const reference
    //SampleClass& nr = fooNotReference();

    // But const references work with rvalues
    // (this is simply a C++ rule ...)
    const SampleClass& cnr = fooRvalueReference();

    // Function names are rvalues
    typedef SampleClass ((&PTR))();
    PTR ptr = fooNotReference; // ===> XXXXX

    // expression(fooNotReference) must be rvalue
    // typedef SampleClass ((&&PTR))();
    // PTR ptr = fooNotReference; // ===> XXXXX

    SampleClass arr [4];

    // Error! Array names are rvalues
    // (return a pointer to the first
    // element of the array), but
    // ra is a non-const reference and
    // can thus only bind to lvalues
    SampleClass(&ra) [4]  = arr;

    //SampleClass(&&rra) [4] = arr;

    // In C++11 you can use rvalue
    // references to bind temporary
    // objects and other rvalues
    // Note the && instead of &
    SampleClass&& rvr = fooNotReference();
    // These temporary variables can
    // then be used further
    rvr.someMemberFunction();


    SampleClass&& rvr1 = fooRvalueReference();
    rvr1.someMemberFunction();
}