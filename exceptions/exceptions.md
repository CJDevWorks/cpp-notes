# exceptions




**Throwing objects**

Throw a pointer to the object?? That would mean capture by pointer
 - what if an exception is raise while allocating object.
 - how to clean up that object.

what about throwing by value and capturing by value.
    - copy constructor called.
    - slicing for po;ymorphic objects.

The conclusion is that exceptions should be thrown by value, and caught by (usually const) reference.


**What happens when we allocate this object with new and it throws exception?**

- Memory for the object is allocated
- The object's constructor throws an exception
- The object was not instantiated due to the exception
- The memory occupied by the object is deleted
- The exception is propagated, until it is caught

```
// Original code: Fred* p = new Fred();
Fred* p;
void* tmp = operator new(sizeof(Fred)); // 1. allocation via operator new same as malloc
try {
new(tmp) Fred(); // 2. Placement new to construct object
p = (Fred*)tmp; // 3. The pointer is assigned only if the ctor succeeds
}
catch (...) {
operator delete(tmp); // Deallocate the memory
throw; // Re-throw the exception
}
return p;
```


**Exception guarantee**


1. **No-throw guarantee**, also known as failure transparency: Operations are guaranteed to succeed and satisfy all requirements even in exceptional situations. If an exception occurs, it will be handled internally and not observed by clients.

Very difficult or impossible to implement, since memory allocation may fail and throw an exception. Handling allocation failure would then be problematic, since repeated attempts are also likely to fail.

        **noexcept, noexcept(true), throw()**

The function does not throw an exception. However, if an exception is thrown out of a function marked throw(), the Visual C++ compiler calls std::terminate, not std::unexpected

1. **Strong exception safety**, also known as commit or rollback semantics: Operations can fail, but failed operations are guaranteed to have no side effects, so all data retain their original values.[4]

Can be implemented fairly easily by doing any allocation first and then copying into a temporary buffer that is eventually swapped if no errors are encountered. In this case, insertion of x into v will either succeed, or v will remain unchanged.

1. **Basic exception safety, also known as a no-leak guarantee:** Partial execution of failed operations can cause side effects, but all **invariants are preserved and no resources are leaked**. Any stored data will contain valid values, even if they differ from what they were before the exception.

Implemented by ensuring that the size field is guaranteed to be updated if x is successfully inserted. Also, all allocations need to be handled in a way that prevents any chance of a memory leak, regardless of failure.

4. No exception safety: No guarantees are made.

Usually, at least basic exception safety is required to write robust code. Higher levels of safety can sometimes be difficult to achieve, and might incur an overhead due to extra copying.

Implementation in which an insertion failure might lead to corrupted content in v, an incorrect size value, or a memory leak.

throw(Type)

throw(...)

exception specification is deprecated : now just noexcept(true)/noexcept(false)
