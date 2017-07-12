**Do not invoke virtual functions from constructors or destructors**

See order of construction and destruction. Therefore the vtable is pointing to the object(subobject under constrction - it can be base intermediate or final).
Due to this actual override will not be called.

Exceptions:

1. Because valid use cases exist that involve calling (non-pure) virtual functions from the constructor of a class, it is permissible to call the virtual function with an explicitly qualified ID.

```

struct A {
  A() {
    // f();   // WRONG!
    A::f();   // Okay
  }
  virtual void f();
};
```

2. It is permissible to call a virtual function that has the final virt-specifier from a constructor or destructor, as in this example.

```
struct A {
  A();
  virtual void f();
};

struct B : A {
  B() : A() {
    f();  // Okay
  }
  void f() override final;
};

```

3. it is permissible to call a virtual function from a constructor or destructor of a class that has the final class-virt-specifier,

```

struct A {
  A();
  virtual void f();
};

struct B final : A {
  B() : A() {
    f();  // Okay
  }
  void f() override;
};
```