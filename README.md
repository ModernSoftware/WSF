
# The C++ Web Service Framework

![License](https://img.shields.io/badge/license-MIT-blue.svg)
[![Build Status](https://travis-ci.org/mov-eax/WSF.svg?branch=master)](https://travis-ci.org/mov-eax/WSF)
[![codecov](https://codecov.io/gh/mov-eax/WSF/branch/master/graph/badge.svg)](https://codecov.io/gh/mov-eax/WSF)
![C++ Standard](https://img.shields.io/badge/C++%20version-11-blue.svg)
![CMake](https://img.shields.io/badge/cmake%20version-3.7-blue.svg)

## Summary

A framework with the sole intention of making C++ Web API development extremely productive and easier to do. Save time by using an easy to use chainable routing interface. Work directly with MongoDB and Redis with custom built high-level drivers. Support is focused on Mac, Debian and Windows OSes and will shift primarily to Docker Containers in the future.

### The New Vision

At first, the original intent was to create a mono framework with all key features (ie: Redis, Mongo, RabbitMQ etc). However, after some consideration about the project. I decided it was best to dial it down to focusing solely on just the router itself with this project. And creating integrations and modules for other frameworks.

I believe the only core thing thing that needs a true integration is websocket++ to listen on the same port as a WSF server. Otherwise, there is no need for me to prescribe you to use cases like `hiredisx` or `congo`. However, I do still highly suggest `Congo` over anything currently on the market for free Mongo ODMs.

## How it works

### An intuitive and simple router

Setting up is straight forward, here's an example main function:

```c++
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
```

Routes feel a lot like Express and anything similar to it. Routes are chainable or can be colon separated. In the future this same functionality can be applied for middleware and prefixing routes.

In order to handle routes. You can use the Response object and interface to interact with data. All you need to do is update the `_json` response:

```c++
wsf::utility::Response info(wsf::utility::Router& app) {
    wsf::utility::Response res;

    res._json = wsf::service::metadata(res._json);
    res._json["query"] = app.query;

    return res;
}
```

Accessing data in responses is similar to any other framework:

```c++
web::json::value = app.query; // Request query string
web::json::value = app.body; // Request json payload
std::string = app.method; // Request method
std::string = app.path; // Request uri path
```

## Requirements for Compilation

You can just go the easy way with Docker. But if you need to do more in depth tinkering. You might want to compile directly.

With docker all you need to do is:

```
docker build -t wsf .
```

And you'll be able to SSH into the container and compile with cmake accordingly.

### Required for build

1. [C++ REST SDK](https://github.com/Microsoft/cpprestsdk)

2. [Boost Core](https://github.com/boostorg/boost/wiki/Getting-Started)

3. [OpenSSL](https://github.com/openssl/openssl)

4. [CMake and Make](https://cmake.org/) (>=3.7)

### Optional requirements

5. [MongoDB](https://github.com/mongodb/mongo)

- Before installing the C++ drivers, you need to install [the C drivers first](https://github.com/mongodb/mongo-c-driver/releases).

- Once the C drivers are installed you can install [the C++ drivers](http://mongocxx.org/mongocxx-v3/installation/).

6. [Redis](https://github.com/antirez/redis/)

- Use hiredisx to interact with Redis [hiredisx](https://github.com/ChrisCates/hiredisx).

- The hiredis C drivers are required for hiredisx [hiredis](https://github.com/redis/hiredis).

7. [Websocket++](https://github.com/zaphoyd/websocketpp)

- *Note: Websocket is only required to create WS(S) servers and is not required to create websocket clients.*

## Building with CMake

CMake will always be the best way to interface with WSF. Primary support will be for Mac OS, Debian and Windows Operating Systems.

### Standard Build

**1. Create the build directory**

You can build directly in the source file if you don't plan on committing to this repository.

```bash
mkdir build
cd build
```

**2. Run cmake and make:**

If you want to try the sample application, just make sure to turn `BINARY=ON` with cmake.

```bash
cmake .. -DEXAMPLE=ON
make
```

**3. Install libraries or run the server binary**

If you turned the example on, then you should have a server binary that can run with just:

```bash
./example
```

If you'd prefer to install the WSF library to your machine just run only this instead:

```
make install
```

**4. (Optional) Add flags for drivers**

Run CMake with the following optional flags:

```bash
cmake -DMONGO=ON # To enable mongodb
cmake -DREDIS=ON # To enable hiredisx
cmake -DWSS=ON # To enable websocket++
```

**5. *NOTE:* sometimes you might need to specify library paths, if you do need to, you can do like so:**

```bash
# Custom OpenSSL paths
cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl -DOPENSSL_LIBRARIES=/usr/local/opt/openssl/lib ..

# Custom HiRedis/HiRedisX path
cmake -DHIREDIS_INCLUDE_DIR=/usr/local/include/hiredis ..
cmake -DHIREDISX_INCLUDE_DIR=/usr/local/include/hiredisx ..

# Custom Websocket++ path
cmake -DWSSPP_INCLUDE_DIR=/usr/local/include/websocketpp ..
```

### Custom binary flags

The binary also comes with custom command line options:

```bash
$ server --help

The C++ Web Service Framework for modern web services:
--help print help message
-h [ --host ] arg specify host to listen on (default is http://0.0.0.0)
-p [ --port ] arg specify port to listen on (default is 3000)
-c [ --cors ] arg specify CORS (default is * which is sometimes unsafe)
--mongo arg MongoDB url (default is mongodb://localhost:27017)
--mongodb arg MongoDB DB name (default is wsf)
--redis arg Redis url (default is localhost)
--redisPort arg Redis port (default is 6379)
--redisTimeout arg Redis timeout (default is 3 in s)
```

### Testing

Set custom cmake flags to enable testing:

```bash
# Example flags that can be "ON" or "OFF"
cmake .. -DALL_TESTING=ON -DSTANDARD_TESTING=ON -DMONGO_TESTING=ON -DREDIS_TESTING=ON
```

Then just run:

```
make
make test
```

## Need help?

Feel free to open a PR or issue if you have any concerns in regards to the codebase.
