#include "../Shared.hpp"

#ifndef _REQUEST_H
#define _REQUEST_H 1

namespace wsf { namespace utility {

        /*
        * @function requestConfig
        * Retrieves the configuration objet for http requests
        *
        * @argument|web::json::value configParams
        * The config parameters when making http requests
        *
        * @returns web::http::client::http_client_config
        */
        web::http::client::http_client_config requestConfig(web::json::value configParams) {
            web::http::client::http_client_config config;

            if (configParams["credentials"].is_object()) {
                web::http::client::credentials credentials;
                std::string username = configParams["credentials"]["username"].as_string();
                std::string password = configParams["credentials"]["password"].as_string();

                credentials = web::http::client::credentials(username, password);
                config.set_credentials(credentials);
            }

            if (configParams["timeout"].is_integer()) {
                std::chrono::seconds timeout(configParams["timeout"].as_integer());
                config.set_timeout(timeout);
            }

            return config;
        }

        /*
        * @function request
        * Create a http request as a pplx::task
        *
        * @argument|web::http::method method
        * The type of method, ie: GET, POST, PATCH, DELETE
        *
        * @argument|string url
        * The url to query
        *
        * @argument|web::json::value body
        * The body of the request (if POST, PATCH)
        *
        * @argument|web::json::value configParams
        * The parameters to pass when create a request
        *
        * @returns pplx::task<web::http::http_response>
        */
        pplx::task<web::http::http_response> request(web::http::method method, std::string url, web::json::value body, web::json::value configParams) {
            return pplx::task<web::http::http_response>([=] {
                try {
                    web::http::client::http_client_config config = requestConfig(configParams);
                    web::http::client::http_client client(url, config);

                    web::http::http_response response = client.request(method).get();
                    return response;
                } catch (std::exception& e) {
                    std::cout << e.what() << std::endl;

                    web::http::http_response response;
                    response.set_status_code(500);
                    response.set_reason_phrase("Something went wrong creating the request");

                    return response;
                }
            });
        }

        /*
        * @function request
        * Create a http request as a pplx::task
        *
        * @argument|web::http::method method
        * The type of method, ie: GET, POST, PATCH, DELETE
        *
        * @argument|string url
        * The url to query
        *
        * @argument|web::json::value body
        * The body of the request (if POST, PATCH)
        *
        * @returns pplx::task<web::http::http_response>
        */
        pplx::task<web::http::http_response> request(web::http::method method, std::string url, web::json::value body) {
            return pplx::task<web::http::http_response>([=] {
                try {
                    web::http::client::http_client client(url);
                    web::http::http_response response = client.request(method).get();
                    return response;
                } catch (std::exception& e) {
                    std::cout << e.what() << std::endl;

                    web::http::http_response response;
                    response.set_status_code(500);
                    response.set_reason_phrase("Something went wrong creating the request");

                    return response;
                }
            });
        }

        /*
        * @function request
        * Create a http request as a pplx::task
        *
        * @argument|web::http::method method
        * The type of method, ie: GET, POST, PATCH, DELETE
        *
        * @argument|string url
        * The url to query
        *
        * @returns pplx::task<web::http::http_response>
        */
        pplx::task<web::http::http_response> request(web::http::method method, std::string url) {
            return pplx::task<web::http::http_response>([=] {
                try {
                    web::http::client::http_client client(url);
                    web::http::http_response response = client.request(method).get();
                    return response;
                } catch (std::exception& e) {
                    std::cout << e.what() << std::endl;

                    web::http::http_response response;
                    response.set_status_code(500);
                    response.set_reason_phrase("Something went wrong creating the request");

                    return response;
                }
            });
        }

}   }

#endif
