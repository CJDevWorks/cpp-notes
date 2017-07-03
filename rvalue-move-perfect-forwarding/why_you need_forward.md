**Why std::forward**

```
template<typename T, typename Arg>
shared_ptr<T> factory(Arg arg)
{
  return shared_ptr<T>(new T(arg));
}
```

Problem : extra copy in new T(arg);

Take 1: pass by reference.
```
template<typename T, typename Arg>
shared_ptr<T> factory(Arg& arg)
{
  return shared_ptr<T>(new T(arg));
}

```
problem:  Doesn't work with rvalues :-
factory<X>(hoo()); // error if hoo returns by value
factory<X>(41); // error

Take 2 : Pass by const reference :

```
template<typename T, typename Arg>
shared_ptr<T> factory(Arg const & arg)
{
  return shared_ptr<T>(new T(arg));
}

```
Problem :
1. Too many overloads if there is const/non-const function is there are more args.

2. Disables move. (the argument of the constructor of T in the body of factory is an lvalue.)

**_Solution:   std::forward_**

Check - how_std_forward_works

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