**For Stack why deque is default adapter? why not vector? why not list?**

Q. since we only add elements and remove elements from one side of a stack.Why isn't the
default be vector instead???? why not list since we don't access elements in the middle of the stack?


The reason is that deque is orders of magnitude faster than list. List allocates each element separately, while deque allocates large chunks of elements.

**Similarly for queue why deque is default adapter? why not vector? why not list?**

vector cannot be used for queue adaptor because it doesn't have pop_front.
List is more overhead per element.

**Similarly for priority_queue why vector/deque? why not list?**

Separate question: priority_queue adaptor requires random access and
so can be built using vector or deque but not list (Lippman). Why
does it require random access?

Internally std::priority_queue maintains a heap. Inserting and deleting
elements from a heap requires random access.