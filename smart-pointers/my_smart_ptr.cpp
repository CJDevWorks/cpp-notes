//
// Created by Chandrajeet Singh on 17/7/17.
//
#include <iostream>
#include <memory>

template <typename T>
struct default_delete
{
    void operator()(T* p) const noexcept
    {
        delete p;
    }
};

std::unique_ptr<int> up;
std::shared_ptr<int> sp;

template <typename T, template<typename>class Deleter= default_delete<T>>
class MyUnique_Ptr {
    T *mp;
    Deleter del;
public:
    MyUnique_Ptr () : mp (nullptr) { }

    MyUnique_Ptr (T *p) : mp (p) , del{} { }

    ~MyUnique_Ptr () {
        if (mp) del (mp);
    }

    //MyUnique_Ptr(const MyUnique_Ptr& other) = delete;
    //MyUnique_Ptr& operator = (const MyUnique_Ptr& other) = delete;

    MyUnique_Ptr(MyUnique_Ptr &&other)
    :   mp(other.mp), del(other.del)
    {
        other.mp = nullptr;
    }

    MyUnique_Ptr& operator = (MyUnique_Ptr&& other)
    {
        mp = other.mp;
        del = other.del;
        other.mp = nullptr;
    }

    //templatized  move constructor and move assignment operator.
};

