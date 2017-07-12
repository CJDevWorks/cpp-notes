**Build 'em Up, Tear 'em Down**

**Construction Order:**

1. virtual base classes shall be initialized in the order they appear on a depth-first left-to-right traversal of the directed acyclic graph of base classes, where “left-to-right” is the order of appearance of the base class names in the derived class base-specifier-list.


2. Then, direct base classes shall be initialized in declaration order as they appear in the base-specifier-list (regardless of the order of the mem-initializers).

3. Then, non-static data members shall be initialized in the order they were declared in the class definition (again regardless of the order of the mem-initializers).

4. Finally, the compound-statement of the constructor body is executed.

**Destrcution Order :**

The declaration order is mandated to ensure that base and member subobjects are destroyed in the reverse order of initialization.

When you construct an instance of a derived class, what happens, exactly?

If the class has a vtbl, the process goes something like the following.

Step 1: Construct the top-level base part:.

- **Make the instance point to the base class's vtbl**.
- **Construct the base class instance member variables**.
- Execute the body of the base class constructor.


Step 2: Construct the derived part(s) (recursively):

- **Make the instance point to the derived class's vtbl**.
- **Construct the derived class instance member variables**.
- Execute the body of the derived class constructor.

**Destruction happens in reverse order, something like this:**

Step 1: Destruct the derived part:

(The instance already points to the derived class's vtbl.)
- Execute the body of the derived class destructor.
- Destruct the derived class instance member variables.

Step 2: Destruct the base part(s) (recursively):

- Make the instance point to the base class's vtbl.
- Execute the body of the base class destructor.
- Destruct the base class instance member variables.


Based on Above :

"Never call virtual functions during construction or destruction."
