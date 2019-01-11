#include "../Shared.hpp"
#include "../Config.hpp"

#ifndef _REDIS_H
#define _REDIS_H 1

    #ifdef REDIS
        #include "redis/api.hpp"
        if (wsf::redis::init().get()) {
            std::cout << "Redis Enabled on URI " << wsf::config::redis << "\n";
        } else {
            std::cout << "Redis Failed to initialize on URI " << wsf::config::redis << "\n";
        }
    #else
        #define REDIS 0
        #include "redis/placeholder.hpp"
    #endif

#endif
