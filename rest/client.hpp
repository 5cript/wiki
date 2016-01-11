#ifndef REST_CLIENT_HPP_INCLUDED
#define REST_CLIENT_HPP_INCLUDED

#include "request.hpp"

#include <string>

namespace WikiClient
{
    class Client
    {
    public:
        Client(std::string host, std::string path, bool ssl = false);

        std::string getPage(std::string const& title);

    private:
        std::string sendRequest(Request const& request);
        std::string sendSecureRequest(Request const& request);

    private:
        std::string host_;
        std::string path_;
        bool ssl_;
    };
}

#endif // REST_CLIENT_HPP_INCLUDED
