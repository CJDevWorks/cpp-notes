
* What is the difference between the vtable for a class with virtual functions and a class with pure virtual functions?
* if an abstract class with a pure virtual function doesn't define the function, what goes in the corresponding place in the vtbl?

Traditionally, C++ implementors have provided a special function, which prints "Pure virtual function called" (or words to that effect), and then crashes the program.

gcc: "pure virtual method called".


