## Asserts

Defined in header <cassert>
```
#ifdef NDEBUG
#define assert(condition) ((void)0)
#else
#define assert(condition) /*implementation defined*/
#endif
```

- Assertions are for debugging. The user of your shipped code should never see them.
If an assertion is hit, your code needs to be fixed. PreCondition to identify internal coding bugs.

Typically, assertions can be used for:

- Catching the program logic errors.  Use assertion statements to catch logic errors. You can set an assertion on a
condition that must be true according to your program logic. The assertion only has an effect if a logic error occurs.

- Checking the results of an operation.  Use assertion statements to check the result of an operation.
Assertions are most valuable for testing operations which results are not so obvious from a quick visual inspection.


- Testing the error conditions that supposed to be handled.  Use assertions to test for error conditions at a point in
 your code where errors supposed to be handled.

### Implement a static assert

leave a generic template non-defined, and define only the true specialization.

```
template<bool> // generic
struct my_static_assert;

template<>
struct my_static_assert<true>{};

#define STATIC_ASSERT(exp) (my_static_assert< (exp) >())

template<typename T1, typename T2>
void dumb_copy(const T1 from, T2 to) {
    STATIC_ASSERT(sizeof(T2) >= sizeof(T1));
    memcpy(&to, &from, sizeof(T1));
}

```

### Usage C++11

can provide a message but has to be string literal, not even const expression

```
#include <assert.h>
#include <type_traits>

template <class T>
void swap(T& a, T& b)
{
    static_assert(std::is_copy_constructible<T>::value,
                  "Swap requires copying");
    static_assert(std::is_nothrow_copy_constructible<T>::value
               && std::is_nothrow_copy_assignable<T>::value,
                  "Swap may throw");
    auto c = b;
    b = a;
    a = c;
}

template <class T>
struct data_structure
{
    static_assert(std::is_default_constructible<T>::value,
                  "Data Structure requires default-constructible elements");
};

```


