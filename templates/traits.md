Iterator traits :

**Implementation of common traits:**

```
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

### integer_const
This is the base class of traits class
```
template<class T, T v>
struct integral_constant {
    static constexpr T value = v;
    typedef T value_type;
    typedef integral_constant type; // using injected-class-name
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; } //since c++14
};

template <bool B>
using bool_constant = integral_constant<bool, B>;
```

true_type	std::integral_constant<bool, true>
false_type	std::integral_constant<bool, false>
