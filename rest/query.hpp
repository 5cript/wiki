#ifndef QUERY_HPP_INCLUDED
#define QUERY_HPP_INCLUDED

#include "SimpleJSON/parse/jsd.h"
#include "SimpleJSON/parse/jsd_convenience.h"
#include "SimpleJSON/parse/jsd_optional.h"
#include "SimpleJSON/stringify/jss.h"
#include "SimpleJSON/stringify/jss_optional.h"
#include "SimpleJSON/stringify/jss_fusion_adapted_struct.h"
#include "SimpleJSON/utility/rename.h"

#include <string>
#include <vector>
#include <map>
#include <sstream>

namespace WikiClient
{
    struct Query;
    struct Page;
	struct Revision;

	using QueryPagesType = std::map <std::string, Page>;
	using RenamedString = JSON::rename <std::string, SJSON_SHORT_STRING("*")>;

    struct Query : public JSON::Stringifiable <Query>
                 , public JSON::Parsable <Query>
    {
        std::map <std::string, Page> pages;
    };

    struct QueryBatch : public JSON::Stringifiable <QueryBatch>
                      , public JSON::Parsable <QueryBatch>
    {
        std::string batchcomplete;
        boost::optional <Query> query;
    };

    struct Revision : public JSON::Stringifiable <Revision>
                    , public JSON::Parsable <Revision>
    {
        std::string contentformat;
        std::string contentmodel;
		JSON::rename <std::string, SJSON_SHORT_STRING("*")> content;
    };

    struct Page : public JSON::Stringifiable <Page>
                , public JSON::Parsable <Page>
    {
        uint64_t pageid;
        uint64_t ns;
        std::string title;
        std::vector <Revision> revisions;
    };
}

BOOST_FUSION_ADAPT_STRUCT(
	WikiClient::QueryBatch,
	(std::string, batchcomplete)
	(boost::optional <WikiClient::Query>, query)
)

BOOST_FUSION_ADAPT_STRUCT(
	WikiClient::Query,
	(WikiClient::QueryPagesType, pages)
)

BOOST_FUSION_ADAPT_STRUCT(
	WikiClient::Revision,
	(std::string, contentformat)
	(std::string, contentmodel)
	(WikiClient::RenamedString, content)
)

BOOST_FUSION_ADAPT_STRUCT(
	WikiClient::Page,
	(uint64_t, pageid)
	(uint64_t, ns)
	(std::string, title)
	(std::vector <WikiClient::Revision>, revisions)
)


#endif // QUERY_HPP_INCLUDED
