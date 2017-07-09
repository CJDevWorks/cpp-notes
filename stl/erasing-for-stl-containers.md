# erasing-for-stl-containers

(1) For contiguous-memory, sequence-based containers (vector, deque,
string), use the erase-remove(-if)-idiom:

```
int main(int argc, char * argv [])
 {
     std::vector<int> vec(10);
    
     auto gen = std::mt19937(static_cast<unsigned>(time(nullptr)));
                            
     auto dist = std::uniform_int_distribution<short>(1, 5);
    
     auto random = std::bind(dist, gen);
    
     auto itr = std::ostream_iterator<int>(std::cout, " ");
    
     // Output: 2 4 5 2 3 1 2 3 4 4
     for (auto& i : vec) itr = i = random();
    
     // std::remove partitions the vector so that all elements matching
     // '3' are at the end of the vector. It returns the iterator to the
     // first of the matched elements, so that eraseing from there to
the
     // end of the vector erases all the '3's
     vec.erase(std::remove(vec.begin(), vec.end(), 3), vec.end());
    
     std::cout << std::endl;
    
     // Output: 2 4 5 2 1 2 4 4
     for (auto& i : vec) itr = i;
    
     vec.erase(std::remove_if(vec.begin(),
                              vec.end(),
                              [&] (int x) { return x > 3; }),
               vec.end());
    
     std::cout << std::endl;
    
     // Output: 2 2 1 2
     for (auto& i : vec) itr = i;

}
```

(2) For std::list, use the remove and remove_if member function:

```
int main(int argc, char * argv [])
 {
     std::list<int> list(10);
    
     auto gen = std::mt19937(static_cast<unsigned>(time(nullptr)));
                            
     auto dist = std::uniform_int_distribution<short>(1, 5);
    
     auto random = std::bind(dist, gen);
    
     auto itr = std::ostream_iterator<int>(std::cout, " ");
    
     // Output: 2 5 4 1 1 4 5 5 3 3
     for (auto& i : list) itr = i = random();
    
     list.remove(3);
    
     std::cout << std::endl;
    
     // Output: 2 5 4 1 1 4 5 5
     for (auto& i : list) itr = i;
    
     list.remove_if([&] (int x) { return x > 3; });
    
     std::cout << std::endl;
    
     // Output: 2 1 1
     for (auto& i : list) itr = i;

}
```

(3) For associative containers (std::map), walk the container:
Note remove_if can't be applied.

```
int main(int argc, char * argv [])
 {
     std::map<int, int> map;
    
     auto gen = std::mt19937(static_cast<unsigned>(time(nullptr)));
                            
     auto dist = std::uniform_int_distribution<short>(1, 5);
    
     auto random = std::bind(dist, gen);
    
     auto itr = std::ostream_iterator<int>(std::cout, " ");
    
     for (int i = 0; i < 10; ++i) itr = map[i] = random();
    
     // Output: 4 4 4 4 4 3 3 3 5 1
     for (auto& i : map) if (i.second == 3) map.erase(i.first);
    
     std::cout << std::endl;
    
     // Output: 4 4 4 4 4 3 5 1
     for (auto& i : map) itr = i.second;
    
     for (auto& i : map) if (i.second > 3) map.erase(i.first);
    
     std::cout << std::endl;
    
     // Output: 4 4 4 3 1
     for (auto& i : map) itr = i.second;

}
```

C++98

```
map<string, SOME_TYPE>::iterator pm_it = port_map.begin();
while(pm_it != port_map.end())
{
    if (pm_it->second == delete_this_id)
    {
        port_map.erase(pm_it++);  // Use iterator.
                                  // Note the post increment.
                                  // Increments the iterator but returns the
                                  // original value for use by erase
    }
    else
    {
        ++pm_it;           // Can use pre-increment in this case
                           // To make sure you have the efficient version
    }
}
```