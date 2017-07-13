# template-specialization

Sometimes a generic algorithm can work much more efficiently for a certain kind of sequence
(for example, when given random-access iterators), and so it makes sense to specialize it for that case while
using the slower but more generic approach for all other cases.

Performance is a common reason to specialize, but it's not the only one; for example, you might also specialize a
template to work with certain objects that don't conform to the normal interface expected by the generic template.

**This declaration must be in the same namespace or, for member templates, class scope as the primary template
definition which it specializes.**

For class templates only, you can define partial specializations that don't have to fix all of the
primary (unspecialized) class template's parameters.

Here is an example from 14.5.4. The first template is the primary class template:

```
  template<class T1, class T2, int I>
  class A             { };// #1

  // We can specialize this for the case when T2 is a T1*:
  template<class T, int I>
  class A<T, T*, I>   { }; // #2

  // Or for the case when T1 is any pointer:
  template<class T1, class T2, int I>
  class A<T1*, T2, I> { }; // #3

  // Or for the case when T1 is int and T2 is any pointer and I is 5:
  template<class T>
  class A<int, T*, 5> { }; // #4

  // Or for the case when T2 is any pointer:
  template<class T1, class T2, int I>
  class A<T1, T2*, I> { }; // #5
```

Declarations 2 to 5 declare partial specializations of the primary template. The compiler will then choose the
appropriate template. Choosing among matching partial specialization with "more specialized".

```
  A<int, int, 1>   a1;  // uses #1
  A<int, int*, 1>  a2;  // uses #2, T is int,
                        //          I is 1
  A<int, char*, 5> a3;  // uses #4, T is char
  A<int, char*, 1> a4;  // uses #5, T1 is int,
                        //          T2 is char,
                        //          I is 1
  A<int*, int*, 2> a5;  // ambiguous:
                        // matches #3 and #5
```

```
// Template class
template<typename T>
class Foo
 {
public:
    
     Foo()
     {
         std::cout << "Foo<T> called" << std::endl;
     }
 };
// Full specialization, T is not used
template<>
class Foo<int>
 {
public:
     Foo()
     {
         std::cout << "Foo<int> called" << std::endl;
     }
 };

**// Partial specialization, T is used, but in different form: T*  ***
template<typename T>
class Foo<T*>
 {
public:
    
     Foo()
     {
         std::cout << "Foo<T*> called" << std::endl;
     }
 };

int main(int argc, char * argv [])
 {
     Foo<double> foo;
     Foo<int> a;
     Foo<short*> b;
}
```

Output:

>>> FOO<T> CALLED

>>> FOO<INT> CALLED

>>> FOO<T*> CALLED
