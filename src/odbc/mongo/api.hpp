#include "../../Shared.hpp"
#include "../../Config.hpp"

#ifndef _MONGO_API_H
#define _MONGO_API_H 1
    #include <bsoncxx/builder/stream/document.hpp>
    #include <bsoncxx/builder/basic/array.hpp>
    #include <bsoncxx/builder/basic/document.hpp>
    #include <bsoncxx/builder/basic/kvp.hpp>
    #include <bsoncxx/json.hpp>
    #include <bsoncxx/types.hpp>
    #include <bsoncxx/stdx/make_unique.hpp>
    #include <bsoncxx/stdx/optional.hpp>
    #include <bsoncxx/stdx/string_view.hpp>

    #include <mongocxx/client.hpp>
    #include <mongocxx/pool.hpp>
    #include <mongocxx/instance.hpp>
    #include <mongocxx/options/find.hpp>
    #include <mongocxx/uri.hpp>

    namespace wsf { namespace mongo {

        /*
        * @mongocxx::instance MongoInstance
        * An instance of the MongoDB driver
        */
        mongocxx::instance MongoInstance{};

        /*
        * @mongocxx::uri uri
        * The MongoDB URI, uses the configuration url
        */
        mongocxx::uri uri(wsf::config::mongo);

        /*
        * @mongocxx::pool
        * The MongoDB query pool uses the mongo uri
        */
        mongocxx::pool pool{uri};

        /*
        * @string db
        * The Mongo database to query
        */
        std::string db = wsf::config::mongodb;

    }   }

    #include "mongo.insert.hpp"
    #include "mongo.find.hpp"
    #include "mongo.update.hpp"
    #include "mongo.delete.hpp"

#endif
