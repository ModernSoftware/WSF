#define BOOST_TEST_MODULE "Config.hpp tests"

#include <boost/test/unit_test.hpp>
#include <string>

#include "Config.hpp"

BOOST_AUTO_TEST_SUITE(Config)

BOOST_AUTO_TEST_CASE(ConfigVariables) {

    // Server Config
    BOOST_CHECK_EQUAL(wsf::config::host, "http://0.0.0.0");
    BOOST_CHECK_EQUAL(wsf::config::port, "3000");
    BOOST_CHECK_EQUAL(wsf::config::cors, "*");

    // Mongo Driver Config
    BOOST_CHECK_EQUAL(wsf::config::mongo, "mongodb://localhost:27017");
    BOOST_CHECK_EQUAL(wsf::config::mongodb, "wsf");

    // Redis Driver Config
    BOOST_CHECK_EQUAL(wsf::config::redis, "localhost");
    BOOST_CHECK_EQUAL(wsf::config::redisPort, 6379);
    BOOST_CHECK_EQUAL(wsf::config::redisTimeout, 3);

}

BOOST_AUTO_TEST_SUITE_END()
