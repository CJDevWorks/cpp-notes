
The 'range-based for' (i.e. foreach style) for loops provide C++11 with a simple for-each style loop syntax. It works with both the STL collection classes (hiding the complexity of using the STL iterator's manually), as well as with plain C arrays, and can be made to work with any custom classes as well (see Using with your own collection classes below).


- Use auto when you want to work with a copy of elements in the range.
- Use auto& when you want to modify elements in the range in non-generic code.
in generic code of the contsiner is a proxy type then its a problem

- Use auto&& when you want to modify elements in the range in generic code.
 To elaborate, auto&& is a forwarding reference, also known as a universal reference. It behaves as follows:

When initialized with an lvalue, it creates an lvalue reference.
When initialized with an rvalue, it creates an rvalue reference.

- Use const auto& when you want read-only access to elements in the range (even in generic code).


Limitations

There are some limitations when using the range-based for-loop:

If you're used to iterating arrays by index, you no longer have that index if you need it for something (i.e. avoiding the trailing comma when outputting a comma-separated list, or just outputting the first N elements). You can of course track separately a count, but then you lose some of the conciseness gains.

If you want to iterate a collection backwards, there's no simple standard way in C++11 to do that with the 'ranged-based for'. You can use boost, which provides an adaptor so that you can do for (int y : boost::adaptors::reverse(x)), or you can create such an adaptor yourself. Or you can just use the old syntax with rbegin() and rend() in this case and at least still benefit from using auto.


**Using 'range-based for' on your own collection classes**

Adding begin() + end() class member functions

The simplest way is to define begin() + end() member functions. The variable returned by these needs to:

- be incrementable, such that incrementing the value returned by begin() will eventually result in a value that matches the value returned by end()
- return a sensible value corresponding to the when operator* is applied to it


- if creating an custom iterator class for this variable, to fulfil this, the following three operators need to be fined:
    - the prefix increment operator – T& operator++()
    - the != comparison operator – bool operator!=(const T& t)const
    - for dereferencing to return the value – T& operator*()

One thing to note – begin() and end() will be called just once at the start of the loop, rather than every loop iteration.
