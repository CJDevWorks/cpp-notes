###### Proxied Containers and STL Assumptions - std::vector<bool> and std::bitset
1. vector<bool> is not a container.

2. vector<bool> attempts to illustrate how to write standard-conforming proxied containers that do
 extra work invisibly under the covers. Unfortunately, that's not a sound idea, because although
 a proxied collection can be an important and useful tool, by definition it must violate the
 standard's container requirements and therefore can never be a conforming container. (See #1.)

      Corollary: Go ahead and write proxied collections, but don't attempt to write ones that
      still meet the standard's container or sequence requirements. First, it's not possible.
      Second, the main reason to conform to the standard container requirements is to be used with
       the standard algorithms, yet the standard algorithms are typically inappropriate for
       proxied containers because proxied containers have different performance characteristics
       than plain-and-in-memory containers.

3. vector<bool>'s name is a trifle misleading because the things inside aren't even standard bools.
 A standard bool is at least as big as a char, so that it can be used "normally." So, in fact,
 vector<bool> does not even really store bools, despite the name.

4. vector<bool> forces a specific optimization on all users by enshrining it in the standard.
That's probably not a good idea, even if the actual performance overhead turns out to be
negligible for a given compiler for most applications; different users have different requirements.

