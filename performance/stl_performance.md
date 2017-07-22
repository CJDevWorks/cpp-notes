
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