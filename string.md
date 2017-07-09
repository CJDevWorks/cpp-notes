
- String(C & C++ style) and array of string are completly different.
Latter is fixed but format can grow.

- In addition, C++ strings are not null-terminated, so they can store null bytes,unlike C strings.
 Multiple copies of the same string share the same underlying buffer whenever possible. But
 because a string is mutable, new buffers are created as necessary.

- Differrence char array and char*
  1. First off, in function arguments, they are exactly equivalent:
     void foo(char *x);
     void foo(char x[]);
     exactly the same in all respects (note! this only applies if the brackets are empty)

  2. In other contexts, char * allocates a pointer, while char [] allocates an array.
     Where does the string go in the former case, you ask? The compiler secretly allocates a
     static anonymous array to hold the string literal. So:

     char *x = "Foo"; // is approximately equivalent to:
     static const char __secret_anonymous_array[] = "Foo";
     char *x = (char *) __secret_anonymous_array;

     Note that you must not ever attempt to modify the contents of this anonymous array via
     this pointer; the effects are undefined (often meaning a crash):
     x[1] = 'O'; // BAD. DON'T DO THIS.

     Using the array syntax directly allocates it into new memory. Thus modification is safe:
     char x[] = "Foo";
     x[1] = 'O'; // No problem.

  3. char text[10] = ""; // is equivalent to ==> char text[10] = { '\0' }; first explicit rest implicit

  4. char text[5] = { 'H', 'e', 'l', 'l', 'o' }; // No room for terminating zero

  5. char buf [10]; // ==> you will have random content in all the elements.

  6. char *cstr1 = "hello";
     *(cstr1)='t';


  7. char *cstr2; //ERROR
     strcpy(cstr2, "hello");
     *(cstr2)='t';

     // Allocate memory :
     char *cstr2 = (char*)malloc(strlen("hello")+1);

  8. char cstr3[100];
     cstr3 = "hello";  // array name decays into a pointer to first value of array, It cant be assigned
     *(cstr3)='t';

     int a[100];
     int b[100];
     ...
     a = b;     //error


  9.  char cstr4[100] = "hello";
      *(cstr4)='t';

  10. /*returns the length of the string without null char */
      int strlen(const char*);

      /*copies the 2nd string into the 1st*/
      char* strcpy(char*, const char*);

      /*compares two strings*/
      int strcmp(const char*, const char*)

       /*char *a = strdup("stack overflow"); */
       The strdup() function returns a pointer to a new string which is a duplicate of the string  s.
       Memory for the new string is obtained with malloc(3), and can be freed with free(3).

       char nameArr[12] = "Alan Turing";
	   const char *namePtrConstChar = "Edsger W. Dijkstra";
	   char *ptr;

       // 1. copying - stack
       ptr = nameArr;

       // Error
       // nameArr = namePtrConstChar;

       // 2. copying - heap
	   ptr = new char[strlen(nameArr) + 1];
	   strcpy(ptr, nameArr);
	   delete [] ptr;

  11. std::string ::: --
      s1<s2
      Lexicographical comparison of string values; s1 or s2, but not both, can be a C-style string.

      s1==s2
      Comparison of string values; s1 or s2, but not both, can be a C-style string.

  12. use the cin to get a numeric or a single word, but we need to use getline() for an input with spaces.

  13. To convert string to other data type : stringstream

  14.  To reset stringstream:
      ss.str("");
      ss.clear();

whats will change :p, or what it points to and what it will return

```
*p++
```

The postfix ++ and -- operators essentially have higher precedence than the prefix unary operators.

*p++ ==> *(p++) // p is increased but it return value p was pointer before(postfix)

Alternative : (*p)++ and ++*p

