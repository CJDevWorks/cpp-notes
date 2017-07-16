why smart pointer has reset and not raw pointer assignement

Attempting to assign a raw pointer to a smart pointer means --

existing_smart_ptr = new T(args); // this means a conversion operator
// which converts raw pointer to smart ptr. Allowing such conversions can be problematic

// first in unique_ptr - copy assignment is not supported. move assignment is supported