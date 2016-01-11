#include "rest/request.hpp"
#include "rest/client.hpp"

#include <iostream>
#include <fstream>

int main()
{
    using namespace WikiClient;

    Client c("localhost", "/mediawiki", false);

    std::ofstream writer ("test.html", std::ios_base::binary);
    writer << c.getPage("Hauptseite");

    return 0;
}
