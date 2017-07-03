Effective C++
*********************************************************************************************************************************************
**_Item 2: Prefer consts, enums, and inlines to #defines_**

there's no way to create a class-specific constant using a #define, because #defines don't respect scope.
Once a macro is defined, it's in force for the rest of the compilation (unless it's #undefed
somewhere along the line). Which means that not only can't #defines be used for class-specific constants,
they also can't be used to provide any kind of encapsulation, i.e., there is no such thing as a “private” #define.
Of course, const data members can be encapsulated;

```
// call f with the maximum of a and b
#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))

CALL_WITH_MAX(++a, b);          // a is incremented twice
CALL_WITH_MAX(++a, b+10);       // a is incremented once

template<typename T>                               // because we don't
inline void callWithMax(const T& a, const T& b)    // know what T is, we
{                                                  // pass by reference-to-
  f(a > b ? a : b);                                // const — see Item 20
}
```

* Unlike when using a #define, if an error occurs when using a constant, then its name is included in the error message.
* For a constant pointer in the header file, declare both the pointer and the data it points to as const.
* In-class initialization is allowed only for integral types, and only for constants.
* When using a macro, remember to parenthesize all the arguments, and beware expressions being evaluated multiple times if used as arguments.

**_Item 3: Use const whenever possible_**

char *p = greeting;                    // non-const pointer,
                                       // non-const data

const char *p = greeting;              // non-const pointer,
                                       // const data

char * const p = greeting;             // const pointer,
                                       // non-const data

const char * const p = greeting;       // const pointer,
                                       // const data

If the word const appears to the left of the asterisk, what's pointed to is constant;
if the word const appears to the right of the asterisk, the pointer itself is constant;
if const appears on both sides, both are constant

--- difference  between const iterator and const_iterator
const std::vector<int>::iterator iter =     // iter acts like a T* const
  vec.begin();
*iter = 10;                                 // OK, changes what iter points to
++iter;                                    // error! iter is const

std::vector<int>::const_iterator cIter =   //cIter acts like a const T*
  vec.begin();
*cIter = 10;                               // error! *cIter is const
++cIter;                                  // fine, changes cIter

const Member Functions --

mutable frees non-static data members from the constraints of bitwise constness:

Avoiding Duplication in const and Non-const Member Functions.
1. cast *this to const reference.
2. call const function.
3. remove constantness from that function.

class TextBlock {
public:

  ...

  const char& operator[](std::size_t position) const     // same as before
  {
    ...
    ...
    ...
    return text[position];
  }

  char& operator[](std::size_t position)         // now just calls const op[]
  {
    return
      const_cast<char&>(                         // cast away const on
                                                 // op[]'s return type;
        static_cast<const TextBlock&>(*this)     // add const to *this's type;
          [position]                            // call const version of op[]
      );
  }

...

};

const return type ---


const arguments --


 mutable frees non-static data members from the constraints of bitwise constness:
 * Using const is wonderful because it allows the compiler to enforce a semantic constraint.
 * Declaring an iterator const means it isn't allowed to point to something different, but whatever it points to may be modified.
 * One of the hallmarks of good user-defined types is that they avoid gratuitous incompatibilities with built-in types.
 * A const member function can overload a non-const member function, and the former will be used on constobjects.
 * Bitwise const is C++'s definition of const. Logical const is when bits in the object are changed, but in ways that the client cannot detect.
 * The mutable keyword frees non-static data members from the constraints of bitwise const.
 * By calling static_cast to add const to this, and then const_cast to remove const from the return value, the overloaded non-const function can call the const one.

 4. **_Make sure that objects are initialized before they're used:**_

 the relative order of initialization of non-local static objects defined in different translation units is undefined. There is a reason for this. Determining the “proper” order in which to initialize non-local static objects is hard. Very hard. Unsolvably hard. In its most general form — with multiple translation units and non-local static objects generated through implicit template instantiations (which may themselves arise via implicit template instantiations) — it's not only impossible to determine the right order of initialization, it's typically not even worth looking for special cases where it is possible to determine the right order.

Fortunately, a small design change eliminates the problem entirely. All that has to be done is to move each non-local static object into its own function, where it's declared static. These functions return references to the objects they contain. Clients then call the functions instead of referring to the objects. In other words, non-local static objects are replaced with local static objects.

 * Reading uninitialized values yields undefined behavior, so always initialize objects before you use them.
 * Always listing every data member on the initialization list avoids having to remember which data members may go uninitialized.
 * Within a class, data members are initialized in the order they're declared, and not in their order on the initialization list.
 * If a non-local static object in one translation unit uses a non-local static object in another translation unit, it may be uninitialized, because their initialization order is undefined.
 * Using static objects defined in functions eliminates this problem, and if you never call such a function, you don't even construct its static object.

 Item 5: Know what functions C++ silently writes and calls

 class Empty {
public:
  Empty() { ... }                            // default constructor
  Empty(const Empty& rhs) { ... }            // copy constructor

  ~Empty() { ... }                           // destructor — see below
                                             // for whether it's virtual

  Empty& operator=(const Empty& rhs) { ... } // copy assignment operator
};

 Note that the generated destructor is non-virtual (see Item 7) unless it's for a class inheriting from a base class that itself declares a virtual destructor (in which case the function's virtualness comes from the base class).

if constructor is declared in NamedObject, compilers won't generate a default constructor.

 As for the copy constructor and the copy assignment operator, the compiler-generated versions simply copy each non-static data member of the source object over to the target object.

 in general, compiler-generated copy assignment operators behave as I've described only when the resulting code is both legal and has a reasonable chance of making sense.

 template<class T>
class NamedObject {
public:
  // this ctor no longer takes a const name, because nameValue
  // is now a reference-to-non-const string. The char* constructor
  // is gone, because we must have a string to refer to.
  NamedObject(std::string& name, const T& value);

  ...                               // as above, assume no
                                    // operator= is declared
private:
  std::string& nameValue;           // this is now a reference
  const T objectValue;              // this is now const
};

Finally, compilers reject implicit copy assignment operators in derived classes that inherit
from base classes declaring the copy assignment operator private.

* A compiler declares a copy constructor, copy assignment operator, and destructor if you don't declare them yourself, as well as a default constructor if you declare none.
* The generated destructor is not virtual unless the class inherits from a base class with a virtual destructor.
* You must define the copy constructor yourself if the class contains a reference member or a const member.


6. Explicitly disallow the use of compiler-generated functions you do not want
boost::noncopyable

 class Uncopyable {
protected:                                   // allow construction
  Uncopyable() {}                            // and destruction of
  ~Uncopyable() {}                           // derived objects...

private:
  Uncopyable(const Uncopyable&);             // ...but prevent copying
  Uncopyable& operator=(const Uncopyable&); // declarations only
};

class HomeForSale: private Uncopyable {     // class no longer
  ...                                       // declares copy ctor or
};

[declarations only]
 The scheme isn't foolproof, because member and friend functions can still call your private
 functions. Unless, that is, you are clever enough not to define them. Then if somebody
 inadvertently calls one, they'll get an error at link-time.
 This trick — declaring member functions private and deliberately not implementing them is so well
 established, it's used to prevent copying in several classes in C++'s iostreams library.

[why base class]
It's possible to move the link-time error up to compile time (always a good thing — earlier
error detection is better than later) by declaring the copy constructor and copy assignment
operator private not in HomeForSale itself, but in a base class specifically designed to prevent copying.
The base class is simplicity

 inheritance from Uncopyable needn't be public[item 32]
 Uncopyable's destructor need not be virtual (see Item 7)
 it's eligible for the empty base class optimization (Item 39)
* Declare the copy constructor and the copy assignment operator private to prevent the compiler from generating its own version.
* To stop member and friend functions from still calling them, don't actually define them; this generates an error during the linking stage.

 Item 7: Declare destructors virtual in polymorphic base classes

 Polymorphic base classes should declare virtual destructors.
 If a class has any virtual functions, it should have a virtual destructor.

 [except]
 Sometimes, however, you have a class that you'd like to be abstract, but you don't have any
 pure virtual functions. What to do? Well, because an abstract class is intended to be used
 as a base class, and because a base class should have a virtual destructor, and because a pure
 virtual function yields an abstract class, the solution is simple: declare a pure virtual
 destructor in the class you want to be abstract. Here's an example:

Classes not designed to be base classes or not designed to be used polymorphically should not
declare virtual destructors.

The same analysis applies to any class lacking a virtual destructor, including all the STL container
types (e.g., vector, list, set, tr1::unordered_map (see Item 54), etc.). If you're ever tempted
to inherit from a standard container or any other class with a non-virtual destructor, resist the temptation!
(Unfortunately, C++ offers no derivation-prevention mechanism akin to Java's final classes or C#'s sealed classes.)

[defining a final class]
It relies on the fact that the most derived class in a hierarchy must construct a virtual base. For example:

class Usable;

class Usable_lock {
friend class Usable;
private:
Usable_lock() {}
Usable_lock(const Usable_lock&) {}
};

class Usable : public virtual Usable_lock {
// ...
public:
Usable();
Usable(char*);
// ...
};

Usable a;

class DD : public Usable { };

DD dd;  // error: DD::DD() cannot access
        // Usable_lock::Usable_lock(): private  member

[creating objects on stack only]


[creating objects on heap only]

* When a derived class object is deleted through a pointer to the base class with a non-virtual destructor, results are undefined, but typically the derived part isn't destroyed.
* If the class isn't intended to be a base class, making the destructor virtual increases its size, as this adds a vptr(virtual table pointer) and vtbl (virtual table).
* The string class and STL container types (vector, list, set, etc.) lack virtual destructors, and so should never be inherited from.

Item 8: Prevent exceptions from leaving destructors
* Depending on the circumstances, if two destructors simultaneously emit exceptions, program execution either terminates or yields undefined behavior.
* One option is to terminate the program in the destructor, thereby preventing any undefined behavior.
* The second option is to swallow the exception, but only if the program can reliably continue after the exception was ignored.
* Good practice is to try and move the operation that can generate an exception to outside the destructor.

When the vector v is destroyed, it is responsible for destroying all the Widgets it contains.
Suppose v has ten Widgets in it, and during destruction of the first one, an exception is
thrown. The other nine Widgets still have to be destroyed (otherwise any resources they hold
would be leaked), so v should invoke their destructors. But suppose that during those calls,
a second Widget destructor throws an exception. Now there are two simultaneously active
exceptions, and that's one too many for C++. Depending on the precise conditions under which
such pairs of simultaneously active exceptions arise, program execution either terminates or
yields undefined behavior. In this example, it yields undefined behavior.

There are two primary ways to avoid the trouble.
Terminate the program
Swallow the exception

class DBConn {
public:
  ...

  void close()                                     // new function for
  {                                                // client use
    db.close();
    closed = true;
  }

  ~DBConn()
   {
   if (!closed) {
   try {                                            // close the connection
     db.close();                                    // if the client didn't
   }
   catch (...) {                                    // if closing fails,
     make log entry that call to close failed;   // note that and
     ...                                             // terminate or swallow
   }
  }

private:
  DBConnection db;
  bool closed;
};

Item 9: Never call virtual functions during construction or destruction
* During base class construction, virtual function calls never go down into a derived class, because an object is not of a derived class until its constructor begins execution.
* The same reasoning applies during destruction.
* You must ensure that your constructors or destructors don't call virtual functions, and that all the functions they call obey the same constraint.

Don't call virtual functions during construction or destruction, because such calls will
never go to a more derived class than that of the currently executing constructor or destructor.

since you can't use virtual functions to call down from base classes during construction, you can compensate by
having derived classes pass necessary construction information up to base class constructors instead.


 class Transaction {
public:
  explicit Transaction(const std::string& logInfo);

  void logTransaction(const std::string& logInfo) const;   // now a non-
                                                           // virtual func
  ...
};

Transaction::Transaction(const std::string& logInfo)
{
  ...
  logTransaction(logInfo);                                // now a non-
}                                                         // virtual call

class BuyTransaction: public Transaction {
public:
 BuyTransaction( parameters )
 : Transaction(createLogString( parameters ))             // pass log info
  { ... }                                                 // to base class
   ...                                                    // constructor

private:
  static std::string createLogString( parameters );
};

[Virtual constructor Idiom]

Item 10: Have assignment operators return a reference to *this
* This is what all built-in types do, thereby allowing chained assignments, and it applies to all assignment operators (such as operator+=).

This is only a convention; code that doesn't follow it will compile. However, the convention is followed by all the built-in types as well as by all the types in

int x, y, z;

x = y = z = 15;                        // chain of assignments

class Widget {
public:
  ...
  Widget& operator+=(const Widget& rhs   // the convention applies to
  {                                      // +=, -=, *=, etc.
   ...
   return *this;
  }
   Widget& operator=(int rhs)            // it applies even if the
   {                                     // operator's parameter type
      ...                                // is unconventional
      return *this;
   }
   ...
};


Item 11: Handle assignment to self in operator=
* Code that operates on references or pointers to multiple objects of the same type must consider that the objects might be the same.
* Guard against self-assignment by checking the argument's address against this at the top of operator+=.
* In many cases, a careful ordering of statements can yield code that guards against both exceptions and self-assignment.
* Another alternative that guards against both exceptions and self-assignment is the "copy and swap" technique, which is covered in Item 29.

[assignment of deleted object]
Widget&
Widget::operator=(const Widget& rhs)              // unsafe impl. of operator=
{
  delete pb;                                      // stop using current bitmap
  pb = new Bitmap(*rhs.pb);                       // start using a copy of rhs's bitmap

  return *this;                                   // see Item 10
}

[exception unsafe]
Widget& Widget::operator=(const Widget& rhs)
{
  if (this == &rhs) return *this;   // identity test: if a self-assignment,
                                    // do nothing
  delete pb;
  pb = new Bitmap(*rhs.pb);  /// bang -- if exception

  return *this;
}

[safe ordering is required]
Widget& Widget::operator=(const Widget& rhs)
{
  Bitmap *pOrig = pb;               // remember original pb
  pb = new Bitmap(*rhs.pb);         // point pb to a copy of rhs's bitmap
  delete pOrig;                     // delete the original pb

  return *this;
}

[copy and swap idiom]
Widget& Widget::operator=(const Widget& rhs)
{
  Widget temp(rhs);             // make a copy of rhs's data

  swap(temp);                   // swap *this's data with the copy's
  return *this;
}

Item 12: Copy all parts of an object

* When you add new data members to a class, be sure to update its copy constructor and copy assignment operator accordingly.
* A copying function should copy all local data members, and also invoke the appropriate copying function in all base classes.

Item 13: Use objects to manage resources

[when to use auto_ptr/shared_ptr/weak_ptr/intrusive_ptr]
* A thrown exception or a premature return, continue, or goto statement might preclude execution from eaching a delete statement.
* By putting resources inside objects like auto_ptr, we can rely on C++'s destructor invocation to ensure that the resources are released.
* Resource Acquisition Is Initialization, or RAII, means acquiring a resource and initializing its managing object happen in the same statement.
* Copying an auto_ptr sets it to null. While this enforces an object being managed by only one auto_ptr, you cannot use them in STL containers.
* There is no auto_ptr or shared_ptr for dynamically allocated arrays because you should be using vectorinstead.

Item 14: Think carefully about copying behavior in resource-managing classes

template <class Lockable>
class lock{
public:
    lock(Lockable & m) : mtx(m){
        mtx.lock();
    }
    ~lock(){
        mtx.unlock();
    }
private:
    Lockable & mtx;
};

* For resources that are not heap-based, smart pointers like auto_ptr and shared_ptr are inappropriate as resource handlers.
* Policies for copying an RAII object include prohibiting copying, and reference counting, copying, and transferring ownership of the underlying resource.

Item 15: Provide access to raw resources in resource-managing classes
* An implicit conversion function on the RAII class can make access to the raw resource easier, but this increases the chance of errors.
* Often an explicit conversion function simply named get is preferable, even if clients must explicitly call it each time.
* Returning the raw resource violates encapsulation, but RAII classes don't exist simply to encapsulate it, but to ensure that it is released.

Item 16: Use the same form in corresponding uses of new and delete
If you use [] in a new expression, you must use [] in the corresponding delete expression.
If you don't use [] in a new expression, you mustn't use [] in the corresponding delete expression.

* Using the expression delete when delete [] should be used results in undefined behavior.
* The memory for an array usually includes the size of the array, so that the delete operator knows how many destructors to call.
* Use the same form of new in all constructors that initialize a pointer member, or else you may use the wrong form of delete.
* The string and vector classes largely eliminate the need to dynamically allocate an array.

Item 17: Store newed objects in smart pointers in standalone statements
processWidget(std::tr1::shared_ptr<Widget>(new Widget), priority());

Before processWidget can be called, then, compilers must generate code to do these three things:

Call priority.

Execute “new Widget”.

Call the tr1::shared_ptr constructor.

if sequence -
sequence of operations:

Execute “new Widget”.

Call priority.

Call the tr1::shared_ptr constructor.

std::tr1::shared_ptr<Widget> pw(new Widget);  // store newed object
                                              // in a smart pointer in a
                                              // standalone statement

processWidget(pw, priority());                // this call won't leak


Chapter 4: Designs and Declarations

Item 18: Make interfaces easy to use correctly and hard to use incorrectly
* The type system is your primary ally in preventing undesirable code from compiling.
* Restrict what can be done with a type. A common way to impose restrictions is to add const wherever you can.
* Avoid gratuitous incompatibilities with the built-in types so that interfaces behave consistently, thereby reducing mental friction.
* Any interface that requires clients to remember to do something is prone to incorrect use, because clients can forget to do it.
* In many applications, the additional runtime costs of resource managers are unnoticeable, but the reduction in client errors will be noticed by everyone.

Item 19: Treat class design as type design
* Approach class design with the same care that language designers lavish on the design of built-in types.
* Good types have a natural syntax, intuitive semantics, and one or more efficient implementations.
* If you inherit from existing classes, you are constrained by their design, particularly by whether their functions are virtual or not.
* Guarantees made with respect to performance, exception safety, and resource usage impose constraints on your implementation.
* If you're defining a whole family of types, you don't want to define a new class, you want to define a new class template.
* If you're only subclassing so you can add functionality to an existing class, consider non-member functions or templates instead.


Item 20: Prefer pass-by-reference-to-const to pass-by-value
Prefer pass-by-reference-to-const over pass-by-value. It's typically more efficient and it avoids the slicing problem.

The rule doesn't apply to built-in types and STL iterator and function object types. For them, pass-by-value is usually appropriate.
This same advice applies to iterators and function objects in the STL, because, by convention, they are designed to be passed by value. Implementers of iterators and function objects are responsible for seeing to it that they are efficient to copy and are not subject to the slicing problem
* Passing by reference eliminates the slicing problem, where passing a derived class object to a function that accepts a base class object calls the base class copy constructor.
* References are typically implemented as pointers, so passing built-in types like int by value is usually more efficient.
* Implementers of iterators and function objects ensure that they are efficient to copy and are not subject to the slicing problem.
* Avoid passing a user-defined type by value because while its size may be small now, that is subject to change with its implementation.


Item 21: Don't try to return a reference when you must return an object
* A function should never return a reference or pointer to a local object that is destroyed when the function exits.
* Returning a reference from a function like operator* is incorrect. Such a function must return a new object.
* In some cases the construction and destruction of such a return value can be safely eliminated by the compiler.

Never return a pointer or reference to a local stack object, a reference to a heap-allocated object, or a pointer or reference to a local static object if there is a chance that more than one such object will be needed.

Item 22: Declare data members private
* Many data members should be hidden, and rarely does every data member require a getter and a setter.
* Only functional interfaces makes it easy to notify other objects when variables are read or written, to verify class invariants and function pre- and postconditions, to perform synchronization in threaded environments, etc.
* Public means unencapsulated, which means an unchangeable implementation, especially for classes that are widely used.
* Protected data is as unencapsulated as public data, since changing such a data member could break all derived classes that use it, which is an unknowably large amount of code.

Item 23: Prefer non-member non-friend functions to member functions
* The more functions that can access data, the less the data is encapsulated, and the harder it is to change the characteristics of the data.
* Unlike a member function, a non-member non-friend function doesn't increase the count of functions that can access the private parts of a class.
* Consider putting the non-member function in the same namespace as the class it operates on.
* Partitioning functionality in a namespace across multiple files promotes clean organization, and clients can freely add more functions to the namespace.

Item 24: Declare non-member functions when type conversions should apply to all parameters

class Rational {

  ...                                             // contains no operator*
};
const Rational operator*(const Rational& lhs,     // now a non-member
                         const Rational& rhs)     // function
{
  return Rational(lhs.numerator() * rhs.numerator(),
                  lhs.denominator() * rhs.denominator());
}
Rational oneFourth(1, 4);
Rational result;

result = oneFourth * 2;                           // fine
result = 2 * oneFourth;                           // hooray, it works!

Should operator* be made a friend of the Rational class?

In this case, the answer is no, because operator* can be implemented entirely in terms of Rational's public interface. The code above shows one way to do it. That leads to an important observation: the opposite of a member function is a non-member function, not a friend function. Too many C++ programmers assume that if a function is related to a class and should not be a member (due, for example, to a need for type conversions on all arguments), it should be a friend. This example demonstrates that such reasoning is flawed.

* For overloaded operators, compilers will also look at non-member functions accepting two parameters in the namespace or global scope.
* Parameters are eligible for implicit type conversion only if they are listed on the parameter list. The object on which the member function is invoked is never eligible.
* To support mixed mode arithmetic with operator overloading, make operators non-member functions accepting both operands as arguments.
* The opposite of a member function is a non-member function, not a friend function. Avoid friend functions when you can.

Multiple inheritance :

http://www.drdobbs.com/cpp/multiple-inheritance-considered-useful/184402074?pgno=1


Item 25: Consider support for a non-throwing swap
* If using the "pimp idiom," define a member function named swap that does the actual swapping, then specializestd::swap to call that member function.
* It's okay to totally specialize templates in std, adding new templates, classes, functions, or anything else to stdresults in undefined behavior.
* In addition to the specialization of std::swap, write a non-member version of swap in the same namespace of your class.
* By prefacing a call to swap with using std::swap, compilers will look for the namespace definition first, then the specialization in std, and finally the general form.
Chapter 5: Implementations
Item 26: Postpone variable definitions as long as possible
* Postponing declaring a variable until you have its initialization arguments avoids unnecessary default constructions.
* Assigning a variable defined outside a loop is more efficient than initializing it on ever iteration, because it avoids destructing when each iteration completes.
Item 27: Minimize casting
* Casts can subvert the type system, which is there to ensure that you're not trying to perform any unsafe or nonsensical operations on objects.
* Only use reinterpret_cast for low-level casts in low-level code, such as from a pointer to an int. It yields unportable results.
* Use static_cast to force implicit conversions as well as the reverse of such conversions, with the exception of const to non-const.
* Prefer the explicit, new-style casts. They are easier to search for, and their narrow purpose makes it possible for compilers to diagnose usage errors.
* Type conversions of any kind, either explicit via casts or implicit by compilers, often lead to additional code that is executed at runtime.
* Avoid making assumptions about how things are laid out in C++. Making casts based on such assumptions leads to undefined behavior.
* A dynamic_cast can have a significant runtime cost. If you need to perform derived class operations through a pointer or reference to the base class, explore alternative designs.
* Casts should be isolated as much as possible, typically hidden inside functions whose interfaces shield callers from the work done inside.
Item 28: Avoid returning "handles" to object internals
* A data member is only as encapsulated as the most accessible function returning a reference to it.
* Returning const references to data members can still lead to dangling handles, which refer to parts of objects that don't exist any longer.
* Functions that return a handle to an object internal are the exception and not the rule.
Item 29: Strive for exception-safe code
* Exception-safe functions don't leak resources, and don't allow data structures or objects to enter a corrupted state.
* The basic guarantee ensures that the program remains in a valid state if an exception is thrown, but that exact state may not be predictable. The strong guarantee ensures that the state is unchanged.
* Often you can't guarantee that no exceptions are thrown, because anything that dynamically allocates memory can throw a bad_alloc exception.
* When functions have side-effects on non-local data instead of operating exclusively on local state, it's much harder to offer the strong guarantee.
* If a system has even a single function that's not exception-safe, then the system as a whole is not exception-safe.
* A function's exception-safety guarantee is a visible part of its interface, and you should choose it as deliberately as you choose all other interface aspects.
Item 30: Understand the ins and outs of inlining
* Compiler optimizations are typically designed for stretches of code that lack function calls, so inlining allows more optimizations.
* Inlined code can also lead to additional paging, a reduced instruction cache hit rate, and their accompanying performance penalties.
* The inline keyword is a request that compilers may ignore, and only the most trivial functions that are not virtual may be inlined.
* Even empty constructors and destructors are unlikely to be inlined, as they implicitly call the constructors of base classes and data members.
* Debuggers have trouble with inlined functions. For example, you can't set a breakpoint in a function that isn't there.
Item 31: Minimize compilation dependencies between files
* Instead of trying to forward-declare parts of the standard library, use the proper #include statements and be done with it.
* You never need a class definition to declare a function using that class. Forward declare the class, and shift the burden of including its definition to clients that call the function.
* A class that employs the pimpl idiom is often called a handle class.
* If a function is declared as pure virtual in an interface class, then there is no need to include the keyword virtualin its declaration in the subclass.
* Handle classes and interface classes decouple interfaces from implementations and thereby reduce compilation dependencies between files.
Chapter 6: Inheritance and Object-Oriented Design
Item 32: Make sure public inheritance models "is-a"
* The most important rule in object-oriented programming in C++ is that public inheritance means "is-a".
* There is no one ideal design for all software. The best design depends on what the system is expected to do, both now and in the future.
* Good interfaces prevent invalid code from compiling. Prefer design that rejects operations during compilation than one that rejects at runtime.
* A class named Square extending Rectangle is a classic example of the fragile nature of class hierarchies.
Item 33: Avoid hiding inherited names
* If a function in a derived class has the same name as a function in the base class, it hides all overloaded forms of that function in the base class.
* To preserve the is-a relationship of inheritance, the derived class must include a using declaration to inherit all overloaded forms of a function with a given name.
Item 34: Differentiate between inheritance of interface and inheritance of implementation
* Pure virtual functions must be redeclared by any concrete class that inherits them.
* A simple virtual function allows a derived class to inherit a function interface as well as an implementation.
* A pure virtual function can still have an implementations of its own. A subclass must redeclare it, but it can call down to this "default" implementation.
* A non-virtual function serves a mandatory implementation, and should never be redefined in a derived class.
* Don't blindly declare all member functions virtual, and don't blindly declare all member functions non-virtual. Consider each one individually.
Item 35: Consider alternatives to virtual functions
* When a non-virtual member function calls a private virtual member function, subclasses can redefine the latter. This is a form of the template method design pattern.
* The only way to resolve the need for non-member functions to access the non-public parts of a class is to weaken its encapsulation.
* The tr1::function class can refer to anything that acts like a function and returns a type convertible to the specified type.
* The "standard" strategy pattern offers the possibility that an existing strategy can be tweaked via defining a subclass.
Item 36: Never redefine an inherited non-virtual function
* Non-virtual functions are statically bound, so calling one on a base class pointer or reference uses the base class implementation, and not any derived class implementation.
* A non-virtual function is an invariant over specialization for the base class, and so no derived class should try to redefine it.
* Item 7, which warns against not specifying a virtual destructor in a base class, is a special case of this item.
Item 37: Never redefine a function's inherited default parameter value
* An object's dynamic type is determined by the object to which it currently refers, which in turn determines how it will behave.
* Default parameters are statically bound, so invoking a virtual function defined in a derived class uses a default parameter value from the base class.
* To avoid duplication of the default parameter, use the non-virtual interface idiom, where the default parameter is only defined once in the public non-virtual function.
Item 38: Model "has-a" or "is-implemented-in-terms-of" through composition
* Composition in the application domain expresses a has-a relationship, while in the implementation domain it expresses an is-implemented-in-terms-of relationship.
* Inappropriate subclassing violates the is-a principle, and should be replaced with composition.
Item 39: Use private inheritance judiciously
* With private inheritance, you cannot assign a derived object to a base class pointer, and protected and public members in the base class are private in the derived class.
* Use composition whenever you can, and use private inheritance whenever you must.
* Use private inheritance if two classes don't have an is-a relationship, but one needs to access the protected members or redefine a virtual function in the other.
* If a class privately inherits from another and defines a virtual function, its own subclasses can redefine that function, even if they can't call it.
Item 40: Use multiple inheritance judiciously
* If a function is defined in two base classes, then a call in the derived class to that function is always ambiguous, even if only one definition is accessible.
* Virtual inheritance prevents replicating data in the base class when multiple inheritance is used, but it's slower and creates larger objects.
* The one reasonable of multiple inheritance is to combine public inheritance of an interface with private inheritance of an implementation.
* If the only design you can come up with involves multiple inheritance, you should think a little harder.

Item 41: Understand implicit interfaces and compile-time polymorphism
Both classes and templates support interfaces and polymorphism.
For classes, interfaces are explicit and centered on function signatures. Polymorphism occurs at runtime through virtual functions.
For template parameters, interfaces are implicit and based on valid expressions. Polymorphism occurs during compilation through template instantiation and function overloading resolution.

Item 42: Understand the two meanings of typename
When declaring template parameters, class and typename are interchangeable.
Use typename to identify nested dependent type names, except in base class lists or as a base class identifier in a member initialization list.

Item 43: Know how to access names in templatized base classes
In derived class templates, refer to names in base class templates via a "this->" prefix, via using declarations, or via an explicit base class qualification.

Item 44: Factor parameter-independent code out of templates
Templates generate multiple classes and multiple functions, so any template code not dependent on a template parameter causes bloat.
Bloat due to non-type template parameters can often be eliminated by replacing template parameters with function parameters or class data members.
Bloat due to type parameters can be reduced by sharing implementations for instantiation types with identical binary representations.

Item 45: Use member function templates to accept "all compatible types."
Use member function templates to generate functions that accept all compatible types.
If you declare member templates for generalized copy construction or generalized assignment, you'll still need to declare the normal copy constructor and copy assignment operator, too.

Item 46: Define non-member functions inside templates when type conversions are desired
When writing a class template that offers functions related to the template that support implicit type conversions on all parameters, define those functions as friends inside the class template.

Item 47: Use traits classes for information about types
Traits classes make information about types available during compilation. They're implemented using templates and template specializations.
In conjunction with overloading, traits classes make it possible to perform compile-time if...else tests on types.

48: Be aware of template metaprogramming
Template metaprogramming can shift work from runtime to compile-time, thus enabling earlier error detection and higher runtime performance.
TMP can be used to generate custom code based on combinations of policy choices, and it can also be used to avoid generating code inappropriate for particular types.


49: Understand the behavior of the new-handler
set_new_handler allows you to specify a function to be called when memory allocation requests cannot be satisfied.
Nothrow new is of limited utility, because it applies only to memory allocation; subsequent constructor calls may still throw exceptions.


50: Understand when it makes sense to replace new and delete
There are many valid reasons for writing custom versions of new and delete, including improving performance, debugging heap usage errors, and collecting heap usage information.

51: Adhere to convention when writing new and delete
operator new should contain an infinite loop trying to allocate memory, should call the new-handler if it can't satisfy a memory request, and should handle requests for zero bytes. Class-specific versions should handle requests for larger blocks than expected.
operator delete should do nothing if passed a pointer that is null. Class-specific versions should handle blocks that are larger than expected.

52: Write placement delete if you write placement new
When you write a placement version of operator new, be sure to write the corresponding placement version of operator delete. If you don't, your program may experience subtle, intermittent memory leaks.
When you declare placement versions of new and delete, be sure not to unintentionally hide the normal versions of those functions.

53: Pay attention to compiler warnings.
Take compiler warnings seriously, and strive to compile warning-free at the maximum warning level supported by your compilers.
Don't become dependent on compiler warnings, because different compilers warn about different things. Porting to a new compiler may eliminate warning messages you've come to rely on.

54: Familiarize yourself with the standard library, including TR1
The primary standard C++ library functionality consists of the STL, iostreams, and locales. The C99 standard library is also included.
TR1 adds support for smart pointers (e.g., tr1::shared_ptr), generalized function pointers (tr1::function), hash-based containers, regular expressions, and 10 other components.
TR1 itself is only a specification. To take advantage of TR1, you need an implementation. One source for implementations of TR1 components is Boost.


55: Familiarize yourself with Boost.
Boost is a community and web site for the development of free, open source, peer-reviewed C++ libraries. Boost plays an influential role in C++ standardization.
Boost offers implementations of many TR1 components, but it also offers many other libraries, too.



