#include "rest/request.hpp"

#include <iostream>

int main()
{
    using namespace WikiClient;

    std::unordered_map <std::string, std::string> map;
    map["titles"] = "Main Page";

    Request req("GET", "en.wikipedia.org", "query", "", map);

    std::cout << req.getRequestHeader();
    return 0;
}
