
Is it safe to delete the same pointer twice?

No! (Assuming you didn’t get that pointer back from new in between.)
Undefined behaviour
The C++ language guarantees that delete p will do nothing if p is null.

```
// Original code: delete p;
if (p) {    // or "if (p != nullptr)"
  p->~Fred();
  operator delete(p);
}
```

why delete operator doesn't null out the value
One reason is that the operand of delete need not be an lvalue.
    delete p+1;
    delete f(x);

If you consider zeroing out pointers important, consider using a destroy function:

    template<class T> inline void destroy(T*& p) { delete p; p = 0; }

Note that passing the pointer as a reference (to allow the pointer to be nulled out) has the added benefit of preventing destroy() from being called for an rvalue:

    int* f();
    int* p;
    // ...
    destroy(f());   // error: trying to pass an rvalue by non-const reference
    destroy(p+1);   // error: trying to pass an rvalue by non-const reference


#####Why should I use new instead of trustworthy old malloc()?

First, make_unique (or make_shared) are nearly always superior to both new and malloc() and completely eliminate delete and free().

Having said that, benefits of using new instead of malloc are:

**Constructors/destructors**: unlike malloc(sizeof(Fred)), new Fred() calls Fred’s constructor. Similarly, delete p calls *p’s destructor.

**Type safety**: malloc() returns a void* which isn’t type safe. new Fred() returns a pointer of the right type (a Fred*).

**Overridability**: new is an operator that can be overridden by a class, while malloc() is not overridable on a per-class basis.

##### In p = new Fred(), does the Fred memory “leak” if the Fred constructor throws an exception?

No.

If an exception occurs during the Fred constructor of p = new Fred(), the C++ language guarantees that the memory sizeof(Fred) bytes that were allocated will auto-magically be released back to the heap.

Here are the details: new Fred() is a two-step process:

sizeof(Fred) bytes of memory are allocated using the primitive void* operator new(size_t nbytes). This primitive is similar in spirit to malloc(size_t nbytes). (Note, however, that these two are not interchangeable; e.g., there is no guarantee that the two memory allocation primitives even use the same heap!).
It constructs an object in that memory by calling the Fred constructor. The pointer returned from the first step is passed as the this parameter to the constructor. This step is wrapped in a try … catch block to handle the case when an exception is thrown during this step.
Thus the actual generated code is functionally similar to:

```
// Original code: Fred* p = new Fred();
Fred* p;
void* tmp = operator new(sizeof(Fred));
try {
  new(tmp) Fred();  // Placement new
  p = (Fred*)tmp;   // The pointer is assigned only if the ctor succeeds
}
catch (...) {
  operator delete(tmp);  // Deallocate the memory
  throw;                 // Re-throw the exception
}
```

The statement marked “Placement new” calls the Fred constructor. The pointer p becomes the this pointer inside the constructor, Fred::Fred().

whats happens when you have multiple data members, and one of them throws exception during construction.
- As the object is not constructed its destructor will be not called.
- the destructors of base classes and member variables will be called!
- There is no way to identify which of the data member throw exception (unless there is try..catch at every step), in such scenarion RAII becomes usefull.

##### After p = new Fred[n], how does the compiler know there are n objects to be destructed during delete[] p?
Implementation dependent but :
Popular techniques are:

 - Over-allocate the array and put n just to the left of the first Fred object.
 - Use an associative array with p as the key and n as the value.


##### How can I force objects of my class to always be created via new rather than as local, namespace-scope, global, or static?
Make all constructors private - (undefined Vs deleted) : use deleted
Make sure your constructors are in the protected section if you expect Your class will be derived.
