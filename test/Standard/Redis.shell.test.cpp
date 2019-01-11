#define BOOST_TEST_MODULE "odbc/Redis.hpp [Empty] tests"

#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>

#include "odbc/Redis.hpp"

BOOST_AUTO_TEST_SUITE(RedisShell)

BOOST_AUTO_TEST_CASE(RedisShellInit) {

    bool success = wsf::redis::init().get();

    BOOST_CHECK_EQUAL(success, false);
}

BOOST_AUTO_TEST_CASE(RedisShellSet) {

    bool isSet = wsf::redis::set("Yo", "Gotti").get();

    BOOST_CHECK_EQUAL(isSet, false);
}

BOOST_AUTO_TEST_CASE(RedisShellGet) {

    std::string value = wsf::redis::get("Yo").get();

    BOOST_CHECK_EQUAL(value, "");
}

BOOST_AUTO_TEST_CASE(RedisShellDel) {

    bool deleted = wsf::redis::del("Yo").get();

    BOOST_CHECK_EQUAL(deleted, false);
}

BOOST_AUTO_TEST_CASE(RedisShellPush) {

    bool pushed = wsf::redis::push("Ayy", "Yo").get();

    BOOST_CHECK_EQUAL(pushed, false);
}

BOOST_AUTO_TEST_CASE(RedisShellList) {

    std::vector<std::string> pushed = wsf::redis::list("Ayy").get();

    BOOST_CHECK_EQUAL(pushed.size(), size_t(0));
}

BOOST_AUTO_TEST_SUITE_END()
