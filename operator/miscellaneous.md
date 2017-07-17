**Operators which cannot be overloaded**

?: (conditional)

. ( member selection)

.* (member selection with pointer-to-member)

:: (scope resolution)

sizeof (object size information)

typeid (object type information)

Member operator and global operator:

implement member operator and for operators which requires symetry (lshs and rhs)
define another global operator that is implenented in terms of member operator