#define BOOST_TEST_MODULE "odbc/Redis.hpp tests"

#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>

#include "Shared.hpp"
#include "odbc/Redis.hpp"

BOOST_AUTO_TEST_SUITE(Redis)

BOOST_AUTO_TEST_CASE(RedisInit) {

    bool success = wsf::redis::init().get();

    BOOST_CHECK_EQUAL(success, true);
}

BOOST_AUTO_TEST_CASE(RedisSet) {

    bool isSet = wsf::redis::set("Yo", "Gotti").get();

    BOOST_CHECK_EQUAL(isSet, true);
}

BOOST_AUTO_TEST_CASE(RedisGet) {

    std::string value = wsf::redis::get("Yo").get();

    BOOST_CHECK_EQUAL(value, "Gotti");
}

BOOST_AUTO_TEST_CASE(RedisDel) {

    bool deleted = wsf::redis::del("Yo").get();

    BOOST_CHECK_EQUAL(deleted, true);
}

BOOST_AUTO_TEST_CASE(RedisPush) {
    
    bool deleted = wsf::redis::del("Ayy").get();

    BOOST_CHECK_EQUAL(deleted, true);

    bool pushed = wsf::redis::push("Ayy", "Yo").get();

    BOOST_CHECK_EQUAL(pushed, true);
}

BOOST_AUTO_TEST_CASE(RedisList) {

    std::vector<std::string> list = wsf::redis::list("Ayy").get();

    BOOST_CHECK_EQUAL(list.size(), size_t(1));
    BOOST_CHECK_EQUAL(list[0], "Yo");
}

BOOST_AUTO_TEST_SUITE_END()
