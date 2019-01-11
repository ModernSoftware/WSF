#include "../Shared.hpp"
#include "../Config.hpp"

#include "Response.utility.hpp"

#ifndef _ROUTER_UTILITY_H_
#define _ROUTER_UTILITY_H_ 1

    namespace wsf { namespace utility {

        /*
        * @class Router
        * The router class is used to manage routes to their respective functions
        */
        class Router {
            protected:
                /*
                * @property|string host
                * The host of the client querying the api
                */
                std::string host;

                /*
                * @property|web::http::experimental::listener::http_listener listener
                * The web api listener
                */
                web::http::experimental::listener::http_listener listener;

                /*
                * @function generateResponse
                * Generates a response to return to the client
                *
                * @argument|web::http::status_code code
                * The status code to send to the client
                *
                * @argument|string payload
                * The json response as a string
                *
                * @returns web::http::http_response
                */
                web::http::http_response generateResponse(web::http::status_code code, std::string payload) {
                    web::http::http_response response(code);

                    response.headers().add(U("Access-Control-Allow-Origin"), wsf::config::cors);
                    response.set_body(payload, "application/json");

                    return response;
                }

                /*
                * @function generateNotFound
                * Generates the generic 404 not found response
                *
                * @argument|wsf::utility::Router app
                * A pointer to the router app
                *
                * @returns wsf::utility::Response
                */
                wsf::utility::Response generateNotFound(wsf::utility::Router& app) {
                    wsf::utility::Response res;
                    res.updateCode(404);
                    res._json["message"] = web::json::value::string("Path not found...");
                    web::json::value info;

                    return res;
                }

            public:
                /*
                * @property|web::http::http_request request
                * The request from the client
                */
                web::http::http_request request;

                /*
                * @property|web::uri uri
                * The uri that the client queried
                */
                web::uri uri;

                /*
                * @property|string path
                * The string of the route queried by the client
                */
                std::string path;

                /*
                * @property|string method
                * The string of the type of method (ie: GET, POST, PATCH, DELETe etc.)
                */
                std::string method;

                /*
                * @property|web::json::value body
                * The json body that the client sent to the web api
                */
                web::json::value body;

                /*
                * @property|web::json::value query
                * The key values of the query string that the client sent to the web api
                */
                web::json::value query;

                /*
                * @function init
                * Initializes the router and returns a pointer of the router object.
                *
                * @returns Router
                */
                Router& init() {
                    this->host = wsf::config::host + ":" + wsf::config::port;
                    this->listener = web::http::experimental::listener::http_listener(this->host);

                    return *this;
                }

                /*
                * @function route
                * Create a route with it's respective response route.
                * This route is templated and must return a WSF response
                *
                * @argument|string routeMethod
                * The type of method to use for the route (ie: GET, POST, PATCH, DELETE)
                *
                * @argument|string routePath
                * The url of the method
                *
                * @argument|Fn response
                * The templated response. It should be a WSF response
                *
                * @returns Router
                * Just returns a pointer of the router, to allow chainable routes
                */
                template <typename Fn>
                Router& route(std::string routeMethod, std::string routePath, Fn response) {
                    this->listener.support(routeMethod, [=](web::http::http_request r) {
                        this->request = r;

                        this->uri = this->request.request_uri();
                        this->path = this->uri.path();
                        this->method = this->request.method();

                        try {
                            this->body = this->request.extract_json().get();
                        } catch (std::exception& e) {
                            std::cout << e.what() << std::endl;
                        }

                        try {
                            std::string qs = this->uri.query();
                            auto q = web::uri::split_query(qs);

                            for (auto item : q) {
                                this->query[item.first] = web::json::value(item.second);
                            }
                        } catch (std::exception& e) {
                            std::cout << e.what() << std::endl;
                        }

                        if (routeMethod == this->method && routePath == this->path) {
                            wsf::utility::Response res = response(*this);
                            std::cout << res.result() << "\n";
                            request.reply(this->generateResponse(res.code, res.result()));
                        }

                        std::cout << "[" + this->method + "] Request to " << this->path << "\n";
                    });

                    return *this;
                }

                /*
                * @function get
                * Create a GET route with it's respective response route.
                * This route is templated and must return a WSF response
                *
                * @argument|string routePath
                * The url of the method
                *
                * @argument|Fn response
                * The templated response. It should be a WSF response
                *
                * @returns Router
                * Just returns a pointer of the router, to allow chainable routes
                */
                template <typename Fn>
                Router& get(std::string routePath, Fn response) {
                    return this->route("GET", routePath, response);
                }

                /*
                * @function post
                * Create a POST route with it's respective response route.
                * This route is templated and must return a WSF response
                *
                * @argument|string routePath
                * The url of the method
                *
                * @argument|Fn response
                * The templated response. It should be a WSF response
                *
                * @returns Router
                * Just returns a pointer of the router, to allow chainable routes
                */
                template <typename Fn>
                Router& post(std::string routePath, Fn response) {
                    return this->route("POST", routePath, response);
                }

                /*
                * @function patch
                * Create a PATCH route with it's respective response route.
                * This route is templated and must return a WSF response
                *
                * @argument|string routePath
                * The url of the method
                *
                * @argument|Fn response
                * The templated response. It should be a WSF response
                *
                * @returns Router
                * Just returns a pointer of the router, to allow chainable routes
                */
                template <typename Fn>
                Router& patch(std::string routePath, Fn response) {
                    return this->route("PATCH", routePath, response);
                }

                /*
                * @function put
                * Create a PUT route with it's respective response route.
                * This route is templated and must return a WSF response
                *
                * @argument|string routePath
                * The url of the method
                *
                * @argument|Fn response
                * The templated response. It should be a WSF response
                *
                * @returns Router
                * Just returns a pointer of the router, to allow chainable routes
                */
                template <typename Fn>
                Router& put(std::string routePath, Fn response) {
                    return this->route("PUT", routePath, response);
                }

                /*
                * @function del
                * Create a DELETE route with it's respective response route.
                * This route is templated and must return a WSF response
                *
                * @argument|string routePath
                * The url of the method
                *
                * @argument|Fn response
                * The templated response. It should be a WSF response
                *
                * @returns Router
                * Just returns a pointer of the router, to allow chainable routes
                */
                template <typename Fn>
                Router& del(std::string routePath, Fn response) {
                    return this->route("DELETE", routePath, response);
                }

                /*
                * @function options
                * Create a OPTIONS route with it's respective response route.
                * This route is templated and must return a WSF response
                *
                * @argument|string routePath
                * The url of the method
                *
                * @argument|Fn response
                * The templated response. It should be a WSF response
                *
                * @returns Router
                * Just returns a pointer of the router, to allow chainable routes
                */
                template <typename Fn>
                Router& options(std::string routePath, Fn response) {
                    return this->route("OPTIONS", routePath, response);
                }

                /*
                * @function notFound
                * Create a catch all as a 404 for routes that are do not match.
                *
                * @returns Router
                */
                Router& notFound() {
                    wsf::utility::Response res = this->generateNotFound(*this);
                    request.reply(this->generateResponse(res.code, res.result()));

                    return *this;
                }

                /*
                * @function start
                * Start the web api
                *
                * @returns int
                */
                int start() {
                    try {
                        std::cout << "Server starting on host: " << host << "\n";
                        this->listener.open().wait();
                        while (true);
                    } catch (std::exception& e) {
                        std::cout << e.what() << std::endl;
                        return 2;
                    }
                    return 0;
                }
        };

    }   }

#endif
