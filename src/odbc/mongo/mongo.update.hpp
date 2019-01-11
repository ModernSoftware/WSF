#ifndef _MONGO_API_UPDATE_H
#define _MONGO_API_UPDATE_H 1

    namespace wsf { namespace mongo { namespace update {

        /*
        * @function options
        * Configures the option parameters for the update query
        *
        * @argument|web::json::value params
        * The options to use for the update query
        *
        * @returns mongocxx::options::update
        * Returns the update configuration parameters
        */
        mongocxx::options::update options(web::json::value params) {
            mongocxx::options::update opt{};

            if (params["upsert"].is_boolean()) {
                opt.upsert(params["upsert"].as_bool());
            }

            return opt;
        }

        /*
        * @function one
        * Updates one document from a collection
        *
        * @argument|string collection
        * The name of the collection
        *
        * @argument|web::json::value filter
        * The data to filter to select to update
        *
        * @argument|web::json::value data
        * The data to update for the collection
        *
        * @argument|web::json::value optionsParams
        * The parameters to pass into the web api
        *
        * @returns pplx::task<bool>
        * Returns whether or not the update query was successful
        */
        pplx::task<bool> one(std::string collection, web::json::value filter, web::json::value data, web::json::value optionsParams = web::json::value::parse("{}")) {
            return pplx::task<bool>([=] {
                if (!MONGOCXX) return false;

                try {
                    auto opt = options(optionsParams);

                    auto poolInstance = wsf::mongo::pool.acquire();
                    auto client = (*poolInstance)[db][collection];

                    web::json::value newData;
                    newData["$set"] = data;

                    auto dataDocument = bsoncxx::from_json(newData.serialize().c_str());
                    auto filterDocument = bsoncxx::from_json(filter.serialize().c_str());

                    auto done = client.update_one(filterDocument.view(), dataDocument.view(), opt);

                    return done ? true : false;
                } catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                    return false;
                }
            });
        }

        /*
        * @function many
        * Updates multiple documents from a collection
        *
        * @argument|string collection
        * The name of the collection
        *
        * @argument|web::json::value filter
        * The data to filter to select to update
        *
        * @argument|web::json::value data
        * The data to update for the collection
        *
        * @argument|web::json::value optionsParams
        * The parameters to pass into the web api
        *
        * @returns pplx::task<bool>
        * Returns whether or not the update query was successful
        */
        pplx::task<bool> many(std::string collection, web::json::value filter, web::json::value data, web::json::value optionsParams = web::json::value::parse("{}")) {
            return pplx::task<bool>([=] {
                if (!MONGOCXX) return false;

                try {
                    auto opt = options(optionsParams);

                    auto poolInstance = wsf::mongo::pool.acquire();
                    auto client = (*poolInstance)[db][collection];

                    web::json::value newData;
                    newData["$set"] = data;

                    auto dataDocument = bsoncxx::from_json(newData.serialize().c_str());
                    auto filterDocument = bsoncxx::from_json(filter.serialize().c_str());

                    auto done = client.update_many(filterDocument.view(), dataDocument.view(), opt);

                    return done ? true : false;
                } catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                    return false;
                }
            });
        }

    }   }   }

#endif
