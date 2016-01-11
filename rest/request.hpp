#ifndef REST_REQUEST_HPP_INCLUDED
#define REST_REQUEST_HPP_INCLUDED

#include <string>
#include <unordered_map>

namespace WikiClient
{
    class Request
    {
    public:
        std::string getRequestUrl() const;
        std::string getRequestHeader() const;

        Request(std::string type, std::string host, std::string pathPrefix,
                std::string action, std::string format,
                std::unordered_map <std::string, std::string> parameters); // can not be created on its own.

    private:
        std::string type_;
        std::string host_;
        std::string pathPrefix_;
        std::string action_;
        std::string format_;
        std::unordered_map <std::string, std::string> parameters_;
    };
}

#endif // REST_REQUEST_HPP_INCLUDED
