**std::unique_ptr<T> or std::unique_ptr<T[]>**

- smart pointer to manage exclusive ownership of a resource.
When the unique_ptr object goes out of scope, the underlying resource is deleted. By default, unique_ptr calls delete on the underlying resource, but you can give your custom deleter.

- Good example is a factory method

- Note that the size of a unique_ptr class with default deleter is same as the size of raw pointer, so no penalty for using unique_ptr.

- In case the deleter is a function pointer, the size of unique_ptr will increase by atleast the size of the function pointer, so that is why it is recommended to use function objects or stateless lambdas (lambdas which do not capture scope) as deleters as the compiler can directly stick the code in the function object in the d'tor of the unique_pointer so there is no increase in size.


```

struct custom_delete {
    template <typename T>
    void operator()(T* const ptr) const {
        delete ptr;
    }
};

void destroy(int * p) {delete p;}

int main(){
    std::unique_ptr<int> x;
    std::unique_ptr<int, custom_delete> y;
    //auto del = [](int * p) {delete p;};
    //std::unique_ptr<int, decltype(del)> y(nullptr, del);
    //std::unique_ptr<int, void (*)(int*)> y(nullptr, destroy);

    std::cout << "sizeof(x): " << sizeof(x) << "\n"
              << "sizeof(y): " << sizeof(y) << "\n"
              << std::flush;
}
```

Note : the object return from factory with unique_ptr with custom deleter. The base classes should have virtual destructor. They are getting deleted from custom deleter (that takes raw pointer to class).
So unless all objects created from factory are derived from base class that will be a problems.

- unique_ptr conversion to shared_ptr

Important
---------
std::unique_ptr<> cannot be copied, but can be moved. So we can actually put them into containers.

**Unique_ptr<T[]>**

interfaces for subscript, cc, mc,  ca, ma

- strings, vector, arrays are better alternatives but in case of levacy system integration where the incoming data is char*

Why unique_ptr should have the deleter as part of interface and not implicit type erasure as in Smart_ptr


```
//char *p = malloc(256);
//char *p2 = new char;  // not terribly useful, but possible
//char *p3 = new char [256];
//char *p4 = "Just some random text";

struct MyDeleter{
    MyDeleter()
    : f( [](char *p) { delete p;} )
    {}

    // allow the user to specify what type of deleter to use
    explicit MyDeleter(std::function< void(char *)> const &f_ )
    : f(f_)
    {}

    void operator()(char *p) const
    {
        f(p);
    }

    private:
    std::function< void(char *)> f;
};

typedef std::unique_ptr<char, MyDeleter > Unique_Ptr_2;
Unique_Ptr_2 p( (char *)malloc(256),     MyDeleter( [](char *p) { free(p); } ));
Unique_Ptr_2 p2( new char ,              MyDeleter( [](char *p) { delete p; } ));
Unique_Ptr_2 p3( new char [256],         MyDeleter( [](char *p){ delete [] p; } ));
Unique_Ptr_2 p4( "Just some random text", MyDeleter( [](char *){} ));

```



