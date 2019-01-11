#include "Shared.hpp"
#include "odbc/Redis.hpp"

#ifndef _REDIS_SERVICE_SAMPLE_H
#define _REDIS_SERVICE_SAMPLE_H 1

namespace wsf { namespace service { namespace redis {

    web::json::value set(web::json::value result) {
        web::json::value data;

        std::string key = "redis_test";
        std::string value = "testing";
        bool success = wsf::redis::set(key, value).get();

        data["success"] = web::json::value(success);
        data["key"] = web::json::value(key);
        data["value"] = web::json::value(value);

        return data;
    }

    web::json::value get(web::json::value result) {
        web::json::value data;

        std::string key = "redis_test";
        std::string value = wsf::redis::get(key).get();

        data["key"] = web::json::value(key);
        data["value"] = web::json::value(value);

        return data;
    }

    web::json::value del(web::json::value result) {
        web::json::value data;

        std::string key = "redis_test";
        bool deleted = wsf::redis::del(key).get();

        data["key"] = web::json::value(key);
        data["deleted"] = web::json::value(deleted);

        return data;
    }

    web::json::value push(web::json::value result) {
        web::json::value data;

        std::string key = "redis_test_list";
        std::string value = "hello";
        bool pushed = wsf::redis::push(key, value).get();

        data["key"] = web::json::value(key);
        data["value"] = web::json::value(value);
        data["pushed"] = web::json::value(pushed);

        return data;
    }

    web::json::value list(web::json::value result) {
        web::json::value data;

        std::string key = "redis_test_list";
        std::vector<std::string> values = wsf::redis::list(key).get();

        int vecSize = (int) values.size();

        for (int i = 0; i < vecSize; i++) {
            data["values"][i] = web::json::value(values[i]);
        }

        data["key"] = web::json::value(key);
        data["listSize"] = web::json::value(vecSize);

        return data;
    }

}   }   }
#endif