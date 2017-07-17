CPP Exception Classes

```
#include <stdexcept>

-   std::logic_error
-   std::invalid_argument
-   std::runtime_error
-   std::range_error
-   std::length_error
-   std::domain_error
-   std::overflow_error
-   std::underflow_error
-   std::out_of_range
```

```
void foo()
 {
     throw std::runtime_error("An error occured!");
 }
int main(int argc, char * argv [])
 {
     try
     {
         foo();
     }
    
     catch (const std::exception& e)
     {
         std::cout << e.what() << std::endl;
     }
    

}
```


bad_alloc : by global operator new fails (except when the nothrow version of new is used).

bad_cast :  by dynamic_cast if a type conversion on a reference fails at runtime.

bad_typeid : By typeid operator if argument is zero or the null pointer, this exception gets thrown.

bad_exception : unexpected exceptions.
if class bad_exception is part of the exception specification, then unexpected() usually rethrows an exception of this type:
void f() throw(E1, std::bad_exception)

Thus, if an exception specification includes the class bad_exception, then any exception
not part of the specification may be replaced by bad_exception within the function unexpected().

If there is no bad::exception and an exception is thrown which is not part of specification then the global function unexpected() gets called, which usually calls terminate() to terminate the program.