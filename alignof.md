# alignof

Each type has an alignment requirement. Generally, this is so variables of the type can be accessed efficiently, without having to cause the CPU to generate more than one read/write access in order to reach any given member of the datatype. Furthermore, it also ensure efficient copying of the entire variable. alignof will return the alignment requirement for the given type.

alignas is used to force an alignment on a datatype (so long as it is not less stringent that what alignof said datatype would return)

To get the alignment requirements of a type use the alignof keyword or
std::alignment_of<Type>::value.

std::alignment_of<Base>::value == alignof(Base);

Whats alignement , padding and size of through example :

for a struct such as
struct
{
char c;
double d;
int32_t i; } Mystruct;

 on a typical implementation, you have:

Set Offset to 0.
1. char requires alignment of 1, so Offset is already a multiple of 1 (0*1 is 0). Put c at this offset, 0. Add the size of c, 1, to Offset, making it 1.

2. double requires alignment of 8, so add 7 to Offset, making it 8. Put d at this offset, 8. Add the size of d, 8, to Offset, making it 16.


3. int requires alignment of 4, so Offset is already a multiple of 4 (4*4 is 16). Put i at this offset, 16. Add the size of i, 4, to Offset, making it 20.

**At the end, the largest alignment required was 8, so add 4 to Offset, making it 24. The size of this struct is 24 bytes.**

Observe that the above has nothing to do with any word size of the machine. It only uses the alignment requirement of each member. The alignment requirement can be different for each type, and it can be different from the size of the type, and the above will still work.

(The algorithm breaks if alignment requirements are not powers of two. That could be fixed by making the last step increase the offset to be a multiple of the least common multiple of all the alignments.)


