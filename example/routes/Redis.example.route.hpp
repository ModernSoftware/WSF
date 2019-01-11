#include "Shared.hpp"
#include "utility/Router.utility.hpp"

#include "../services/Server.service.hpp"
#include "../services/Redis.example.service.hpp"

#ifndef _REDIS_ROUTE_SAMPLE_H
#define _REDIS_ROUTE_SAMPLE_H 1

namespace wsf { namespace route { namespace redis {

    wsf::utility::Response set(wsf::utility::Router& app) {
        wsf::utility::Response res;

        res._json = wsf::service::metadata(res._json);
        res._json = wsf::service::redis::set(res._json);

        return res;
    }

    wsf::utility::Response get(wsf::utility::Router& app) {
        wsf::utility::Response res;

        res._json = wsf::service::metadata(res._json);
        res._json = wsf::service::redis::get(res._json);

        return res;
    }

    wsf::utility::Response del(wsf::utility::Router& app) {
        wsf::utility::Response res;

        res._json = wsf::service::metadata(res._json);
        res._json = wsf::service::redis::del(res._json);

        return res;
    }

    wsf::utility::Response push(wsf::utility::Router& app) {
        wsf::utility::Response res;

        res._json = wsf::service::metadata(res._json);
        res._json = wsf::service::redis::push(res._json);

        return res;
    }

    wsf::utility::Response list(wsf::utility::Router& app) {
        wsf::utility::Response res;

        res._json = wsf::service::metadata(res._json);
        res._json = wsf::service::redis::list(res._json);

        return res;
    }

}   }   }

#endif
