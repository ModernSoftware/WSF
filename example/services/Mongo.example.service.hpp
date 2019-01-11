#include "Shared.hpp"
#include "odbc/Mongo.hpp"

#ifndef _MONGO_SERVICE_SAMPLE_H
#define _MONGO_SERVICE_SAMPLE_H 1

namespace wsf { namespace service { namespace mongo {

    namespace insert {

        web::json::value one(web::json::value result) {
            web::json::value sampleData;
            sampleData["hello"] = web::json::value::string("world");

            auto task = wsf::mongo::insert::one("test", sampleData);
            bool success = task.get();

            result["insertedData"] = sampleData;
            result["success"] = web::json::value(success);

            return result;
        }

        web::json::value many(web::json::value result) {
            web::json::value sampleData;
            sampleData[0]["hello"] = web::json::value::string("world");
            sampleData[1]["hello"] = web::json::value::string("world");
            sampleData[2]["hello"] = web::json::value::string("world 1");
            sampleData[3]["hello"] = web::json::value::string("world 2");
            sampleData[4]["hello"] = web::json::value::string("world 3");

            auto task = wsf::mongo::insert::many("test", sampleData);
            bool success = task.get();

            result["insertedData"] = sampleData;
            result["success"] = web::json::value(success);

            return result;
        }

    }

    namespace update {

        web::json::value one(web::json::value result) {
            web::json::value filterData;
            filterData["hello"] = web::json::value::string("world");

            web::json::value newData;
            newData["updated"] = true;

            web::json::value options;
            options["upsert"] = true;

            auto task = wsf::mongo::update::one("test", filterData, newData, options);
            bool success = task.get();

            result["success"] = web::json::value(success);

            return result;
        }

        web::json::value many(web::json::value result) {
            web::json::value filterData;
            filterData["hello"] = web::json::value::string("world");

            web::json::value newData;
            newData["updated_all"] = true;

            web::json::value options;
            options["upsert"] = true;

            auto task = wsf::mongo::update::many("test", filterData, newData, options);
            bool success = task.get();

            result["success"] = web::json::value(success);

            return result;
        }

    }

    namespace find {

        web::json::value one(web::json::value result) {
            auto task = wsf::mongo::find::one("test");
            result["data"] = task.get();

            return result;
        }

        web::json::value many(web::json::value result) {
            auto task = wsf::mongo::find::many("test");
            result["data"] = task.get();

            return result;
        }

    }

    namespace remove {

        web::json::value one(web::json::value result) {
            web::json::value filterData;
            filterData["hello"] = web::json::value::string("world 2");

            auto task = wsf::mongo::remove::one("test", filterData);
            bool success = task.get();

            result["success"] = web::json::value(success);

            return result;
        }

        web::json::value many(web::json::value result) {
            web::json::value filterData;
            filterData["hello"] = web::json::value::string("world");

            auto task = wsf::mongo::remove::many("test", filterData);
            bool success = task.get();

            result["success"] = web::json::value(success);

            return result;
        }

    }

}   }   }

#endif
