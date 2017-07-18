

 They decay their return type; i.e., they convert reference type to non-cv object type, function to function pointer, and array to pointer. These are the same conversions that occur when you pass arguments to functions by value. Thus, a lambda with deduced return type:

```
[](T x, U y) { return y < x ? y : x; }
```

Is equivalent to:

```
[](T x, U y) -> typename std::decay<decltype(y < x ? y : x)>::type
{ return y < x ? y : x; }
```

But do you know what that means? Lambdas cannot deduce reference return types! If you need your lambda to return a reference, you have to say it explicitly. But you see, it is not bad that lambdas do not deduce references; otherwise they would be risking causing an UB. And in the language that encourages value semantics returning by value is not a bad thing.