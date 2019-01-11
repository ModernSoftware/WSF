#include <string>

#ifndef _CONFIG_H
#define _CONFIG_H 1

namespace wsf { namespace config {

    /*
    * @string host
    * The host URL for the web api
    * The default is http://0.0.0.0 which exposes the server to the local area network
    */
    std::string host = "http://0.0.0.0";

    /*
    * @string port
    * The port to listen on for the web api
    * The default is 3000 where you can ping the localhost:3000 url to interact with the api
    */
    std::string port = "3000";

    /*
    * @string cors
    * The CORS url to allow web applications to interact with the web api
    * The default is * which means any web application can interact with the api
    */
    std::string cors = "*";

    /*
    * @string mongo
    * The MongoDB url to listen on to interact with a Mongo Database
    * The default is on localhost
    */
    std::string mongo = "mongodb://localhost:27017";

    /*
    * @string mongodb
    * The Mongo Database to interact with from the Mongo url
    * The default is wsf
    */
    std::string mongodb = "wsf";

    /*
    * @string redis
    * The Redis host to interact with hiredisx
    * The default is localhost
    */
    std::string redis = "localhost";

    /*
    * @int redisPort
    * The Redis port to interact with hiredisx
    * The default port is 6379
    */
    int redisPort = 6379;

    /*
    * @int redisTimeout
    * The Redis timeout to wait for queries
    * The default is 3 seconds
    */
    int redisTimeout = 3;

}   }

#endif
