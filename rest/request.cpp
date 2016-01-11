#include "request.hpp"

#include <sstream>
#include <iomanip>

namespace WikiClient
{
//####################################################################################
    std::string Request::getRequestUrl() const
    {
        std::string result = pathPrefix_ + "/api.php?";
        result += "action=" + action_;
        if (!format_.empty())
            result += "&format=" + format_;

        for (auto const& i : parameters_)
        {
            std::stringstream arg;
            for (auto const& j : i.second) {
                if (j <= 32)
                    arg << '%' << std::hex << std::setw(2) << (int)j;
                else
                    arg << j;
            }
            result += std::string("&") + i.first + "=" + arg.str();
        }
        return result;
    }
//-----------------------------------------------------------------------------------
    std::string Request::getRequestHeader() const
    {
        std::stringstream request;
        request << type_ << " " << getRequestUrl() << " HTTP/1.1\r\n";
        request << "Host: " << host_ << "\r\n";
        request << "Connection: close\r\n\r\n";

        return request.str();
    }
//-----------------------------------------------------------------------------------
    Request::Request(std::string type, std::string host, std::string pathPrefix,
                     std::string action, std::string format,
                     std::unordered_map <std::string, std::string> parameters)
        : type_(std::move(type))
        , host_(std::move(host))
        , pathPrefix_(std::move(pathPrefix))
        , action_(std::move(action))
        , format_(std::move(format))
        , parameters_(std::move(parameters))
    {
    }
//####################################################################################
}
