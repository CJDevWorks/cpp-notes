# using-find,-equal_range-and-other-algorithms

~~Edit~~



USING find, equal_range AND OTHER ALGORITHMS


There are many ways to find or lookup an element in a sequence:

    * `find`
    * `equal-range`
    * `binary_search`
    * `count`
    * `lower_bound`
    * `upper_bound`

However each answer a different question.


Unsorted Ranges

To search for the first occurrence of an element in an unsorted sequence
you should use std::find:

    std::vector<std::size_t> v = {1, 3, 2, 7, 5};

    auto itr = std::find(v.begin(), v.end(), 2);

    if (itr != v.end()) std::cout << "Found!";

    else std::cout << "Not found!";

If you want to know how many elements of a given value are in a
sequence, you would use std::count. You may also be tempted to use
std::count for existance check, however it is less efficient than
std::find, because for a successful search std::find would terminate
while std::count would look through the entire range.


Sorted Ranges

For a sorted range (but not a set/map), things are very different. To
check for existence, use std::binary_search:

    std::vector<std::size_t> v = {1, 2, 3, 4, 5};

    if (std::binary_search(v.begin(), v.end(), 3)) std::cout << "Found!";

    else std::cout << "Not found!";

The next part is IMPORTANT. To look for the first occurrence of the
value, do not use std::find. Also do not use std::lower_bound, but
rather std::equal_range:

    std::vector<std::size_t> v = {1, 2, 3, 4, 5};

    auto pair = std::equal_range(v.begin(), v.end(), 3);

    // Do something with pair.first
    if (pair.first != pair.second) std::cout << "Found!";

    else std::cout << "Not found!";

Why not std::lower_bound? Because you would have to first check if the
returned iterator is not the end, and then if the returned value is the
value you are looking for (since lower_bound returns the first value
_not less_, i.e. _greater or equal_ to whatever you passed it). You
would most likely do it like so:

    std::vector<std::size_t> v = {1, 2, 3, 4, 5};

    auto itr = std::lower_bound(v.begin(), v.end(), 3);

    if (itr != v.end() && *itr == 3) std::cout << "Found!";

    else std::cout << "Not found!";

However, std::lower_bound works with _equivalence_, not equality! Thus
it would have to look like so, which is too much of a hassle:

    std::vector<std::size_t> v = {1, 2, 3, 4, 5};

    auto itr = std::lower_bound(v.begin(), v.end(), 3);

    if (itr != v.end() && ! (*itr < 3) && !(3 < *itr)) std::cout << "Found!";

    else std::cout << "Not found!";

Moreover, you can also get a cheaper counting-algorithm through
std::equal_range than through the linear std::count, because the count,
i.e. the number of values matching the value you passed
std::equal_range, is equal to std::distance(pair.begin(), pair.end()).


Associative containers (set/map)

For std::set, std::mulitset, std::map and std::multimap, the main rule
is to use their member methods rather than the non-member algorithms,
i.e. std::set::count instead of std::count, for example. Same also goes
for std::list, by the way.


Putting it all together

  Your question                       Unsorted Range   Sorted Range                       std::set/std::map
  ----------------------------------- ---------------- ---------------------------------- -------------------
  Does the value exist?               std::find        std::binary_search                 member find
  Where is the first such value?      std::find        std::equal_range                   member find
  How many objects have that value?   std::count       std::equal_range + std::distance   member count
