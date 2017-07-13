# default-and-value-initialization

Default initialize : (leaves the object's value indeterminate)

**Syntax**

```
T object ;
new T ;
new T ( ) ; // until C+03
```

if T is a non-POD (until C++11) class type, the constructors are considered and subjected to overload resolution against the empty argument list. The constructor selected (which is one of the default constructors) is called to provide the initial value for the new object;

```
int plain_int;
int c_style_array[13];
std::array<int, 13> cxx_style_array;
Foo foo;
```

Value Initialize: (initialize all elements to T{})

**Syntax**

```
T();
new T ();
Class::Class(...) : member() { ... }
T object {};
T{};
new T {};
Class::Class(...) : member{} { ... }
```


```
int plain_int{};
int c_style_array[13]{};
std::array<int, 13> cxx_style_array{};
Foo foo = Foo()
```

Implicitly defined (by the compiler) default constructor of a class does not initialize members of built-in types.
 Its default initialized


```
class Foo
{
public:
     int x;
};
```

```
Foo foo; // x contains garbage - default initialize
Foo foo = Foo(); // x = 0 // value initialize
Foo* foo = new Foo(); // foo->x = 0  // value initialize the class not the default constructor
```



