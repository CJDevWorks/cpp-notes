
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <iterator>

std::vector<int> v{1,4,5,6,2,3,11, 12, 10, 18, 7,8,9};

void print(int i)
{
    std::cout << i << std::endl;
}

int main(int argc, char** argv)
{

        auto predicate = [&] (int* a, int* b) { return *a < *b; };
        std::set<int*, decltype(predicate)> ptrs({
                                                         new int(5),
                                                         new int(-1),
                                                         new int(10)}, predicate);
        for (const auto& i : ptrs) print(*i); // -1 5 10
        for (auto& i : ptrs) delete i;

    std::sort(v.begin(), v.end(), [](int a, int b){ return a < b;});
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout , " "));
    //auto found = std::binary_search(v.begin(), v.end(), 100);
    bool found = false;
    auto pair =  std::equal_range(v.begin(), v.end(), 10);

    if(pair.first != pair.second)
        found = true;

    auto it1 = std::lower_bound(v.begin(), v.end(), 10);
    auto it2 = std::upper_bound(v.begin(), v.end(), 10);

    bool found1 = (it1 != v.end() && it2 != v.end() && it1 == it2);

    std::cout << std::endl << " found:" << found1 << std::endl;
}