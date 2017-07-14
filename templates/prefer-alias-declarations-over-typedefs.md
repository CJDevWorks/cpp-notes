# prefer-alias-declarations-over-typedefs

There are three main reasons why to prefer alias-declarations over
typedefs:

1. They look clearer and better.

2. ^ especially for function pointers:

typedef void (*pointer) (std::string, bool);

vs.

using pointer = void (*) (std::string, bool);

(Note how the name is no longer nested as horribly).

3. Alias declarations can be templated!

```
template<typename Key>
using HashMap = std::unordered_map<Key, int, std::hash<Key>, std::equal_to<Key>,
                    std::allocator<std::pair<const Key, int>>>;
HashMap<string> sHashMap;
```

```
template<typename Key>
struct HashMap98{
    typedef std::unordered_map<Key, int, std::hash<Key>, std::equal_to<Key>,
                    std::allocator<std::pair<const Key, int>>> type;
};

HashMap98<string>::type sHashMap98;
```

Note : typename and accessing it via type.

**why typename :**

Because the compiler could not know if there were still a specialization
of Map where _typ_e were not actually a type, but for example a static
variable.

This is not the case for alias declarations, as alias
declarations _must_ alias a type, meaning there is no need for either
the ::type nor for the typename:


One last thing to note is that for all the type_traits operations in the
<type_traits> header which use a typedef and a struct, there is also a
corresponding version using alias declarations. These alias-declaration
versions are accessible by appending a ‘_t’ at the end of e.g.
std::remove_reference (making it std::remove_reference_t):

```
// C++98
typename std::remove_const<T>::type object;

// C++14
std::remove_const_t<T> object;

template<typename T>
struct my_remove_reference{
    typedef T type;
};

template<typename T>
struct my_remove_reference<T&>{
    typedef T type;
};

template<typename T>
struct my_remove_reference<T&&>{
    typedef T type;
};

template<typename T>
using my_remove_reference_t<T> =  my_remove_reference<T>::type

```

