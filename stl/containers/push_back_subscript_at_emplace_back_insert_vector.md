
**std::vector::capacity**

Returns the number of elements that the container has currently allocated space for.

**std::vector::size**

Returns the number of elements in the container, i.e. std::distance(begin(), end()).

**std::vector::resize**

- Resizes the container to contain count elements.
- If the current size is greater than count, the container is reduced to its first count elements.
value initialized.
- Vector capacity is never reduced when resizing to smaller size because that would invalidate all iterators

**reserve(size_t)**

- Increase the capacity of the vector to a value **that's greater or equal to new_cap**.
- If new_cap is greater than the current capacity(): new storage is allocated, all iterators, including the past-the-end iterator, and all references to the elements are invalidated
- If new_cap is not greater than capacity():  method does nothing.  no iterators or references are invalidated.

### operator[]() and at()

vector<T>::at(), is required to perform bounds checking to ensure that the vector actually contains the requested element.

vector<T>::operator[]() is allowed, but not required, to perform bounds checking.  - Implenentation
specific - thats for performance.

```
void f( vector<int>& v )
{
  v[0];      // A
  v.at(0);   // B
}
```

Whats the outcome ???
- if v is not empty then there is no difference between lines A and B.
- if v is empty line B is guaranteed to throw a std::out_of_range exception, but there's no telling what line A might do.

### size() Vs capacity()
capacity >= size. Capacity will grew as per implementation (in reallocation - generally exponentially).


### capacity() Vs reserve()

```
vector<int> v;
v.reserve( 2 );
```


### resize() Vs reserve()

resize will impact size and capacity(if its greater). shrink for actual elements
reserve will impact capacity(if its greater). Both never shrink for memory.

**There's a big difference between size() (which goes with resize()) and capacity() (which goes with reserve()):**

- size() tells you how many elements are currently actually present in the container, and resize() adjusts the actual contents of the container to be the specified size by adding or removing elements at the end. Both functions are available for list, vector, and deque, not other containers.

- capacity() tells you how many **elements have room** before adding another would force the vector to allocate more space, and r**eserve() grows (never shrinks) into a larger internal buffer** if necessary to ensure at least the specified space is available. Both functions are available only for vector.

### shrink a vector/string

see swap-trick-for-shrink-to-fit