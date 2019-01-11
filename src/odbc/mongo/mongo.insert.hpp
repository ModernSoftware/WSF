#ifndef _MONGO_API_INSERT_H
#define _MONGO_API_INSERT_H 1

    namespace wsf { namespace mongo { namespace insert {

        /*
        * @function one
        * Insert one documents from a collection
        *
        * @argument|string collection
        * The name of the collection
        *
        * @argument|web::json::value data
        * The data to insert into the collection
        *
        * @returns pplx::task<bool>
        * Returns whether or not the insertion was successful
        */
        pplx::task<bool> one(std::string collection, web::json::value data) {
            return pplx::task<bool>([=] {
                if (!MONGOCXX) return false;

                try {
                    auto poolInstance = wsf::mongo::pool.acquire();
                    auto client = (*poolInstance)[db][collection];

                    auto dataString = data.serialize().c_str();
                    auto document = bsoncxx::from_json(dataString);

                    auto done = client.insert_one(document.view());

                    return done ? true : false;
                } catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                    return false;
                }
            });
        }

        /*
        * @function many
        * Insert multiple documents from a collection
        *
        * @argument|string collection
        * The name of the collection
        *
        * @argument|web::json::value data
        * The data to insert into the collection
        *
        * @returns pplx::task<bool>
        * Returns whether or not the insertion was successful
        */
        pplx::task<bool> many(std::string collection, web::json::value data) {
            return pplx::task<bool>([=] {
                if (!MONGOCXX) return false;

                try {
                    if (!data.is_array()) return false;

                    auto bulkData = data.as_array();

                    auto poolInstance = wsf::mongo::pool.acquire();
                    auto client = (*poolInstance)[db][collection];

                    std::vector<bsoncxx::document::value> documents;

                    for (int i = 0; i < bulkData.size(); i++) {
                        std::string documentString = bulkData[i].serialize().c_str();
                        auto document = bsoncxx::from_json(documentString);
                        documents.push_back(bsoncxx::document::value(document.view()));
                    }

                    auto done = client.insert_many(documents);

                    return done ? true : false;
                } catch (std::exception &e) {
                    std::cout << e.what() << std::endl;
                    return false;
                }
            });
        }

    }   }   }

#endif
