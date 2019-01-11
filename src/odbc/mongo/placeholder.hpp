#include "../../Shared.hpp"
#include "../../Config.hpp"

#ifndef _MONGO_API_H
#define _MONGO_API_H 1
    namespace wsf { namespace mongo {

        namespace insert {

            pplx::task<bool> one(std::string collection, web::json::value data) {
                return pplx::task<bool>([=] {
                    return false;
                });
            }

            pplx::task<bool> many(std::string collection, web::json::value data) {
                return pplx::task<bool>([=] {
                    return false;
                });
            }

        }

        namespace find {

            pplx::task<web::json::value> one(std::string collection, web::json::value filter = web::json::value::parse("{}"), web::json::value optionsParams = web::json::value::parse("{}")) {
                return pplx::task<web::json::value>([=] {
                    web::json::value placeholder;
                    placeholder = web::json::value::parse("{}");
                    return placeholder;
                });
            }

            pplx::task<web::json::value> many(std::string collection, web::json::value filter = web::json::value::parse("{}"), web::json::value optionsParams = web::json::value::parse("{}")) {
                return pplx::task<web::json::value>([=] {
                    web::json::value placeholder;
                    placeholder = web::json::value::parse("[]");
                    return placeholder;
                });
            }

        }

        namespace update {

            pplx::task<bool> one(std::string collection, web::json::value filter, web::json::value data, web::json::value optionsParams = web::json::value::parse("{}")) {
                return pplx::task<bool>([=] {
                    return false;
                });
            }

            pplx::task<bool> many(std::string collection, web::json::value filter, web::json::value data, web::json::value optionsParams = web::json::value::parse("{}")) {
                return pplx::task<bool>([=] {
                    return false;
                });
            }

        }

        namespace remove {

            pplx::task<bool> one(std::string collection, web::json::value filter) {
                return pplx::task<bool>([=] {
                    return false;
                });
            }

            pplx::task<bool> many(std::string collection, web::json::value filter) {
                return pplx::task<bool>([=] {
                    return false;
                });
            }

        }

        

    }   }
#endif