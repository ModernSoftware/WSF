#define BOOST_TEST_MODULE "services/ServerData.hpp tests"

#include <boost/test/unit_test.hpp>
#include <string>

#include "Shared.hpp"
#include "services/Server.service.hpp"

BOOST_AUTO_TEST_SUITE(ServerData)

BOOST_AUTO_TEST_CASE(ServerDataResponse) {

    web::json::value placeholder;
    web::json::value info = wsf::service::metadata(placeholder);

    BOOST_CHECK_EQUAL(info["version"].as_string(), "0.0.1");
    BOOST_CHECK_EQUAL(info["server"].as_string(), "WSF");

}

BOOST_AUTO_TEST_SUITE_END()
