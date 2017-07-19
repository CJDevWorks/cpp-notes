//
// Created by Chandrajeet Singh on 17/7/17.
//

// typename... Args is called a template parameter pack, and
// Args... args is called a function parameter pack
// std::cout << __PRETTY_FUNCTION__ << "\n";

#include <memory>
#include <iostream>

template <class... Ts> struct tuple {};

template <class T, class... Ts>
struct tuple<T, Ts...> : tuple<Ts...> {
    tuple(T t, Ts... ts) : tuple<Ts...>(ts...), tail(t) {}

    T tail;
};


/// Examples

template<class... Types>
struct count {
    static const std::size_t value = sizeof...(Types);
};

template<typename T, typename... Args>
T adder(T first, Args... args) {
    return first + adder(args...);
}

template <template <typename, typename...> class ContainerType,
        typename ValueType, typename... Args>
void print_container(const ContainerType<ValueType, Args...>& c) {
    for (const auto& v : c) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
}


template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}