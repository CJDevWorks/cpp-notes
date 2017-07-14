# casting

Prefer C++style casting over old-style, C casts and generally, try to
avoid casting, especially dynamic_cast<> as it has very poor
performance.

static_cast<type>(object) // Casts an object between similar types, e.g.
int to double

reinterpret_cast<type>(object) // Casts an object from a completely
different type to another type, e.g. class Foo() { } to char* 

dynamic_cast<type>(object) // Casts between inheritance hierarchies,
e.g. from Base pointer to Derived to Derived pointer

const_cast<type>(object) // Casts a way the const of an object
const_cast of a object which actualy is a const : results are undefined.

const int a = 10;
const int& refA = a;
int a_cast = const_cast<int&>(refA)

**reinterpret_cast**

reinterpret_cast<Type>(expression)

- reinterpret_cast casts a pointer to any other type of pointer.
- It also allows casting from a pointer to an integer type and vice versa.

- This operator can cast pointers between non-related classed. The operation results is a simple binary copy of the value from one pointer to the other. The content pointed does not pass any kind of check nor transformation between types.

In the case that the copy is performed from a pointer to an integer, the interpretation of its content is system dependent and therefore any implementation is non portable. A pointer casted to an integer large enough to fully contain it can be casted back to a valid pointer.

class A {};
class B {};
A * a = new A;
B * b = reinterpret_cast<B*>(a);

- reinterpret_cast treats all pointers exactly as traditional type-casting operators do.

**static_cast**

- static_cast performs any casting that can be implicitly performed as well as the inverse cast (even if this is not allowed implicitly).
- Applied to pointers to classes, that is to say that it allows to cast a pointer of a derived class to its base class (this is a valid conversion that can be implicitly performed) and it can also perform the inverse: cast a base class to its derivated class.

In this last case the base class that is being casted is not checked to determine wether this is a complete class of the destination type or not.

class Base {};
class Derived: public Base {};
Base * a = new Base;
Derived * b = static_cast<Derived*>(a);
static_cast, aside from manipulating pointers to classes,

can also be used to perform conversions explicitly defined in classes, as well as to perform standard conversions between fundamental types:
double d=3.14159265;
int i = static_cast<int>(d);
dynamic_cast

dynamic_cast is exclusively used with pointers and references to objects. It allows any type-casting that can be implicitly performed as well as the inverse one when used with polymorphic classes, however, unlike static_cast, dynamic_cast checks, in this last case, if the operation is valid. That is to say, it checks if the casting is going to return a valid complete object of the requested type.
Checking is performed during run-time execution. If the pointer being casted is not a pointer to a valid complete object of the requested type, the value returned is a NULL pointer.

class Base { virtual dummy(){}; };
class Derived : public Base { };

Base* b1 = new Derived;
Base* b2 = new Base;
Derived* d1 = dynamic_cast<Derived*>(b1);   // succeeds
Derived* d2 = dynamic_cast<Derived*>(b2);   // fails: returns NULL
If the type-casting is performed to a reference type and this casting is not possible an exception of type bad_cast is thrown:

class Base { virtual dummy(){}; };
class Derived : public Base { };

Base* b1 = new Derived;
Base* b2 = new Base;
Derived d1 = dynamic_cast<Derived&*>(b1);   // succeeds
Derived d2 = dynamic_cast<Derived&*>(b2);   // fails: exception thrown
const_cast

This type of casting manipulates the const attribute of the passed object, either to be set or removed:
class C {};
const C * a = new C;
C * b = const_cast<C*> (a);
Neither of the other three new cast operators can modify the constness of an object.

