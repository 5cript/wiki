#include "response_header.hpp"

#include <sstream>

namespace WikiClient
{
    std::pair <ResponseHeader, std::string /*body*/> parseResponse(std::string const& response)
    {
        std::stringstream sstr;

        sstr << response;

        ResponseHeader head;

        sstr >> head.httpVersion;
        sstr >> head.responseCode;
        std::getline(sstr, head.responseMessage);

        head.responseMessage.pop_back();

        head.httpVersion = head.httpVersion.substr(5, head.httpVersion.length() - 5);

        if (head.httpVersion != "1.0" && head.httpVersion != "1.1")
            throw std::runtime_error("unsupported http version");

        std::string headerLine;
        while(std::getline(sstr, headerLine))
        {
            if (headerLine == "\r")
                break;

            auto pos = headerLine.find(":");
            if (pos == std::string::npos)
                throw std::runtime_error("HTTP header entry does not contain colon");

            auto lhs = headerLine.substr(0, pos);
            auto rhs = headerLine.substr(pos + 1, headerLine.length() - pos);

            head.entries[lhs] = rhs;
        }

        return {
            head,
            response.substr(sstr.tellg(), response.length() - sstr.tellg())
        };
    }
}
