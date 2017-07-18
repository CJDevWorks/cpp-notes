#include <iostream>
#include <typeinfo>
#include "boost/type_index.hpp"

#define PRINT(T, val) \
using std::cout;    \
using boost::typeindex::type_id_with_cvr;   \
std::cout << "[T = " << type_id_with_cvr<T>().pretty_name() \
<< "] [param =" << type_id_with_cvr<decltype(val)>().pretty_name() << "]" << '\n';

#define PRINT1(T, val) \
using std::cout;    \
using boost::typeindex::type_id_with_cvr;   \
std::cout << "[T = " << type_id_with_cvr<T>().pretty_name() \
<< "] [param =" << type_id_with_cvr<decltype(val)>().pretty_name() << "]" << '\n';


template <class T, class U>
auto min(T x, U y) -> decltype(y < x ? y : x)
{
    return y < x ? y : x;
}

int x = 1;
int& rx = x;
int* px = &x;
const int* cpx = &x;

const int cx =2;
const int& crx = cx;
const int* pcx = &cx;

// function returning rvalue
int getCount()
{
    return 10;
}

void somefunc()
{
}

template<typename T>
void fooVal(T val)
{
    PRINT(T, val);
}

template<typename T>
void fooRef(T& val)
{
    PRINT(T, val);
}

template<typename T>
void fooCRef(const T& val)
{
    PRINT(T, val);
}


template<typename T>
void fooPtr(T* val)
{
    PRINT(T, val);
}

template<typename T>
void fooFwdRef(T&& val)
{
    PRINT(T, val);
}

template<typename T>
void fooArrayVal(T val)
{
    PRINT(T, val);
}

template<typename T>
void fooArrayRef(T (&)[10])
{
    T val[10];
    PRINT(T, val);
}

void rulesTemplateTypeDeduction()
{
    // by reference
    fooRef(x); // int
    fooRef(cx); // const int
    fooRef(crx); // const int

    fooCRef(x);   // int
    fooRef(cx);   // const int --xx
    fooRef(crx);  // const int -- xx

    fooPtr(px); // int
    fooPtr(cpx); // const int

    // by universal ref, expression is always lvalue
    fooFwdRef(x); // int&
    fooFwdRef(cx);  // const int&
    fooFwdRef(crx); // const int&
    fooFwdRef(28);  // rvalue int -- xxx
    fooFwdRef(getCount()); // int -- xx

    // by val
    fooVal(x);  // int
    fooVal(cx); // int
    fooVal(crx);  // int  -- yyy
    fooVal(px);   // int*
    fooVal(cpx);  // const int*  -- yyy
    const char* charPtr = "Fun With Pointer";
    fooVal(charPtr);  // const char* -- yyy

    const char* const consCharPtr = "Fun With Pointer";
    fooVal(consCharPtr); // const char* -- yyy

    // Array argument
    const char name[] = "C.J.Singh";
    fooVal(name);  // const char*  -- yyy
    const char (&arrRef)[10] = name;
    fooVal(arrRef);  // const char*  -- yyy

    fooRef(name); // const char [10]  -- xxx

    // function
    fooVal(somefunc); // void (*) () -- param?
    fooRef(somefunc); // void ()  -- param
}

void rulesAutoTypeDeduction()
{
    // all rules same as template except - initializer_list
    // common examples
    auto x =27;
    const auto cx = x;
    const auto& crx = x;

    auto&& uref1 = x;
    auto&& uref2 = cx;
    auto&& uref3 = 27;

    const char name[] = "C.J.Singh";
    auto arr1 = name;
    auto& arr2 = name;

    auto func1 = somefunc;
    auto& func2 = somefunc;

    // initializer examples
    auto initX = {10}; // -- not an integer but an initilizer_list
    auto initX1{11}; // -- not an integer bit an initializer list
    // auto initX2 = {1,2,3.0}; // initializer with different type
    auto initX2 = {1,2,3}; // std::initializer_list<int>
    // fooVal({1,2,3}) // can't deduce type - by template deduction
    // but if a overload is provided as
    // template<typename T>
    // void fooVal(std::initializer_list<T> initList);
    // then fooVal({1,2,3}) will be duduced as initializer_list<int>

    // auto in function return type
    // same as template deduction
    // auto createInitList() {return {1,2,3};} // error

    // auto as lambda argument
    // same as template deduction
    // std::vector<int> v;
    // auto resetV = [](const std::vector<int>& other) { v = other;}
    // resetV({1,2,3});
}

void rules_decltype_Deduction()
{
    int x = 5;
    decltype(x); // int
    decltype((x)); // int&

    int i =4, j=3;
    int dummy =5;
    PRINT(decltype(min(i,j)), dummy);
}

void rulesInitializerList()
{
    // initializer examples
    auto initX = {10}; // -- not an integer but an initilizer_list
    auto initX1{11}; // -- not an integer bit an initializer list
    // auto initX2 = {1,2,3.0}; // initializer with different type
    auto initX2 = {1,2,3}; // std::initializer_list<int>
    // fooVal({1,2,3}) // can't deduce type - by template deduction
    // but if a overload is provided as
    // template<typename T>
    // void fooVal(std::initializer_list<T> initList);
    // then fooVal({1,2,3}) will be duduced as initializer_list<int>

    // auto in function return type
    // same as template deduction
    // auto createInitList() {return {1,2,3};} // error

    // auto as lambda argument
    // same as template deduction
    // std::vector<int> v;
    // auto resetV = [](const std::vector<int>& other) { v = other;}
    // resetV({1,2,3});
}

int main(int argc, char* argv[])
{

    rulesTemplateTypeDeduction();

    std::cout << "decltype deduction " << std::endl;
    rules_decltype_Deduction();
}