# lambdas

- [ input capture ] ( parameters ) { something; }

- with return type (this is optional)
[ input capture ] ( parameters ) -> optional { something; }

**The closure object**

A lambda expression does several things at once:
- It defines the function object class with its function call operator on the fly and creates a single object, the closure object.

- They have a specific type, but you can not name it. For all purposes except for the compiler’s inner workings, the
type has no name. If you have two identical lambda expressions, they will produce closures of two different types regardless.

- You can capture and have an alias or typedef for a closure type by using `decltype`, but since you most often will use lambdas for single use throwaway purposes, this should be a relatively rare use case.

- The most obvious member of the closure type is the function call operator. It has the provided signature, except that it is const-qualified, i.e. the closure object can not be changed.

- Another important member is the implicit conversion to a function pointer. The type corresponds to that of a function with the same parameter list and return type that provided in the lambda signature. So if you encounter an old fashioned callback in the form of a function pointer instead of “anything callable”, you can pass it a lambda, **as long as it has an empty capture list and the correct parameter list**


**members of the closure type**



    - It has a deleted default constructor, so you can’t use the a forementioned typedef to create an independent second object of the same type.

    - Assignment operators are also deleted, so you can’t change a closure object by assigning it an old version of itself.

    - Closure types have defaulted copy and move constructors as well as a defaulted destructor. You can, copy
    and/or move a closure object or you can’t, depending on its members. The destructor simply destroys the closure members as it should.

      - Function call operator

        The function call operator is implicitly declared const. That way, closures can not change their captured state from call to call, which makes sense.

        However, if you truly need to work around that fact, you can do so by explicitly declaring the lambda mutable. The parameter list is no longer optional in that case:

        auto lam = [callcount = 0u] () mutable {
          cout << ++callcount;
        };

As long as the lambda expression has no capture list, all those special members do nothing.

**Closure member variable types**

  - The rules for deducing the types for all those closure member variables are mostly the same rules as for `auto` variables,
  i.e. as for templates. That includes the problems with braced initializers, so better stay clear of those in
  init captures as well.

  - However, when capturing by value, the closure members retain the const and volatile qualifiers from their originals, i.e. capturing a `const string` by value will create a const copy inside the closure object.

  - This does not apply to init captures, so if you need a nonconst capture of a const variable, use an init capture with the same name, like `[a = a]`.




**For input capture:**

Explict captures

- [&] take closure by reference

- [=] take closure by value

-  [=, &var] // Take by value by default, but take the variable “var" by reference.

- Capturing member variables: you have to capture the this pointer. there is no need to prefix the members with `this->` every time inside the lambda.

```
struct Beast {
  unsigned strength;

  void attack(vector<Hero>& heroes) {
    for_each(begin(heroes), end(heroes),

      [this](Hero& hero){
        hero.applyDamage(strength);
      }

    );
  }
};
```

**Use cases :**

In algorithms :


Custom Deleter :


CallBack:


Interface adoption function:


Context specification function:








