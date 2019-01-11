#include "utility/CLI.utility.hpp"
#include "utility/Router.utility.hpp"
#include "routes/Server.route.hpp"
#include "routes/Mongo.example.route.hpp"
#include "routes/Redis.example.route.hpp"

int main(int argc, char** argv) {
    if (wsf::cli::parse(argc, argv) == false) {
        std::cout << "There seems to be something wrong with your command line flags..." << "\n";
        return 2;
    }

    wsf::utility::Router app;

    return app.init()
        // Mongo Example Routes
        .route("GET", "/mongo/insert/one", wsf::route::mongo::insert::one)
        .route("GET", "/mongo/insert/many", wsf::route::mongo::insert::many)
        .route("GET", "/mongo/update/one", wsf::route::mongo::update::one)
        .route("GET", "/mongo/update/many", wsf::route::mongo::update::many)
        .route("GET", "/mongo/find/one", wsf::route::mongo::find::one)
        .route("GET", "/mongo/find/many", wsf::route::mongo::find::many)
        .route("GET", "/mongo/remove/one", wsf::route::mongo::remove::one)
        .route("GET", "/mongo/remove/many", wsf::route::mongo::remove::many)
        // Redis Example Routes
        .route("GET", "/redis/set", wsf::route::redis::set)
        .route("GET", "/redis/get", wsf::route::redis::get)
        .route("GET", "/redis/del", wsf::route::redis::del)
        .route("GET", "/redis/push", wsf::route::redis::push)
        .route("GET", "/redis/list", wsf::route::redis::list)
        // Default routes
        .get("/", wsf::route::info)
        .notFound()
        .start();
}
