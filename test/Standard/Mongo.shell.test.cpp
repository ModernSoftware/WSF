#define BOOST_TEST_MODULE "odbc/Mongo.hpp [Empty] tests"

#include <boost/test/unit_test.hpp>
#include <string>

#include "Shared.hpp"
#include "odbc/Mongo.hpp"

BOOST_AUTO_TEST_SUITE(MongoShell)

BOOST_AUTO_TEST_CASE(MongoShellInsertOne) {

    web::json::value data;
    data["data"] = web::json::value("hello world");

    auto task = wsf::mongo::insert::one("test", data);
    bool success = task.get();

    BOOST_CHECK_EQUAL(success, false);
}

BOOST_AUTO_TEST_CASE(MongoShellInsertMany) {

    web::json::value data;
    data[0]["data"] = web::json::value("hello world");
    data[1]["data"] = web::json::value("hello world");

    auto task = wsf::mongo::insert::many("test", data);
    bool success = task.get();

    BOOST_CHECK_EQUAL(success, false);
}

BOOST_AUTO_TEST_CASE(MongoShellUpdateOne) {

    web::json::value filter;
    filter["data"] = web::json::value("hello world");
    web::json::value data;
    data["updated"] = web::json::value(true);
    web::json::value options;
    options["upsert"] = web::json::value(true);

    auto task = wsf::mongo::update::one("test", filter, data, options);
    bool success = task.get();

    BOOST_CHECK_EQUAL(success, false);
}

BOOST_AUTO_TEST_CASE(MongoShellUpdateMany) {

    web::json::value filter;
    filter["data"] = web::json::value("hello world");
    web::json::value data;
    data["updated"] = web::json::value(true);
    web::json::value options;
    options["upsert"] = web::json::value(true);

    auto task = wsf::mongo::update::many("test", filter, data, options);
    bool success = task.get();

    BOOST_CHECK_EQUAL(success, false);
}

BOOST_AUTO_TEST_CASE(MongoShellFindOne) {

    web::json::value filter = web::json::value::parse("{}");
    web::json::value options = web::json::value::parse("{}");

    auto task = wsf::mongo::find::one("test", filter, options);
    web::json::value data = task.get();

    web::json::value compare = web::json::value::parse("{}");

    BOOST_CHECK_EQUAL(data.is_object(), compare.is_object());
}

BOOST_AUTO_TEST_CASE(MongoShellFindMany) {

    web::json::value filter = web::json::value::parse("{}");
    web::json::value options = web::json::value::parse("{}");

    auto task = wsf::mongo::find::many("test", filter, options);
    web::json::value data = task.get();

    BOOST_CHECK_EQUAL(data.is_array(), true);
    BOOST_CHECK_EQUAL(data.as_array().size(), 0);
}

BOOST_AUTO_TEST_CASE(MongoShellRemoveOne) {

    web::json::value filter;
    filter["data"] = web::json::value("hello world");

    auto task = wsf::mongo::remove::one("test", filter);
    bool success = task.get();

    BOOST_CHECK_EQUAL(success, false);
}

BOOST_AUTO_TEST_CASE(MongoShellRemoveMany) {

    web::json::value filter;
    filter["data"] = web::json::value("hello world");

    auto task = wsf::mongo::remove::many("test", filter);
    bool success = task.get();

    BOOST_CHECK_EQUAL(success, false);
}

BOOST_AUTO_TEST_SUITE_END()
