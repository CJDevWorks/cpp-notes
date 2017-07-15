**Course Topics**

1. Class templates
    1. Parameters and arguments, specialization and instantiation (Heap container)
    2. Friends of class templates
    3. Class templates as friends
2. Function templates
    1. Argument deduction
    2. Overloading and interaction with non-template functions
    3. SFINAE
    4. Default function template arguments
3. Other templates
    1. Alias templates
    2. Variable templates
4. Variadic templates
    1. Variadic class templates and template pack expansion (tuple)
    2. Variadic function templates and argument pack expansion (print)
    3. Simultaneous and nested pack expansion (forwarding idiom)
5. Member templates
    1. Copy-like and move-like operations (smart pointer conversions)
    2. Variadic member templates and constructors (PlacedPtr)
    3. Emplacement (Heap)
    4. Generic lambda functions
6. Template translation
    1. Two-phase translation
    2. Dependent names and the typename keyword
    3. Nested template names and the template keyword
    4. INCINI and flexible interface design (STL container comparisons, Heap comparison)
7. Some traditional template programming gotchas and hacks
    1. Array passed as reference does not decay during argument deduction
    2. Failure to track changes in std::stack, etc.
    3. Dependent base classes
    4. Making names dependent for safety
    5. Making names dependent to avoid premature errors (static_assert for primary template)
    6. Exploiting two-phase translation to delay inlining (Chicken/Egg example with set)
8. Class template specialization and partial specialization
    1. Using specialization to customize implementations (Heap container)
    2. Using specialization to ask compile-time questions (is_void, is_const, can_convert)
    3. The type_traits header file
    4. Constraint checking with static_assert
    5. Compile-time type manipulation (std::move implementation, recovering deduced type in generic lambda)
9. Function template specialization
    1. Problems with function template specialization
    2. The Function Template Partial Specialization idiom
10. The First/Rest idiom
    1. Recursive template specialization
    2. First/Rest idiom for variadic class templates
    3. Choosing recursion paths for correctness
    4. Avoiding exponential specialization (std::conditional counter-example)
    5. Dealing with long compile-time sequences (make_index_sequence)
    6. First/Rest for variadic function templates
    7. Using nested class templates for unwrap parameter packs
    8. Using forwarding functions to unwrap parameter packs
*** end of first day ***

11. Alias templates revisited
    1. Adding and removing template parameters
    2. First/Rest with alias template intermediaries
    3. The rebind mechanism
    4. Simplifying complex compile-time predicates (STL iterator categories)
12. Non-type template parameters
    1. First/Rest on index sequence (max_value)
    2. Literal operator templates (base 3 numeric literals)
    3. Function pointers as template arguments (numeric integration)
13. Index parameter packs
    1. Selection with index pack expansion
    2. Using initializer lists to fix evaluation order
    3. Replacing recursive specialization with pack expansion
    4. Replacing recursive specialization with constexpr functions
14. Template template parameters and policy-based design
    1. Template template parameters (Heap container implementation policy)
    2. Variadic template template parameter packs
    3. Variadic variadic template template parameter packs
    4. Applications of template sequences (tuple apply)
15. SFINAE
    1. Mode of application of SFINAE in C++03 vs. Modern C++
    2. Enable_if
    3. Preprocessing overload resolution with SFINAE
    4. Designing DWIM class interfaces (Heap range initialization)
    5. Dealing with overloaded universal reference member functions
    6. Resizable component interfaces (transparent function objects)
    7. Other contexts for SFINAE application (enum containers)
16. Type erasure (std::function and lambdas, Observer design pattern)
17. The Barton-Nackman Trick
    1. Making New Friends idiom (rational number binary operators)
    2. CRTP (count, relational operators, variadic CRTP application)
18. Type structures
    1. Calculating new types at compile time (SI physical units)
    2. Expression templates (matrix arithmetic)
    3. Typelists
    4. Conversion of typelist meta-algorithms to variadic template meta-algorithms (typelist set intersection)
    5. Template ASTs (complex compile-time type predicates)