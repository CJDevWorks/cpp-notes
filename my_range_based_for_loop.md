/*
for ( range_declaration : range_expression ) loop_statement
this loop is equivalent to the following expanded code:

{
    auto && __range = range_expression;
    for (auto __begin = __range.begin(),
                 __end = __range.end();
         __begin != __end; ++__begin)
    {
        range_declaration = *__begin;
        loop_statement
    }
}
 */

so what are requirements :

1. begin() and end()
2. operator !=
3. operator ++ (prefix)
4. operator *

=================

Q. Define your own container class - fixed size container and then define iterator on it
such that it satisfies for loop requirement.

Sol. Look class_design/my_container class

