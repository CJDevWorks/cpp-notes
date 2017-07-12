# abstract-classes-without-pure-virtual-methods

* What is the difference between the vtable for a class with virtual functions and a class with pure virtual functions?
* Why an entry of pure virtual function in virtual table is required

virtual function table binds with class not object.


Here is the syntax used for a pure virtual declaration:

    virtual void f() = 0;

By doing this, you tell the compiler to reserve a slot for a function in the VTABLE, but not to put an address in that particular slot. Even if only one function in a class is declared as pure virtual, the VTABLE is incomplete.

If the VTABLE for a class is incomplete, what is the compiler supposed to do when someone tries to make an object of that class? It cannot safely create an object of an abstract class, so you get an error message from the compiler. Thus, the compiler guarantees the purity of the abstract class. By making a class abstract, you ensure that the client programmer cannot misuse it.

If you want a class without pure virtual functions to be solely an
abstract class, make the destructor pure virtual:

class Base
{
public:
     void do(){ }
     virtual ~Base() = 0;
};

I.e.: you want a base class for inheritance/polymorphism but don't want
the base class to be instantiateable. 

That way, giving it a pure virtual function makes it an abstract class.
However, you must implement that destructor somewhere, as the compiler
will call it when a derived class’ destructor is called. 


