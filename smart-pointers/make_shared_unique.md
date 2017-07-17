**make_unique**

```
template< class T, class... Args >
unique_ptr<T> make_unique(Args&&... args )
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...))
}
```

Three reasons.

**Reason 1 Exception safety**
```
void foo(std::shared_ptr<A> a, int priority);

int getPriority();
{
    foo(std::shared_ptr<A>(new A()), getPriority()); // this can cause a leak if "new A()" is called followed by getPriority() which throws an exception.
}
```

General rule of thumb

```
a) Either use std::make_shared<A>() or always use a named shared_ptr
{
    std::shared_ptr<A> spA(new A());
    foo(spA, getPriority);
}

OR

b)
{
       foo(std::make_shared<A>(), getPriority());
}
```

Same applies for make_unique

**Reason 2 Less typing**

```
auto spA(std::make_shared<A>()); // A is used once. vs
std::shared_ptr<A> spA (new A()); // A is used twice here.
Same applies for make_unique
```

**Reason 3 More effecient (only make shared)**

```
std::shared_ptr<A> spA (new A());  --> needs two memory allocations, one for shared_ptr control block and one for resource A

auto spA(std::make_shared<A>()); --> needs one resource allocation, combined for both control block and for resource A.
```

**Downside**

1) Cannot use custom deleters (make_unique/make_shared)
2) When braced initilizer is passed as argument the make function iternaly make this a paranthesis.
So if that impacts different constructor getting called dont use it. Use auto type deduction to create astd::initializer list and then pass it to make on it.

**make_shared only** -

3) Cannot delete the control block even if there is no shared_ptr exists. This is because even if one weak_ptr exists, then the control block cannot be destroyed. The object will be destroyed but control block will not be released (therefore in system where object size is big, memory can't be reused).

3) For classes which define there own new and delete - calling make_shared on them doesn't make sense. As make_shared allocates memnory for object and control block


