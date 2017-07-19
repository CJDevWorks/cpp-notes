
## why the size of object has to be 1 byte??


## empty base class optimization

## Exception

Empty base optimization is prohibited if one of the empty base classes is also the type or the base of the type of the first non-static data member, since the two base subobjects of the same type are required to have different addresses within the object representation of the most derived type.

```
#include <cassert>

struct Base {}; // empty class

struct Derived1 : Base {
    int i;
};

struct Derived2 : Base {
    Base c; // Base, occupies 1 byte, followed by padding for i
    int i;
};

struct Derived3 : Base {
    Derived1 c; // derived from Base, occupies sizeof(int) bytes
    int i;
};

int main()
{
    // empty base optimization does not apply,
    // base occupies 1 byte, Base member occupies 1 byte
    // followed by 2 bytes of padding to satisfy int alignment requirements
    assert(sizeof(Derived2) == 2*sizeof(int));

    // empty base optimization does not apply,
    // base takes up at least 1 byte plus the padding
    // to satisfy alignment requirement of the first member (whose
    // alignment is the same as int)
    assert(sizeof(Derived3) == 3*sizeof(int));
}

```