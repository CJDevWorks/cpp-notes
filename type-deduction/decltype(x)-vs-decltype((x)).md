# decltype(x)-vs-decltype((x))

decltype(x) and decltype((x)) will not always result in the same type
declaration.

for lvalue expression of type T other than names, decltype always reports a type of T&

```C++
int main(int argc, char * argv[])
{
	struct { int a = 5; } s;

	int x = 5;

	// If the x in decltype(x) is the unparanthesized
	// name of an object or a function or a member access
	// specification (i.e. object.member or pointer->member)
	// then decltype yields the type of x (no reference)
	// s.a is treated as if it were a declared lvalue

	decltype(s.a) y = x;

	 y = 10;

	// No change, y is of type int (not int&)
	// and thus x remains what it was: 5
	std::cout << x << std::endl;

	decltype((s.a)) z = x;

	 z = 10;

	// Change! z is of type int&, because the parantheses
	// syntax results in decltype evaluating its argument
	// as an lvalue *expression*. s.a really returns an int&
	// to s.a, so the declared type will be int&
	std::cout << x << std::endl;
}
```
