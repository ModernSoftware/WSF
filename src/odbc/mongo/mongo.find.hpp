#ifndef _MONGO_API_FIND_H
#define _MONGO_API_FIND_H 1

    namespace wsf { namespace mongo { namespace find {

        /*
        * @function options
        * Create the options for querying Mongo
        *
        *
        * @argument|web::json::value params
        * The parameters for querying
        *
        * @returns mongocxx::options::find
        * Returns the options for a find query
        */
        mongocxx::options::find options(web::json::value params) {
            mongocxx::options::find opt{};

            if (params["sort"].is_object()) {
                auto optionsSort = bsoncxx::from_json(params["sort"].serialize().c_str());
                opt.sort(optionsSort.view());
            }

            if (params["skip"].is_integer()) {
                opt.skip(params["skip"].as_integer());
            }

            if (params["limit"].is_integer()) {
                opt.limit(params["limit"].as_integer());
            }

            return opt;
        }

        /*
        * @function one
        * Find one document from a collection
        *
        * @argument|string collection
        * The name of the collection
        *
        * @argument|web::json::value filter
        * The filter you are querying, the default is {} which is anything
        *
        * @argument|web::json::value optionsParams
        * The option parameters, the default is {} which is the default
        *
        * @returns pplx::task<web::json::value>
        * Returns the json values of documents
        */
        pplx::task<web::json::value> one(std::string collection, web::json::value filter = web::json::value::parse("{}"), web::json::value optionsParams = web::json::value::parse("{}")) {
            return pplx::task<web::json::value>([=] {
                web::json::value result;

                if (!MONGOCXX) return result;

                try {
                    auto opt = options(optionsParams);

                    auto poolInstance = wsf::mongo::pool.acquire();
                    auto client = (*poolInstance)[db][collection];

                    auto filterString = filter.serialize().c_str();
                    auto filterDocument = bsoncxx::from_json(filterString);

                    auto resultDocument = client.find_one(filterDocument.view(), opt);

                    if (resultDocument) {
                        auto resultView = resultDocument->view();

                        auto resultString = bsoncxx::to_json(resultView);
                        auto result = web::json::value::parse(resultString);

                        return result;
                    } else {
                        result = web::json::value::parse("{}");
                        return result;
                    }
                } catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                    result["e"] = web::json::value(e.what());

                    return result;
                }
            });
        }

        /*
        * @function many
        * Find multiple documents from a collection
        *
        * @argument|string collection
        * The name of the collection
        *
        * @argument|web::json::value filter
        * The filter you are querying, the default is {} which is anything
        *
        * @argument|web::json::value optionsParams
        * The option parameters, the default is {} which is the default
        *
        * @returns pplx::task<web::json::value>
        * Returns the json values of documents
        */
        pplx::task<web::json::value> many(std::string collection, web::json::value filter = web::json::value::parse("{}"), web::json::value optionsParams = web::json::value::parse("{}")) {
            return pplx::task<web::json::value>([=] {
                web::json::value documents;

                if (!MONGOCXX) return web::json::value::parse("[]");

                try {
                    auto opt = options(optionsParams);

                    auto poolInstance = wsf::mongo::pool.acquire();
                    auto client = (*poolInstance)[db][collection];

                    auto filterString = filter.serialize().c_str();
                    auto filterDocument = bsoncxx::from_json(filterString);

                    auto resultCursor = client.find(filterDocument.view(), opt);

                    int i = 0;
                    for (auto&& document : resultCursor) {
                        std::string documentString = bsoncxx::to_json(document);
                        documents[i] = web::json::value::parse(documentString);
                        i++;
                    }

                    if (i == 0) documents = web::json::value::parse("[]");

                    return documents;
                } catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                    documents = web::json::value::parse("[]");
                    return documents;
                }
            });
        }

    }   }   }

#endif
