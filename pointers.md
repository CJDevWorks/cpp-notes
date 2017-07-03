##### Pointers

Reasons of Crash

- Un-initialized pointer operation
- invalid access resulting with an attempt to read or write using a NULL pointer.
- Invalid array indexing - out of bound array indexing.
- Illegal stack operation - a program passes a pointer of the wrong type to a function.
- Accessing an illegal address. Infinite loop
- invalid array indexing when the loop index exceeds the array bounds and corrupts memory.
- Invalid object pointer - invoking a method for an illegal object pointer.
Corruption of the v-table pointer. Not checking for memory allocation failure.


**C Array & String**

what will happen in strcpy if src and target overlap or when src is not big enough
 - Undefined behaviour
 - c11 has new functions to handle this

Better alternative:
Use strcpy_s because in addition to the destination and source arguments, it has an additional
argument for the size of the destination buffer to avoid overflow.
this is still probably the fastest way to copy over a string if you are using char arrays/pointers.
```
char *srcString = "abcd";
char destString[256];
strcpy_s(destString, 256, srcString);
```

Problems with strncpy :
May overrun the buffer: strcpy, sprintf
Sometimes null-terminates: strncpy, _snprintf, swprintf, wcsncpy, lstrcpy
Always null-terminates: snprintf, strlcpy