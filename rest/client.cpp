#include "client.hpp"

#include "io_service_provider.hpp"
#include "response_header.hpp"

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <string>
#include <sstream>

#include <iostream>

namespace WikiClient
{
    // evil
    bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
    {
        /*
        char subject_name[256];
        X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
        X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
        std::cout << "Verifying " << subject_name << "\n";
        */

        return true;
    }
//####################################################################################
    Client::Client(std::string host, std::string path, bool ssl)
        : host_(std::move(host))
        , path_(std::move(path))
        , ssl_(ssl)
    {

    }
//-----------------------------------------------------------------------------------
    std::string Client::getPage(std::string const& title)
    {
        std::unordered_map <std::string, std::string> map;
        map["titles"] = title;
        map["prop"] = "revisions";
        map["rvprop"] = "content";

        Request req("GET", host_, path_, "query", "jsonfm", map);
        auto res = parseResponse(sendRequest(req));

        if (res.first.responseCode >= 300)
            throw std::runtime_error(res.first.responseMessage);

        auto body = res.second;
        return body;
    }
//-----------------------------------------------------------------------------------
    std::string Client::sendRequest(Request const& request)
    {
        if (ssl_)
            return sendSecureRequest(request);

        using namespace boost::asio;

        std::string requestString = request.getRequestHeader();
        std::stringstream result;

        ip::tcp::iostream stream;
        stream.expires_from_now(boost::posix_time::seconds(10));
        stream.connect(host_, "http");
        stream << requestString;
        stream.flush();

        result << stream.rdbuf();
        return result.str();
    }
//-----------------------------------------------------------------------------------
    std::string Client::sendSecureRequest(Request const& request)
    {
        using namespace boost::asio;

        std::string requestString = request.getRequestHeader();
        std::stringstream result;

        auto& io_service = IOServiceProvider::getInstance().getIOService();

        // resolve address
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(host_, "https");
        boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

        // create ssl context
        ssl::context ctx(ssl::context::sslv23);

        // create socket
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket(io_service, ctx);

        socket.set_verify_mode(boost::asio::ssl::verify_peer);
        socket.set_verify_callback(&verify_certificate);

        try
        {
            boost::asio::connect(socket.lowest_layer(), endpointIterator);

            boost::system::error_code error;
            socket.handshake(boost::asio::ssl::stream_base::client);

            boost::asio::write(socket, boost::asio::buffer(requestString.c_str(), requestString.length()));
            boost::asio::streambuf response;

            while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
            {
                result << &response;
            }
            if (error != boost::asio::error::eof)
                throw boost::system::system_error(error);
        }
        catch (std::exception const& exc) {
            std::cout << exc.what();
        }

        return result.str();
    }
//####################################################################################
}
