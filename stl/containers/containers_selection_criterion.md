# stl-containers

- ENCAPSULATE operations and interactions and use TYPEDEF or USING= to not have to
specify the container everywhere (makes changing later easier).

- Standard STL sequence containers: vector, string, deque and list

- Standard STL associative containers: set, multiset, map, multimap

- Standard non-STL containers: array, stack, queue, priority_queue, vector<bool>, bitset,

```
vector: default
list: frequent insertions and deletions in the middle of the sequence
deque: insertions and deletions at the beginning and end of sequence
```


- Do you need to be able to insert a new element at an any position in the container? 
NO ASSOCIATIVE CONTAINERS

- Do you care about order?
  NO HASHED CONTAINERS

- What iterator categories are required?
 RANDOMACCESSITERATORS -> VECTOR, DEQUE; 
 BIDIRECTIONAL -> LIST, associative container

- Is lookup speed important?
HASHED CONTAINERS, SORTED VECTORS, ASSOCIATE CONTAINERS.

- Do you need to minimize iterator invalidation? - NODE-BASED CONTAINERS. 



**Iterator Invalidation :**

CONTIGUOUS-MEMORY CONTAINERS store items sequentially, contiguously in
dynamically allocated chunks of memory, like an array. More than one
item is stored per chunk, so insertions and deletions effect other
elements and require them to be moved.

NODE-BASED CONTAINERS store single items in single chunks of dynamically
allocated memory and connect them via pointers. Insertion or erasing
does not affect any other nodes / elements other than the node itself
and its immediate neighbors. 

**Memory and the Standard Containers** **Typical dynamic memory block used per contained object**

**vector**

None; objects are not allocated individually. (See sidebar.)

**deque**

None; objects are allocated in pages, and nearly always each page will store many objects.

**list**

```
struct LNode {
  LNode* prev;
  LNode* next;
  T object;
};
```

**set, multiset**

```
struct SNode {
  SNode* prev;
  SNode* next;
  SNode* parent;
  T object;
};                // or equivalent
```

**map, multimap**

```
struct MNode {
  MNode* prev;
  MNode* next;
  MNode* parent;
  std::pair<const Key, T> data;
};                // or equivalent
```

