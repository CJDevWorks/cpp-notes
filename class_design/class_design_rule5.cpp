#include <iostream>
#include <vector>
#include <string>

using namespace std;

class SearchQuery{

};

class DirectorySearchResult
{
public:
    DirectorySearchResult(
            std::vector<std::string> const& files,
            size_t attributes,
            SearchQuery const* query)
            : files(files),
              attributes(attributes),
              query(new SearchQuery(*query))
    { }

    ~DirectorySearchResult() { if (query != nullptr) delete query; } // owns resource.

    DirectorySearchResult(DirectorySearchResult const& other)
    :   files(other.files)
    ,   attributes(other.attributes)
    ,   query(other.query? nullptr: new SearchQuery{*other.query})
        // two objects can't both point to same resource, double delete.
        {}

    DirectorySearchResult(DirectorySearchResult&& other) noexcept
        :   files(std::move(other.files))
        ,   attributes(other.attributes)
        ,   query(other.query)
    {
        other.query = 0;
        // imp to make it zero after move , other wise delete will cause problem
    }

    DirectorySearchResult& operator=(DirectorySearchResult const& other)
    {
        if (this != &other)
        {
            SearchQuery* tmpQuery = other.query? new SearchQuery(other.query) : nullptr;
            std::swap(query,tmpQuery);
            delete tmpQuery;
            files = other.files;
            attributes = other.attributes;
        }
        return *this;
    }

    DirectorySearchResult&& operator=(DirectorySearchResult && other)
    {
        //if (this != &other) // not required as move constructor is for temporories
        {
            files = std::move(other.files);
            attributes = other.attributes;
            std::swap(query ,other.query);
            other.query = 0;
        }
    }

private:
    std::vector<std::string> files;
    size_t attributes;
    SearchQuery* query;
};
