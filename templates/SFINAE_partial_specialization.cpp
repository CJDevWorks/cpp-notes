#include <iostream>

template<bool B, typename T = void>
struct my_enable_if{ };

template<typename T>
struct my_enable_if <true, T>
{
    typedef T type;
};

template<bool B>
using my_enable_if_t = my_enable_if<B, void>::type;

template <bool B, template IF_, template ELSE_>
struct Condition
{
    typedef IF_ value;
};

template <template IF_, template ELSE_>
struct Condition<false, IF_, ELSE_>
{
    typedef IF_ value;
};