**Optimization Strategies that Bomb (ie that dont work)**

1] Assuming some operations are faster than others. When it comes to optimizing, never ever assume anything. Benchmark everything. Use a profiler.

2] Optimizing as you go. Big mistake. As software engineer Donald Knuth said, "premature optimization is the root of all evil." Optimization is one of the last steps of a project. Plan for it, but don't optimize too soon. If you do, you'll end up optimizing code that you either don't use or that doesn't need to be streamlined in the first place. Moreover, you deviate from the actual business logic you are writing code for.
3] Worrying about performance before concentrating on code correctness. Write the code without optimizations first. Use the profiler to determine if it needs to be revised. Don't ignore performance issues; let performance issues guide your design, data structures, and algorithms

Optimization Strategies that Work

1] Set design goals for performance levels. How responsive should the app be? Be specific. Think in terms of concrete millisecond values. Put the values in the specs. What's the target frame rate? How will the program deal with Internet latency and bandwidth issues? In what portions of the application is efficiency critical, and in what portions is efficiency secondary?
2] Select the proper data structures. Carefully evaluate whether you should use floating point or integer math, lists or vectors, hash tables or trees. The right data structures can make the difference between a great game and a dog. That's why the id team used BSP trees instead of Z-buffering in Quake. BSP trees best solved their particular problem.
3] Choose the right algorithms. A linear search may be more appropriate than a binary search. Insertion sort may be faster than quicksort. See the discussion of swapping algorithms in the next section to see how small algorithm variations can effect performance.
4] Profile to find bottlenecks. Add your optimizations. Profile to find bottlenecks. Rinse and repeat. Don't settle on an optimization without verifying that it actually improves the program. Always run "before" and "after" benchmarks to evaluate optimizations. Store the results of each profiling run so you can compare the differences.


 Example of Selecting the Proper Algorithm: Swapping

Swapping objects is a common operation, especially during sorting. The standard C++ swapping function is very simple.

 template <class T> void MySwap(T& a, T& b)
    {
    T t = a; // copy ctor
    a = b;   // assignment operator
    b = t;   // assignment operator
    }        // destructor (element t)

Swapping is so simple that we really only need a single function to handle it, right? Not necessarily. Often an object can provide its own swapping method that is considerably faster than calling the object's constructor, assignment operator (twice), and destructor. In fact, with STL, there are many specialized swap routines, including string::swap, list::swap, and so forth.

1] Take Advantage of STL Containers
Its a standard
Its thin
Its flexible
Its already written, designed, tested, optimized.

2] Use References instead of pointers.
You dont have to do the extra pointer null checking. They are automatically dereferenced so you have cleaner code and lesser amount of typing.

3] Consider Two-Phase Construction - If your object is very large and takes time

4] Inlining functions
5] Avoiding temporaries objects. (c'tor and d'tors are called for them)
6] Return objects via reference.
7] Use STL containers

Malloc: extern void* malloc(size_t);
Free: extern void free(void*);
Calloc: extern void* calloc(size_t num, size_t size) - Creates a memory of size num*size bytes and initializes with 0.
Realloc: extern void* realloc(void*, size_t)