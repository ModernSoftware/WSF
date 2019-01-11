#include "../Shared.hpp"
#include "../Config.hpp"

#ifndef _MONGO_H
#define _MONGO_H 1

    #ifdef MONGO
        #include "mongo/api.hpp"
        std::cout << "MongoDB Enabled on URI " << wsf::config::mongo << "\n";
        std::cout << "MongoDB is using Database " << wsf::config::mongodb << "\n";
    #else
        #define MONGO 0
        #include "mongo/placeholder.hpp"
    #endif

#endif
