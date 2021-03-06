

### How it works
Suppose that we call std::move on an lvalue of type X:
```
X x;
std::move(x);
```
By the new special template deduction rule, the template argument T will resolve to X&.

<A>
- When an lvalue is passed as an argument to func, T is deduced to be an lvalue reference.
- When an rvalue is passed, T is deduced to be a non-reference.
</A>

Therefore, what the compiler ends up instantiating is
##### LVALUE case:
```
typename remove_reference<X&>::type&&
std::move(X& && a) noexcept
{
  typedef typename remove_reference<X&>::type&& RvalRef;
  return static_cast<RvalRef>(a);
}
```

After evaluating the remove_reference and applying the new reference collapsing rules, this becomes
```
X&& std::move(X& a) noexcept
{
  return static_cast<X&&>(a);
}
```

std::move actually works fine when called on an rvalue.

##### RVALUE case:
```
typename remove_reference<X>::type&&
std::move(X && a) noexcept
{
  typedef typename remove_reference<X>::type&& RvalRef;
  return static_cast<RvalRef>(a);
}
```

why would anybody want to call std::move on an rvalue, when its only purpose is to turn things into rvalues?
Also, you have probably noticed by now that instead of

```
std::move(x); // ===>>> static_cast<X&&>(x);
```

However, std::move is strongly preferred because it is more expressive.