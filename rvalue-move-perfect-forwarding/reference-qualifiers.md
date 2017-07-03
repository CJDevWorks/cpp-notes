# reference-qualifiers

In C++03/98, you can already change the behavior of a member function
depending on wether or not the object on which the function is invoked
(*this) is _const_:

```
class Foo
{
public:
     void f(); // called for const objects
     void f() const; // called for non-const objects
};
```

In C++11, there now also exists the same thing for whether or not the
object is an lvalue or rvalue:
```
class Foo
{
public:
     void f() &; // called for lvalue objects
     void f() &&; // called for rvalue objects
};
```

Thus you could have a wrapper class around a container such as
std::vector<int>, and a method that exposes the container. Then, you’d
want that method to return an lvalue if *this is lvalue, so that the
std::vector<int> is only copied, not moved. If *this is, however, an
rvalue, then the std::vector<int> should be returned as an rvalue
reference, so that it can be moved into its destination:

```
class Wrapper
{
public:
    using container_t = std::vector<int>;
    Wrapper(const container_t& container)
        : _container(container)
    {}

    const container_t& container() const &
    {
        print::ln("Copy");
        return _container;
    }

    container_t&& container() &&
    {
        print::ln("Move");
        return std::move(_container);
    }

private:
    container_t _container;
};

int main(int argc, const char* argv[])
{
    Wrapper wrapper({1, 2, 3, 4, 5});
    // copy-constructs the 'copied'
    // >>> Copy
    auto copied = wrapper.container();

    // move-constructs the 'moved
    // >>> Move
    auto moved = Wrapper({1, 2, 3}).container();
}
```

With virtual function and reference - the derived class should be provided with exact reference type, otherwise hidding

** Reasons for hidding :**

First, it looks in the immediate scope, in this case the scope of class D, and makes a list of all functions it can
find that are named g (regardless of whether they're accessible or even take the right number of parameters).

Only if it doesn't does it then continue "outward" into the next enclosing scope and repeat--in this case, the
scope of the base class B--until eventually it either runs out of scopes without having found a function with the
right name or else finds a scope that contains at least one candidate function.

If a scope is found that has one or more candidate functions, the compiler then stops searching and works with the
candidates that it's found, performing overload resolution and applying access rules.