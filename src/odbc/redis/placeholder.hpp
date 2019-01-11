#include "../../Shared.hpp"
#include "../../Config.hpp"

#ifndef _REDIS_API_H
#define _REDIS_API_H 1
    namespace wsf { namespace redis {

        pplx::task<bool> init() {
            return pplx::task<bool>([=] {
                return false;
            });
        }

        pplx::task<bool> set(std::string key, std::string value) {
            return pplx::task<bool>([=] {
                return false;
            });
        }

        pplx::task<std::string> get(std::string key) {
            return pplx::task<std::string>([=] {
                return "";
            });
        }

        pplx::task<bool> del(std::string key) {
            return pplx::task<bool>([=] {
                return false;
            });
        }

        pplx::task<bool> push(std::string key, std::string value, std::string prefix = "L") {
            return pplx::task<bool>([=] {
                return false;
            });
        }

        pplx::task<std::vector <std::string>> list(std::string key, int start = 0, int end = -1, std::string prefix = "L") {
            return pplx::task<std::vector<std::string>>([=] {
                std::vector<std::string> emptyVec;
                return emptyVec;
            });
        }

    }   }
#endif