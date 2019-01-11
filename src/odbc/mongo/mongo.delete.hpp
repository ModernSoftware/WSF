#ifndef _MONGO_API_DELETE_H
#define _MONGO_API_DELETE_H 1

    namespace wsf { namespace mongo { namespace remove {

        /*
        * @function one
        * Delete one document from a collection
        *
        * @argument|string collection
        * The name of the collection
        *
        * @argument|web::json::value filter
        * The filter you are querying
        *
        * @returns pplx::task<bool>
        * Returns whether or not the query was successful
        */
        pplx::task<bool> one(std::string collection, web::json::value filter) {
            return pplx::task<bool>([=] {
                if (!MONGOCXX) return false;

                try {
                    auto poolInstance = wsf::mongo::pool.acquire();
                    auto client = (*poolInstance)[db][collection];

                    auto filterString = filter.serialize().c_str();
                    auto filterDocument = bsoncxx::from_json(filterString);

                    auto done = client.delete_one(filterDocument.view());

                    return done ? true : false;
                } catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                    return false;
                }
            });
        }

        /*
        * @function one
        * Delete multiple documents from a collection
        *
        * @argument|string collection
        * The name of the collection
        *
        * @argument|web::json::value filter
        * The filter you are querying
        *
        * @returns pplx::task<bool>
        * Returns whether or not the query was successful
        */
        pplx::task<bool> many(std::string collection, web::json::value filter) {
            return pplx::task<bool>([=] {
                if (!MONGOCXX) return false;

                try {
                    auto poolInstance = wsf::mongo::pool.acquire();
                    auto client = (*poolInstance)[db][collection];

                    auto filterString = filter.serialize().c_str();
                    auto filterDocument = bsoncxx::from_json(filterString);

                    auto done = client.delete_many(filterDocument.view());

                    return done ? true : false;
                } catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                    return false;
                }
            });
        }

    }   }   }

#endif
