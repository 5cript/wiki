#include "io_service_provider.hpp"

namespace WikiClient {

    IOServiceProvider::IOServiceProvider()
        : ioService()
    {
    }

    boost::asio::io_service& IOServiceProvider::getIOService()
    {
        return ioService;
    }

}
