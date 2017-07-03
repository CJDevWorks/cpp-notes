### What is std::move
**_*std::move performs an unconditional cast to an rvalue*_**

std::move is used to indicate that an object t may be "moved from", i.e. allowing the efficient transfer of
resources from t to another object.

Here's the implementation:
```
#include <utility>
template< class T >
typename std::remove_reference<T>::type&& move( T&& t ) noexcept;
```

The purpose of std::move is to pass its argument right through by reference and make it bind like an rvalue.

```
template<class T>
typename remove_reference<T>::type&&
std::move(T&& a) noexcept
{
  typedef typename remove_reference<T>::type&& RvalRef;
  return static_cast<RvalRef>(a);
}
```

### Why you need it
The functions that accept rvalue reference parameters (including move constructors, move assignment operators, and
regular member functions such as std::vector::push_back) are selected, by overload resolution, when called with
rvalue arguments (either prvalues such as a temporary objects or xvalues such as the one produced by std::move).

Names of rvalue reference variables are lvalues and have to be converted to xvalues to be bound to the function
overloads that accept rvalue reference parameters, which is why move constructors and move assignment operators
typically use std::move:

Exception in case of : universal reference use std::forward ;