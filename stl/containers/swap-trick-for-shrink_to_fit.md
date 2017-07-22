### shrink a vector/string

before C++11

```
std::vector<int> v;
...
// creates a temporary vector of integers and it is guaranteed[1] to allocate memory just
// enough to hold all the elements in the parameter, v
// std::vector<int>(v).swap(v);
// better -- range constructor
std::vector<int>(v.begin(), v.end()).swap(v);

string s;
....
// for string the copy construtor does nt do any memory allocation
// if underlying implementation if refcounted, so use range constructor.
string(s.begin(), s.end()).swap(s);
```

C++11

```
std::vector<int> myvector (100);
...
myvector.resize(10);
...
myvector.shrink_to_fit();
```