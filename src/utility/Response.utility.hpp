#include "../Shared.hpp"
#include "../Config.hpp"

#ifndef _RESPONSE_UTILITY_H_
#define _RESPONSE_UTILITY_H_ 1

namespace wsf { namespace utility {

    /*
    * @class Response
    * The response class is used to send responses back to the client
    */
    class Response {

        public:
            /*
            * @property|int code
            * The status code, the default is 200 OK
            */
            int code = 200;

            /*
            * @property|web::json::value _json
            * The current json value of the response
            */
            web::json::value _json;

            /*
            * @function updateCode
            * Update the current status code of the response
            *
            * @argument|int _code
            * The code you want to update it to
            *
            * @returns bool
            * Whether or not it successfully updated the code
            */
            bool updateCode(int _code) {
                this->code = _code;
                return true;
            }

            /*
            * @function updateResponse
            * Update the json response
            *
            * @argument|web::json::value __json
            * The json value you want to update it to
            *
            * @returns bool
            * * Whether or not it successfully updated the response
            */
            bool updateResponse(web::json::value __json) {
                this->_json = __json;
                return true;
            }

            /*
            * @function result
            * returns the result for the response
            *
            * @returns string
            * The stringified response
            */
            std::string result() {
                return this->_json.serialize().c_str();
            }

    };

} }

#endif
