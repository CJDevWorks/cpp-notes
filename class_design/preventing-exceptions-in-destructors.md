# preventing-exceptions-in-destructors

Prevent exceptions from leaving destructors. If you fear that a
destructor may have to call a function that may throw an error, provide
the user with an explicit function to “close” or “destruct” the object
where the user

can handle exceptions. Inside the destructor, should an exception arise
when calling that closing function (given the user didn’t do so before,
so have a private boolean member), either:

1.  Abort the program after logging some information. If the program
    can’t continue to function after an error was emitted inside the
    constructor, e.g. some vital things couldn’t be closed, terminate
    the program by calling std::abort().
2.  Silence, or “swallow”, the exception, by having a try-catch block
    inside the destructor for that closing function and then just
    logging that it threw an exception, like “Closing failed!”.

These two things above don’t actually solve the problem of handling
exceptions and giving the user options of how to react, but we already
do so by giving the user the chance to catch exceptions with the
explicit “close” function, so he or she

can’t complain if we don’t handle the exception in the destructor. 

```
Provide a public interface for release or special work that throws exception.
Let client handle the exception. Keep destrucor simple.
```

There are two situations in which a destructor is called. The first is when an object is destroyed under "normal" conditions, e.g., when it goes out of scope or is explicitly deleted. The second is when an object is destroyed by the exception-handling mechanism during the stack-unwinding part of exception propagation. ¤

That being the case, an exception may or may not be active when a destructor is invoked. Regrettably, there is no way to distinguish between these conditions from inside a destructor.4 As a result, you must write your destructors under the conservative assumption that an exception is active, because if control leaves a destructor due to an exception while another exception is active, C++ calls the terminate function.


