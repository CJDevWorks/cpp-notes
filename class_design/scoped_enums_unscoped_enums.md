## Scoped Enum / Enum Class

- C++98 : Typesafe enum using wrapping it in a parameterized class,. Storing enum type in a array [start-end]


The enum classes ("new enums", "strong enums") address three problems with traditional C++ enumerations:

- conventional enums implicitly convert to int, causing errors when someone does not want an enumeration to act as an integer.

- conventional enums export their enumerators to the surrounding scope, causing name clashes.

- the underlying type of an enum cannot be specified, causing confusion, compatibility problems, and makes forward declaration impossible.

The new enums are "enum class" because they combine aspects of traditional enumerations (names values) with aspects of classes (scoped members and absense of conversions).
