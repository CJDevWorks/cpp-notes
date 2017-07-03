# abort()-and-exit()

When called from main(), there are subtle differences:
- **return** Destructors will be called for local/static/global objects.

- **exit** No destructors will be called for local objects. But destructor for static/global objects
will be called.  you can register a specific function / handler that is called when std::exit is
called. This function is set via std::atexit:

- **abort** No destructors will be called. The abort() function's prototype is in cstdlib header
file.std::abort() sends a SIGABRT signal.

```
// Allocate some memory
int* p = new int(5);
// Will be called upon std::exit() call
void foo()
 {
     std::cout << "foo called" << std::endl;
    
     delete p;
 }
int main(int argc, char * argv [])
 {
     // Register the exit handler
     std::atexit(foo);
    
     // another code for std::exit(int) is EXIT_FAILURE
     std::exit(EXIT_SUCCESS);

}
```

##### exit(): library call, _exit(): system call

The exit() call
```
#include <stdlib.h>
void exit(int status);
```
is in fact a wrapper for the _exit() system call:
```
#include <unistd.h>
void _exit(int status);
```
Programs generally don't call _exit() directly, but instead call the exit() library function,
which performs various actions before calling _exit().

- what the exit() does are following:
 - The stdio stream buffers are flushed.
 - The _exit() system call is invoked, using the value supplied in status.

In general, a process may terminate in two general ways:
 - abort() : Abnormal termination : Whether abort() flushes the buffers depends on the implementation.
 - exit() : A Normal termination using the _exit() system call.
An explicit return of n from main() is generally equivalent to calling exit(n),
since the run-time function that invokes main() uses the return value from main() in a call
to exit().

Performing a return without specifying a value, or falling off the end of the main() function,
also results in the caller of main() invoking exit(), and it is actually equivalent to calling
exit(0) if we compile a program using gcc -std=c99 on Linux.
