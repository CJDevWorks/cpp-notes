#include <iostream>
#include <mutex>
#include <unordered_map>

class Sample_CRef_MEM_MTX
{
    const std::string testname;
    int&  testId;
    using USERCache = std::unordered_map<int, std::string>;

    USERCache cache_;
    std::mutex mtx;

public:
    // can it have a default constructor??
    // can it initilize variables in constructor body
    // what about constexpr and noexcept
    Sample_CRef_MEM_MTX()
};
