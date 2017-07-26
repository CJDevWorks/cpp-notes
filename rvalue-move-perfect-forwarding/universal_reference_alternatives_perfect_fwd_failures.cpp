#include <iostream>
#include <set>
#include <type_traits>
// function templates for universal reference

void authenticate() {};

std::multiset<std::string> names;
std::string idToString(int i) {return std::string("Hello");}

template <typename T>
void authenticateAndLog(T&& data)
{
    authenticate();
    names.emplace(std::forward<T>(data));
}

void authenticateAndLog(int data)
{
    authenticate();
    names.emplace(idToString(data));
}

// problem call to
short sId =1;
authenticateAndLog(sId);

// Solution tag dispatching

template <typename T>
void authenticateAndLogImpl(T&& data, std::false_type)
{
    authenticate();
    names.emplace(std::forward<T>(data));
}

template <typename T>
void authenticateAndLogImpl(T&& data, std::true_type)
{
    authenticate();
    names.emplace(idToString(data));
}

template <typename T>
void authenticateAndLog1 (T&& data)
{
    authenticate();
    authenticateAndLogImpl(std::forward<T>(arg), typename std::remove_reference<T>::type);
}

// Universal reference and template constructor:
// overrules copy and move constructors(from subclass)

std::string nameFromIdx(int idx)   // as in Item 26
{
    return std::string("Bart");
}

class Person {
public:
    template<                                 // as before
            typename T,
            typename = std::enable_if_t<
                    !std::is_base_of<Person, std::decay_t<T>>::value
                    &&
                    !std::is_integral<std::remove_reference_t<T>>::value
            >
    >
    explicit Person(T&& n)
            : name(std::forward<T>(n))
    {
        // assert that a std::string can be created from a T object
        static_assert(
                std::is_constructible<std::string, T>::value,
                "Parameter n can't be used to construct a std::string"
        );

        // ...                   // the usual ctor work goes here
    }

    explicit Person(int idx)  // remainder of Person class (as before)
            : name(nameFromIdx(idx))
    { /* ... */ }

    // ...

private:
    std::string name;
};
