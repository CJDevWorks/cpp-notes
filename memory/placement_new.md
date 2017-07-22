### new(void(*address)) T(v)


If A is std::allocator<T>, then this will call placement-new, as by ::new((void*)p) T(v)