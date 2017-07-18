# be-wary-of-`auto`-and-proxy-types

Some classes in the standard library return proxy types, most
prominently std::vector<bool>, whose substript operator (operator[])
does not actually return a reference to a real bool and definitely not
to a bit, but actually returns a proxy object of type
std::vector<bool>::reference. This can lead to problems in a case like
this:

    // Function that returns flag bits (note: not a reference)
    std::vector<bool> flags();

    auto flag = flags()[1];

Here, flags will return a std::vector<bool>, which is then accessed at
index [1], such that a std::vector<bool>::reference object is returned.
The problem is that auto will store this object, not a bool. Because the
returned object is not a reference but simply an object with automatic
storage duration, it will be cleaned-up at the end of the expresssion.
The reference object, however, will still point to the word where the
relevant bit was stored in the now-deleted object, meaning you end up
with a dangling reference/pointer!

**Solution** **explicitly typed initializer idiom**

Thus, be sure to be wary about proxy types with auto, and static_cast
them to get the underlying type directly (i.e. the
_explicitly-typed-initializer idiom_):

```
    auto flag = static_cast<bool>(flags()[1]);
```

**Other Proxy Classes**

Expression Templates (Matrix class)

auto sum = static_cast<Matrix>(m1 + m2 + m3 + m4);

**explicitly typed initializer idiom**

```
double calcEpsilon()  // return tolerance value
{
  return 1.0;
}
 // if conversion is desired
 float ep = calcEpsilon();  // implicitly convert // double -> float

 // explicitly typed initializer idiom
 auto ep = static_cast<float>(calcEpsilon());
 ```