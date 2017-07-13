# Function templates

Overloads of template functions are called ‘base templates’.

```
// A function template with two overloads
template<class T> void f( T );              // (b)
template<class T> void f( int, T, double ); // (c)

// A separate base template that overloads (b) and (c)
// -- NOT a partial specialization of (b), because
// there's no such thing as a partial specialization
// of a function template!
template<class T> void f( T* );             // (d)

// A full specialization of (b) for int
template<> void f<int>( int );              // (e)

// A plain old function that happens to overload with
// (b), (c), and (d) -- but not (e), which we'll
// discuss in a moment
void f( double );                           // (f)
```

RULE :

1. Nontemplate functions are first-class citizens.(but It's preferred only if it is an exact match.)

2. Then base templates as overloads(Note : specialization not considered at this stage):
Only after it's been decided which base template is going to be selected, and that choice is locked in, will the
compiler look around to see if there happens to be a suitable specialization of that template available,
and if so that specialization will get used.

- If that base template happens to be specialized for the types being used, the specialization will get used,
otherwise the base template instantiated with the correct types will be used

- if there's a tie for the "most specialized" function base template, the call is ambiguous because the compiler
can't decide which is a better match.  programmer will have to do something to qualify the call

 - if there's no function base template that can be made to match,
 the call is bad and the programmer will have to fix the code.

```
// Example 1, continued: Overload resolution
//
bool b;
int i;
double d;

f( b );        // calls (b) with T = bool
f( i, 42, d ); // calls (c) with T = int
f( &i );       // calls (d) with T = int
f( i );        // calls (e)
f( d );        // calls (f)
```



3. Consider the following declarations:

```
    template<typename T1, typename T2>
    void f( T1, T2 );                       // 1
    template<typename T> void f( T );       // 2
    template<typename T> void f( T, T );    // 3
    template<typename T> void f( T* );      // 4
    template<typename T> void f( T*, T );   // 5
    template<typename T> void f( T, T* );   // 6
    template<typename T> void f( int, T* ); // 7
    template<> void f<int>( int );          // 8
    void f( int, double );                  // 9
    void f( int );                          // 10
```
Which of the above functions are invoked by each of the following? Be specific by identifying the template parameter types, where appropriate.

```
    int             i;
    double          d;
    float           ff;
    complex<double> c;

    f( i );         // a
    f<int>( i );    // b
    f( i, i );      // c
    f( c );         // d
    f( i, ff );     // e   ----->
    f( i, d );      // f
    f( c, &c );     // g
    f( i, &d );     // h
    f( &d, d );     // i
    f( &d );        // j
    f( d, &i );     // k  ----->
    f( &i, &i );    // l ----->
```


**Don’t fully/explicitly specialize function template, just make a plain
old non-template function**

-- This is due to fact that specialization of function templates don't take part in overload resolution
Look at rule 2 and following example


```
// Example 2: Explicit specialization
//
template<class T> // (a) a base template
void f( T );

template<class T> // (b) a second base template, overloads (a)
void f( T* );     //     (function templates can't be partially
                  //     specialized; they overload instead)

template<>        // (c) explicit specialization of (b)
void f<>(int*);

// ...

int *p;
f( p );           // calls (c)
```



```
// Example 3: The Dimov/Abrahams Example
//
template<class T> // (a) same old base template as before
void f( T );

template<>        // (c) explicit specialization, this time of (a)
void f<>(int*);

template<class T> // (b) a second base template, overloads (a)
void f( T* );

// ...

int *p;
f( p );           // calls (b)! overload resolution ignores
                  // specializations and operates on the base
                  // function templates only

If this surprises you, you're not alone; it has surprised a lot of expert
```


**How to make specialization of function templates and overcome limitations for overload resolution :**

If you're writing a function template, prefer to write it as a single function template that should never be
specialized or overloaded, and implement the function template entirely in terms of a class template.
This is the proverbial level of indirection that steers you well clear of the limitations and dark corners of
function templates. This way, programmers using your template will be able to partially specialize and explicitly
specialize the class template to their heart's content without affecting the expected operation of the function
template. This avoids both the limitation that function templates can't be partially specialized, and
the sometimes surprising effect that function template specializations don't overload. Problem solved.

```
template<class T>
struct FImpl;

template<class T>
void f( T t ) { FImpl<T>::f( t ); } // users, don't touch this!

template<class T>
struct FImpl
{
  static void f( T t ); // users, go ahead and specialize this
};

```
