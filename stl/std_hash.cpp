/*
# std::hash
Make sure the hash function is const!!!!!
 Standard specializations exist for all built-in types, and some other standard library types such as std::string and std::thread. See the link for the full list.

 For other types to be used in a std::unordered_map, you will have to specialize std::hash<> or create your own function object.

 As for the implementation in GCC, the specialization for builtin-types just returns the bit pattern.

template<typename _Tp>
struct hash<_Tp*> : public __hash_base<size_t, _Tp*>
{
  size_t
  operator()(_Tp* __p) const noexcept
  { return reinterpret_cast<size_t>(__p); }
};

 // Explicit specializations for integer types.
#define _Cxx_hashtable_define_trivial_hash(_Tp)     \
template<>                        \
struct hash<_Tp> : public __hash_base<size_t, _Tp>  \
{                                                   \
  size_t                                            \
  operator()(_Tp __val) const noexcept              \
  { return static_cast<size_t>(__val); }            \
};

/// Explicit specialization for bool.
_Cxx_hashtable_define_trivial_hash(bool)

/// Explicit specialization for char.
_Cxx_hashtable_define_trivial_hash(char)


*/
#include <functional>

class A {
public:
    A (int x , const std::string &name)
            : _x (x) , _name (name) { }

private:
    // If you don't have appropriate getters
    // to retrieve all values for hashing
    friend struct std::hash<A>;
    int _x;
    std::string _name;
};

namespace std {

    // custom specialization of std::hash can be injected in namespace std
    template<>
    struct hash<A> {
        using argument_type = A;
        using result_type = std::size_t;

        result_type operator() (const argument_type &argument) const {
            const result_type first = std::hash<int> () (argument._x);
            const result_type second = std::hash<std::string> () (argument._name);
            // Use all bits, mix things up
            return first ^ ( second << 1 );
        }
    };
}

int main (int argc , char *argv[]) {
    A a (5 , "a");
    std::hash<A> hash;
    print (hash (a));

}
