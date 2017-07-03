# Reference Collapsing

Pre-requirement :
 1. Template type-deduction rules (forward references)
 2. references to references are illegal in C++ (this restriction is not on compiler)
 ```
    int x =10;
    auto& &rx=s; // illegal
 ```

 But compiler may produce them in some context and then collapse them. reference collapsing rule:

 ```
    * If either reference is lvalue : result ==> lvalue
    * if both reference rvalue : result ==> rvalue
 ```

This is the basis of how std::forward works. (conditional typecasting - if actual type passed to original function is
rvalue then std::forward inside that function will typecast it to rvalue)

Check - how std_forward_works

#### Reference collapsing occurs in four contexts:

- template instantiation : Discussed above

- auto type generation : Same rule as template instantiation

```
class Widget {};
Widget widgetFactory() { return Widget(); }  // function returning rvalue
template<typename T>
void func(T&& param) {}

Widget w;                // a variable (an lvalue)
func(w);                 // call func with lvalue; T deduced to be Widget&
func(widgetFactory());   // call func with rvalue; T deduced // to be Widget

auto&& w1 = w;   // lvalue
auto&& w2 = widgetFactory(); // rvalue
```

- decltype : Same rule as auto

- creation and use of typedefs and alias declarations,

```
template<typename T>
class Widget {
public:
  typedef T&& ColapsingRefTot;
};

Widget<int&> w; // in this case iys typedef int& ColapsingRefTot
```