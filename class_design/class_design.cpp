#include <iostream>

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
class Base
{
    std::string name_;
    Base(std::string name) : name_(std::move(name)) {}
};

class Derived : public Base
{
    Derived(std::string name) : Base(name){}
};



class MyCpp14Class
{
    struct Impl;
    using PImpl = std::unique_ptr<Impl> ;
    Pimpl impl_;

public:
    explicit MyCpp14Class(std::string name);



};

