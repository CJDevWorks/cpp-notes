Three reasons.

Reason 1 Exception safety.
--------------------------
void foo(std::shared_ptr<A> a, int priority);

int getPriority();
{
    foo(std::shared_ptr<A>(new A()), getPriority()); // this can cause a leak if "new A()" is called followed by getPriority() which throws an exception.
}
General rule of thumb
a) Either use std::make_shared<A>() or always use a named shared_ptr
{
    std::shared_ptr<A> spA(new A());
    foo(spA, getPriority);
}
OR
b) {
       foo(std::make_shared<A>(), getPriority());
}

Reason 2 Less typing
--------------------
auto spA(std::make_shared<A>()); // A is used once. vs
std::shared_ptr<A> spA (new A()); // A is used twice here.

Reason 3 More effecient
----------------------
std::shared_ptr<A> spA (new A());  --> needs two memory allocations, one for shared_ptr control block and one for resource A

auto spA(std::make_shared<A>()); --> needs one resource allocation, combined for both control block and for resource A.


Downside
--------
1) Cannot use custom deleters
2) Cannot delete the control block even if the no shared_ptr exists. This is because even if one weak_ptr exists, then the control block cannot be destroyed.


**make_unique**

```
template< class T, class... Args >
unique_ptr<T> make_unique(Args&&... args )
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...))
}
```