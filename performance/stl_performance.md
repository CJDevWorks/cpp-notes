
#### qsort/bsearch VS std_sort with lambda

```
void qsort (void* base, size_t num, size_t size,
            int (*compar)(const void*,const void*));

void* bsearch (const void* key, const void* base,
               size_t num, size_t size,
               int (*compar)(const void*,const void*));


// sort using a standard library compare function object - descending order
    std::sort(s.begin(), s.end(), std::greater<int>());
```

**Reason** : inlining for functors lambdas

- a.empty() instead of a.size() == 0,
- iter != a.end() instead of iter < a.end()
- call distance(iter1, iter2) instead of iter2 - iter1

vector still has the lowest space overhead (as long as there is no excess capacity) and the greatest locality of reference.

- use container functions rather than their generic overheads .
find() vs container find, list.sort

- for a sorted range use : std::lower_bound/std::upper_bound/equal_range/binary_search
in place of generic find, for associative container use their find. std::equal_range better than std::lowe_bound/upper_bound (first validate return pointer then validate values equal, iterator equal)

- helper function in class should be static?? make normal function put them in a namespace
if its a non static member function then this will be passed

- use insert to append a sequence of elements, push_back for one element, back_inserter for a seq of number.

- std::forward_list : is singly linked list.

