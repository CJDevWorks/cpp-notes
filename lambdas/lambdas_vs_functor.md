
When to prefer lambda:

1) It's trivial and trying to share it is more work than benefit. Small functions that are not repeated.

2) Defining a functor simply adds complexity (due to having to make a bunch of member variables and crap).

When to prefer functors:

1. want more than one instance.

2. have to do advanced resource handling. You can also not define special member functions, including constructors and destructors - what if a functor shall be responsible for resources?

3. need to refer to the functor as a type. For example, to pass it as a template parameter.
4. (related) can give a meaningful and generally useful name to the type (as opposed to the instance).
5. find that the logic can be written cleaner when split up into sub-functions. In a lambda, we have to write everything into a single function.