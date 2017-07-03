#### Std::forward

Client Code:
```
template<typename T, typename Arg>
shared_ptr<T> factory(Arg&& arg)
{
  return shared_ptr<T>(new T(std::forward<Arg>(arg)));
}

```
where std::forward is defined as follows:

```
template<class S>
S&& forward(typename remove_reference<S>::type& a) noexcept
{
  return static_cast<S&&>(a);
}

```

Case 1: Suppose first that factory is called on an lvalue of type X:
```
X x;
factory<A>(x);
```
_Translates to_

```
shared_ptr<A> factory(X& && arg)
{
  return shared_ptr<A>(new A(std::forward<X&>(arg)));
}

X& && forward(remove_reference<X&>::type& a) noexcept
{
  return static_cast<X& &&>(a);
}

```

After evaluating the remove_reference and applying the reference collapsing rules, this becomes:

```
shared_ptr<A> factory(X& arg)
{
  return shared_ptr<A>(new A(std::forward<X&>(arg)));
}

X& std::forward(X& a)
{
  return static_cast<X&>(a);
}

```
This is certainly perfect forwarding for lvalues: the argument arg of the factory function gets passed on to A's
constructor through two levels of indirection, both by old-fashioned lvalue reference.

Next, suppose that factory is called on an rvalue of type X:
```
X foo();
factory<A>(foo());
```

Then, again by the special template deduction rule stated above, factory's template argument Arg resolves to X. Therefore, the compiler will now create the following function template instantiations:

```
shared_ptr<A> factory(X&& arg)
{
  return shared_ptr<A>(new A(std::forward<X>(arg)));
}

X&& forward(X& a) noexcept
{
  return static_cast<X&&>(a);
}

```


This is indeed perfect forwarding for rvalues: the argument of the factory function gets passed on to A's constructor
through two levels of indirection, both by reference. Moreover, A's constructor sees as its argument an expression
that is declared as an rvalue reference and does not have a name. By the no-name rule, such a thing is an rvalue.

Therefore, A's constructor gets called on an rvalue. This means that the forwarding preserves any move semantics
that would have taken place if the factory wrapper were not present.

It is perhaps worth noting that the preservation of move semantics is in fact the only purpose of std::forward
in this context. Without the use of std::forward, everything would work quite nicely, except that A's constructor
would always see as its argument something that has a name, and such a thing is an lvalue.

Another way of putting this is to say that std::forward's purpose is to forward the information whether at the
call site, the wrapper saw an lvalue or an rvalue.