# rvalue-and-lvalue

- An lvalue can be referred to, it has an identity / a name.

- An rvalue cannot be referred to and has no identity. One form of rvalue is a temporary object, 
e.g. non-reference object return value of a function, or intermediary objects during longer expression
( x * (y * z)-> y*z = temporary), which are deleted as soon as the expression in which it is used is fully evaluated. 

- Also literals (5, ‘A’, false) are rvalues.

- An rvalue may be assigned to an lvalue.
- rvalue cant tak etake any other  rvalue or lvalue.

================BINDINGS================
* lvalue ==> lvalue/lvalue ref/const lvalue/const lvalue ref
* const lvalue ==> lvalue/const lvalue ref
* rvalue ==> rvalue/const rvalue ref
* const rvalue ==>  const rvalue ref

Note:
**If you implement**
void foo(X&);
 // but not
void foo(X&&);
then of course the behavior is unchanged: foo can be called on l-values, but not on r-values.

**If you implement**
void foo(X const &);
 // but not
void foo(X&&);
then again, the behavior is unchanged: foo can be called on l-values and r-values, but it is not possible to make it
distinguish between l-values and r-values. That is possible only by implementing
void foo(X&&);

**If you implement**
void foo(X&&);
 // but neither one of
void foo(X&);
void foo(X const &);
foo can be called on r-values, but trying to call it on an l-value will trigger a compile error

Example: (Confirm)
```
T& fooReference();
T fooNotReference();
int main(int argc, char * argv [])
 {
     T t;
    
     // x = lvalue, 5 = rvalue
     // other rvalues: 'c', true etc.
     // Constructors return rvalues!
     T x = t;
    
     // fooReference() = lvalue because
     // it returns a reference
     x = fooReference();
    
     // fooNotReference() = rvalue because
     // it returns a non-reference
     x = fooNotReference();
    
     // rvalues can temporarily act as lvalues
     fooNotReference() = t;
    
     fooNotReference().someMemberFunction();
    
     // Because fooReference() returns a reference
     // to an object which has an identity and can
     // be referred to, r can be a new reference to
     // this object
     T& r = fooReference();
    
     // Error! Because fooNotReference() returns a
     // non-reference temporary rvalue, this object
     // has no identity and can not be referred to
     // by a non-const reference
     T& nr = fooNotReference();
    
     // But const references work with rvalues
     // (this is simply a C++ rule ...)
     const T& cnr = fooNotReference();
    
     // Function names are rvalues
     T& (*ptr)() = fooReference;
    
     T arr [4];
    
     // Error! Array names are rvalues
     // (return a pointer to the first
     // element of the array), but
     // ra is a non-const reference and
     // can thus only bind to lvalues
     T& ra = arr;
    
     // In C++11 you can use rvalue
     // references to bind temporary
     // objects and other rvalues
     // Note the && instead of &
     T&& rvr = fooNotReference();
    
     // These temporary variables can
     // then be used further
     rvr.doSomething();

}
```

Question :

**First example**
```
std::vector<int> return_vector(void)
{
    std::vector<int> tmp {1,2,3,4,5};
    return tmp;
}
std::vector<int> &&rval_ref = return_vector();
```

The first example returns a temporary which is caught by rval_ref. That temporary will have its life
extended beyond the rval_ref definition and you can use it as if you had caught it by value.
This is very similar to the following:
```
const std::vector<int>& rval_ref = return_vector();
```

except that in my rewrite you obviously can't use rval_ref in a non-const manner.

**Second example**
```
std::vector<int>&& return_vector(void)
{
    std::vector<int> tmp {1,2,3,4,5};
    return std::move(tmp);
}
std::vector<int> &&rval_ref = return_vector();
```

In the second example you have created a run time error. rval_ref now holds a reference to the destructed tmp inside
the function. With any luck, this code would immediately crash.

**Third example**
```
std::vector<int> return_vector(void)
{
    std::vector<int> tmp {1,2,3,4,5};
    return std::move(tmp);
}
std::vector<int> &&rval_ref = return_vector();
```

Your third example is roughly equivalent to your first. The std::move on tmp is unnecessary and can actually be a
performance pessimization as it will inhibit return value optimization.

**Best practice**
```
std::vector<int> return_vector(void)
{
    std::vector<int> tmp {1,2,3,4,5};
    return tmp;
}

std::vector<int> rval_ref = return_vector();
```

I.e. just as you would in C++03. tmp is implicitly treated as an rvalue in the return statement.
It will either be returned via return-value-optimization (no copy, no move), or if the compiler decides it can not
perform RVO, then it will use vector's move constructor to do the return.

Only if RVO is not performed, and if the returned type did not have a move constructor would the copy constructor
be used for the return.

- Compilers will RVO when you return a local object by value,
and the type of the local and the return of the function are the same, and neither is cv-qualified
(don't return const types).

- Stay away from returning with the condition (:?) statement as it can inhibit RVO.

- Don't wrap the local in some other function that returns a reference to the local. Just return my_local;.

- Multiple return statements are ok and will not inhibit RVO.


=================== Even if the optimization is not applied (RVO)

there is no need for explcit move , for local objects copiler will add explict move if RVO fails