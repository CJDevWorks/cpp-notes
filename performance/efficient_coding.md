
- for internal stare use enums rather than string. Avoids string comparision , conversion logics.

- in place of web of if/else use swith. If the case range is compact it will be optimized. A jump table is created . The table is an array containing the start address of the code for each case. When executing the switch statement, the table is used to jump to the code associated with the case number.

```
// N.B.: This is not C++ code
static address jump_table[] = { case_a, case_b, end, case_a };
unsigned int index = i - 10;
if (index > 3) goto end;
goto jump_table[index];
case_a: func_a(); goto end;
case_b: func_b();
end:
```

if case range is dispersed:
```
if (i == 100) goto case_a;
if (i == 130) goto case_a;
if (i == 110) goto case_b;
goto end;
case_a: func_a(); goto end;
case_b: func_b();
end:
```

if jump table is not there then seq of if statement becomes important


- calling function from a loop : if arguments are greater create a struct outside loop,
pass that inside loop , manipulate and make a function call.
If arguments are more than the registers then arguments (partly/fully) will be pushed on stacka nd then removed fom stack


**Things to avoid**
1. Throw : it takes thousands of cycle. DO it when you want to convey a real run time error that need to be notified to client and no effective handling is present.

2. Virtual member function : Do use unless required. Look out for virtual destrcutor.
3. Virtual ingeritance : Use it only when the virtual base class has some non-static data, otherwise if there are only function then leave it.
4. Templates with virtual : Avoid it, because when class template is instantiated, it generates copy of all memeber function used (including, vtable and RTTI data). This bloats the code.
5. Automatic deallocators : GC when invoked block others.

6. Volatile : They are useless for multithreading

**Constructor and Destructor**

1. Declare variable as late of possible and initialize variable (other than assignments).
2. pre-incement vs post increment. Almost as fast (implement post inclement in term of pre increments).
3. use composite operator . a+=b/ s.append()/ s1 +=s2


**Allocators and deallocators**
- for static size seq use array rather than vector
- object pool for small objects (avoid mem fragmentation, good use of data caches , high speed for allocation/de-allocation). Sucj allocator can greatly improve performance of node based containers.
Boost provides two allocators :
- pool_allocators
- fast_pool_allocators

**Memory access order**
- in ctor, assignment in order of declaration
- scan arrays in increasing order;in arrays - use row major. scan multidimensional arrays using the rightmost index for innermost loops;
  spacial locality helps cache and vectorization (different architecture have vector processor that support SIMD)
  They can produce loop level automatci vectorization (depending on condition that no fucntion call made, no short iteration count and )


```
float a[num_levels][num_rows][num_columns];
for (int lev = 0; lev < num_levels; ++lev)
{
    for (int r = 0; r < num_rows; ++r)
    {
        for (int c = 0; c < num_columns; ++c)
        {
            a[lev][r][c] += 1;
        }
    }
}
```


**- memory alignment**

- group most used function/variables in compilation unit : Instruction cache localization.


Thread Usage


**IO**

1. Save data in binary format : less space , same format as processor.
2. dont frequently open/close files
3. do a operation on 4 KB io buffer than smaller io.
4. **Memory mapped file** : If you need to access binary file in non sequential fashion instead of accessing it in seek operation or loading it all in application buffer use memory mapped file.

why memory mapped file should not be used in real time application???

```
When you have to access most parts of a binary file in a non-sequential fashion, there are two standard
alternative techniques:
• Open the file without reading its contents; and every time a data is demanded, jump to the data
position using a file positioning operation (aka seek), and read that data from the file.
• Allocate a buffer as large as the whole file, open the file, read its contents into the buffer, close the
file; and every time a data is demanded, search the buffer for it.
Using a memory-mapped file, with respect to the first technique, every positioning operation is
replaced by a simple pointer assignment, and every read operation is replaced by a simple memoryto-
memory copy. Even assuming that the data is already in disk cache, both memory-mapped files
operations are much faster than the corresponding file operations, as the latter require as many system
calls.
With respect to the technique of pre-loading the whole file into a buffer, using a memory-mapped file
has the following advantages:
• When file reading system calls are used, data is usually transferred first into the disk cache and
then in the process memory, while using a memory-mapped file the system buffer containing the
data loaded from disk is directly accessed, thus saving both a copy operation and the disk cache
space. The situation is analogous for output operations.
• When reading the whole file, the program is stuck for a significant time period, while using a
memory-mapped file such time period is scattered through the processing, as long as the file is
accessed.
• If some sessions need only a small part of the file, a memory-mapped file loads only those parts.
• If several processes have to load in memory the same file, the memory space is allocated for every
process, while using a memory-mapped file the operating system keeps in memory a single copy
of the data, shared by all the processes.
• When memory is scarce, the operating system has to write out to the swap disk area even the parts
of the buffer that haven't been changed, while the unchanged pages of a memory-mapped file are
just discarded.
Yet, usage of memory-mapped files is not appropriate in a critical portion of a real-time system, as
access to data has a latency that depends on the fact that the data has already been loaded in system
memory or is still only on disk.
Strictly speaking, this is a technique dependent on the software platform, as the memory-mapped
file feature is not part of C++ standard library nor of all operating systems. Though, given that such
feature exists in all the main operating systems that support virtual memory, this technique is of wide
applicability.
Here are two classes that encapsulate the access to a file through a memory-mapped file, followed by
a small program demonstrating the usage of such classes. They are usable both from Posix operating
systems (like Unix, Linux, and Mac OS X) and from Microsoft Windows. The MemoryFile class
allows both to write and to read a file, and also to change its size.
```


**Caching techniques :**

1. Lookup table : use when operation is costly and previous values can be reused. If lookup size is large then its not that useful.

2. LRU ??

**Sorting**

1. For int sequences with value in predefined range use counting sort.
2. To partially sort a sequence (first/last N elements) use std::partial_sort (stable_partial_sort to maintian order)
3. To get n elements from a sequence but not in sorted order use std::nth_element.
4. To partition a sequence use std::partition/std::stable_partition.
5. std::sort - this is introsort, first q sort if recursion gets too deep use heap sort.
6. stable_sort uses merge sort extra memory (O(n))


**RunTime Support**

- use virtual in place of `typeid` and typeid in place of dynamic_cast.
- noexpect optimization
- move bottlenecks out of try/catch block

**Floating point Vs integer operation**

- If the target processor does not contain a floating point unit, replace floating point functions,
constants and variables with the corresponding integer functions, constants and variables;
if the target processor contains only a single precision floating point unit, replace double
functions, constants and variables with their float correspondents.

- Present processors for desktop or server computers contain dedicated hardware for floating point
arithmetic, both at single and at double precision, and therefore such operations are almost as fast as
their integer correspondents.

- use integer operation as backup (10 pow -8).
- use epsilon for compare

Double Compare issue : false result or unstable result.
Absolute compare with epsilon : If the numbers are big absolute comapring does not give good result. This is due to way float is represented

```
bool isEqual = fabs(f1 – f2) <= epsilon;
```

For numbers larger than 2.0 the gap between floats grows larger and if you compare floats using FLT_EPSILON then you are just doing a more-expensive and less-obvious equality check. That is, if two floats greater than 2.0 are not the same then their difference is guaranteed to be greater than FLT_EPSILON. For numbers above 16777216 the appropriate epsilon to use for floats is actually greater than one, and a comparison using FLT_EPSILON just makes you look foolish. We don’t want that.



Relative epsilon comparisons






