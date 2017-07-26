//
// Created by Chandrajeet Singh on 17/7/17.
//

// enable_shared_from_this uses CRTP
// visitor pattern

template <class Derived>
struct base
{
    void interface()
    {
        // ...
        static_cast<Derived*>(this)->implementation();
        // ...
    }

    static void static_interface()
    {
        // ...
        Derived::static_implementation();
        // ...
    }

    // The default implementation may be (if exists) or should be (otherwise)
    // overridden by inheriting in derived classes (see below)
    void implementation();
    static void static_implementation();
};

// The Curiously Recurring Template Pattern (CRTP)
struct derived_1 : base<derived_1>
{
    // This class uses base variant of implementation
    //void implementation();

    // ... and overrides static_implementation
    static void static_implementation();
};

struct derived_2 : base<derived_2>
{
    // This class overrides implementation
    void implementation();

    // ... and uses base variant of static_implementation
    //static void static_implementation();
};