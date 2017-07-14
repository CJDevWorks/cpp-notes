# prefer-nullptr-to-0-and-null

You should always prefer nullptr to 0 and NULL, on the one hand
because nullptr is a lot more expressive in terms of its
pointer-existence, but also because there can be situations in which
surprises occur if you use 0 or NULL to specify a null-pointer. This is
because 0 and NULL (a macro for 0) are numeric types – 0 being
an int and NULL integral (often int) – and not actually pointer types,
which can cause problems with overloads, for example:

    void f(int);
    void f(void*);

    f(0); // calls f(int)
    f(nullptr); // calls f(void*)

Here the developer may have wished to pass a null-pointer to f, but by
passig a 0, which is an int, s/he actually called the overload taking an
integer. Moreover, 0 may not end up meaning a null-pointer when working
with templates:

    template<typename T>
    void f(const T& pointer)
    {
        function_taking_pointer(pointer);
    }

    f(0); // T is deduced as int -> call fails
    f(nullptr); // fine, T deduced as nullptr_t, which implicitly converts to all pointer types.

Note the last comment: nullptr is of std::nullptr_t, which implicitly
converts to all pointer types.


The **macro NULL is an implementation-defined null pointer constant**, which may be
- an integral constant expression rvalue of integer type that evaluates to zero

- an integer literal with value zero, or a prvalue of type std::nullptr_t

```
#define NULL 0
//since C++11
#define NULL nullptr
```

typedef decltype(nullptr) nullptr_t;

There exist implicit conversions from nullptr to null pointer value of any pointer type and any pointer to member type. Similar conversions exist for any null pointer constant, which includes values of type std::nullptr_t as well as the macro NULL.
