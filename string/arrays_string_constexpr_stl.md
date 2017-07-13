# arrays

### get number of elements of array

***runtime**

sizeof(arr) / sizeof(*arr); // total size divided by size of single

**compileTime**

### size-of-array-with-constexpr

passing array as reference

```
template<typename T, std::size_t N>
constexpr std::size_t size(T (&a) [N])
{
   return N - 1; // null terminator
}

int main(int argc, char * argv [])
{
     char str [] = "Hello";
     std::cout << size(str) << std::endl;
}
```

### std::end implementation for array

```
#include <iostream>
#include <string>
#include <iterator>

template<typename T, std::size_t N>
 T* end_itr(T (&array) [N])
{
    return array + N;
}

int main(int argc, char * argv[])
{
    int arr [] = {1, 2, 3};
    std::copy(std::begin(arr), // equivalent to arr itself
            end_itr(arr),// equivalent to arr + 3
            std::ostream_iterator<int>{std::cout, " "});
}
```

### size-of-string-literal-at-compile-time-with-constexpr

template<std::size_t N>
constexpr std::size_t lower(const char (&string) [N], std::size_t i = 0,
std::size_t count = 0)
 {
     return i == N ?
             count :
             string[i] >= 'a' && string[i] <= 'z' ?
                  lower(string, i + 1, count + 1) :
                  lower(string, i + 1, count);
 }

int main(int argc, char * argv [])
{
     std::cout << lower("Hello World!");
}


**Using arrays with std functions**

std::begin(arr); // equivalent to arr; first element
std::end(arr); // equivalent to arr + sizeof(arr)


```
int a [] = {1, 2, 3};
int b [3];

// Could also use a + 3 (because size is known)
std::copy(a, a + sizeof(a)/sizeof(*a), b);
std::copy(std::begin(b), std::end(b),
            std::ostream_iterator<int>{std::cout, " "});

std::cout << "\n";
std::copy(std::begin(a), std::end(a), std::begin(b));

for (int i : {0, 1, 2}) std::cout << b[i] << " ";
```

std::array