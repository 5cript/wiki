#ifndef QUERY_HPP_INCLUDED
#define QUERY_HPP_INCLUDED

#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "../SimpleJSON/parse/jsd.h"
#   include "../SimpleJSON/parse/jsd_convenience.h"
#   include "../SimpleJSON/parse/jsd_optional.h"
#   include "../SimpleJSON/stringify/jss.h"
#   include "../SimpleJSON/stringify/jss_optional.h"
#   include "../SimpleJSON/stringify/jss_fusion_adapted_struct.h"
#endif

#include <string>
#include <vector>
#include <map>
#include <sstream>

namespace WikiClient
{
    struct Query;
    struct Page;
    struct Revision;

    struct Query : public JSON::FusionStruct <Query>
                 , public JSON::ParsableStruct <Query>
    {
        std::map <std::string, Page> pages;
    };

    struct QueryBatch : public JSON::FusionStruct <QueryBatch>
                      , public JSON::ParsableStruct <QueryBatch>
    {
        std::string batchcomplete;
        boost::optional <Query> query;
    };

    struct Revision : public JSON::FusionStruct <Revision>
                    , public JSON::ParsableStruct <Revision>
    {
        std::string contentformat;
        std::string contentmodel;
        JSON::rename <std::string, SHORT_STRING("*")> content;
    };

    struct Page : public JSON::FusionStruct <Page>
                , public JSON::ParsableStruct <Page>
    {
        uint64_t pageid;
        uint64_t ns;
        std::string title;
        std::vector <Revision> revisions;
    };
}

BOOST_FUSION_ADAPT_STRUCT(WikiClient::QueryBatch, batchcomplete, query)
BOOST_FUSION_ADAPT_STRUCT(WikiClient::Query, pages)
BOOST_FUSION_ADAPT_STRUCT(WikiClient::Revision, contentformat, contentmodel, content)
BOOST_FUSION_ADAPT_STRUCT(WikiClient::Page, pageid, ns, title, revisions)

#endif // QUERY_HPP_INCLUDED
