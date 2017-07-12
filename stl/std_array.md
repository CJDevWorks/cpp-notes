# std::array

template< class T, std::size_t N > struct array;


- std::array is a container that encapsulates fixed size arrays.

- This container is an aggregate type with the same semantics as a struct holding a C-style array T[N] as its only non-static data member.

**Unlike a C-style array, it doesn't decay to T* automatically.**

- As an aggregate type, it can be initialized with aggregate-initialization given at most N initializers that are convertible to T: std::array<int, 3> a = {1,2,3};

###Vs std::vector

Use std:array as a secure, efficient, and convenient alternative to built-in arrays and vectors for your fixed-sized sequences.

- size is fixed at compile time so cant grow.
- allocation and deallocation for vector is time consuming, std::array will not have such problems.
- Its created on stack so don't create large size std::array. small "array" (under 100 elements say) - (a typical stack is about 8MB, so don't allocate more than a few KB on the stack or less if your code is recursive)

- scope of std::array is not as std::vector which is created on heap.

- constexpr size_type size() const noexcept;
- constexpr bool empty() const noexcept;
- like vector has iterators and typedefs

**constructor**
(implicitly declared)

initializes the array following the rules of aggregate initialization (note that default initialization may result in indeterminate values for non-class T)

**destructor**
(implicitly declared)

destroys every element of the array

**operator=**
(implicitly declared)

overwrites every element of the array with the corresponding element of another array
