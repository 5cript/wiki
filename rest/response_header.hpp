#ifndef REST_RESPONSE_HEADER_HPP_INCLUDED
#define REST_RESPONSE_HEADER_HPP_INCLUDED

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace WikiClient
{
    struct ResponseHeader
    {
        std::string httpVersion;
        int responseCode;
        std::string responseMessage;

        std::unordered_map <std::string, std::string> entries;
    };

    std::pair <ResponseHeader, std::string /*body*/> parseResponse(std::string const& response);
}

#endif // REST_RESPONSE_HEADER_HPP_INCLUDED
