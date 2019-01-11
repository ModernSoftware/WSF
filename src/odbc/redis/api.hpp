#include "../../Shared.hpp"
#include "../../Config.hpp"

#ifndef _REDIS_API_H
#define _REDIS_API_H 1
    #include "hiredisx.hpp"

    namespace wsf { namespace redis {

        /*
        * @function init
        * Initialize the hiredisx client
        *
        * @returns pplx::task<bool>
        * Returns whether or not the connection was successful
        */
        pplx::task<bool> init() {
            return pplx::task<bool>([=] {

                hiredisx::options::host = wsf::config::redis;
                hiredisx::options::port = wsf::config::redisPort;
                hiredisx::options::timeoutS = wsf::config::redisTimeout;

                return hiredisx::test::connect();
            });
        }

        /*
        * @function set
        * Set a value in redis
        *
        * @argument|string key
        * The key to update
        *
        * @argument|string value
        * The value to assign to the key
        *
        * @returns pplx::task<bool>
        * Returns whether or not the value was set
        */
        pplx::task<bool> set(std::string key, std::string value) {
            return pplx::task<bool>([=] {
                return hiredisx::set(key, value);
            });
        }

        /*
        * @function set
        * Get a value in redis
        *
        * @argument|string key
        * The key to query
        *
        * @returns pplx::task<string>
        * Returns the value of the key
        */
        pplx::task<std::string> get(std::string key) {
            return pplx::task<std::string>([=] {
                return hiredisx::get(key);
            });
        }

        /*
        * @function del
        * Delete a value in redis
        *
        * @argument|string key
        * The key to delete
        *
        *
        * @returns pplx::task<bool>
        * Returns whether or not the value was deleted
        */
        pplx::task<bool> del(std::string key) {
            return pplx::task<bool>([=] {
                return hiredisx::del(key);
            });
        }

        /*
        * @function push
        * Set a value into a key value array in redis
        *
        * @argument|string key
        * The key to update
        *
        * @argument|string value
        * The value to assign to the key value array
        *
        * @returns pplx::task<bool>
        * Returns whether or not the value was set
        */
        pplx::task<bool> push(std::string key, std::string value, std::string prefix = "L") {
            return pplx::task<bool>([=] {
                return hiredisx::push(key, value, prefix);
            });
        }

        /*
        * @function list
        * Get a key value array from redis
        *
        * @argument|string key
        * The key to update
        *
        * @argument|int start
        * The start of the array, default is 0
        *
        * @argument|int end
        * The end of the array, default is -1, meaning the rest of the array
        *
        * @argument|string prefix
        * Whether to start from left to right or, right to left, default is "L" which is left to right
        *
        * @returns pplx::task<std::vector <std::string>>
        * Returns a vector of the string values
        */
        pplx::task<std::vector <std::string>> list(std::string key, int start = 0, int end = -1, std::string prefix = "L") {
            return pplx::task<std::vector<std::string>>([=] {
                return hiredisx::list(key, start, end, prefix);
            });
        }

    }   }
#endif
