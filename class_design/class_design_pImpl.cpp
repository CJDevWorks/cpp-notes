#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Requirement.
// explicit constructor and explicit operator
// noexcept
// CC, CA, MC,MA
// destructor
// delete
// default
// with members move only type.
// with members constant and reference.
// reference qualifiers
// resource management
// special member function generation
// exceptions

class MyPImpl
{
    struct Impl;
    using PImpl = std::unique_ptr<Impl> ;
    PImpl impl_;

public:
    MyPImpl();
    ~MyMyPImpl(); // cant define here - can be defined after Impl definition

    MyPImpl(const MyPImpl& other);
    MyPImpl& operator = (const MyPImpl& other);

    MyPImpl(MyPImpl&& other);
    MyPImpl& operator = (MyPImpl&& other);

};

// In MyPImpl.cpp
struct MyPImpl::Impl
{
    std::vector<std::string> names;
};

MyPImpl::MyPImpl()
: impl_(std::make_unique<Impl>())
{}

~MyPImpl::MyPImpl() = default;

MyPImpl::MyPImpl(const MyPImpl& other)
    : impl_(std::make_unique<Impl>(*other.impl_))
{}

MyPImpl& MyPImpl::operator = (const MyPImpl& other)
{
    if (this != &other)
        *impl_ = *other.impl_;

    return *this;
}

MyPImpl::MyPImpl(MyPImpl&& other) = default;
MyPImpl& MyPImpl::operator = (MyPImpl&& other) = default;
