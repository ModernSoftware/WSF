#include "Shared.hpp"
#include "utility/Router.utility.hpp"
#include "utility/Response.utility.hpp"

#include "../services/Server.service.hpp"
#include "../services/Mongo.example.service.hpp"

#ifndef _MONGO_ROUTE_SAMPLE_H
#define _MONGO_ROUTE_SAMPLE_H 1

namespace wsf { namespace route { namespace mongo {

    namespace insert {

        wsf::utility::Response one(wsf::utility::Router& app) {
            wsf::utility::Response res;

            res._json = wsf::service::metadata(res._json);
            res._json = wsf::service::mongo::insert::one(res._json);

            return res;
        }

        wsf::utility::Response many(wsf::utility::Router& app) {
            wsf::utility::Response res;

            res._json = wsf::service::metadata(res._json);
            res._json = wsf::service::mongo::insert::many(res._json);

            return res;
        }

    }

    namespace update {

        wsf::utility::Response one(wsf::utility::Router& app) {
            wsf::utility::Response res;

            res._json = wsf::service::metadata(res._json);
            res._json = wsf::service::mongo::update::one(res._json);

            return res;
        }

        wsf::utility::Response many(wsf::utility::Router& app) {
            wsf::utility::Response res;

            res._json = wsf::service::metadata(res._json);
            res._json = wsf::service::mongo::update::many(res._json);

            return res;
        }

    }

    namespace find {

        wsf::utility::Response one(wsf::utility::Router& app) {
            wsf::utility::Response res;

            res._json = wsf::service::metadata(res._json);
            res._json = wsf::service::mongo::find::one(res._json);

            return res;
        }

        wsf::utility::Response many(wsf::utility::Router& app) {
            wsf::utility::Response res;

            res._json = wsf::service::metadata(res._json);
            res._json = wsf::service::mongo::find::many(res._json);

            return res;
        }

    }

    namespace remove {

        wsf::utility::Response one(wsf::utility::Router& app) {
            wsf::utility::Response res;

            res._json = wsf::service::metadata(res._json);
            res._json = wsf::service::mongo::remove::one(res._json);

            return res;
        }

        wsf::utility::Response many(wsf::utility::Router& app) {
            wsf::utility::Response res;

            res._json = wsf::service::metadata(res._json);
            res._json = wsf::service::mongo::remove::many(res._json);

            return res;
        }

    }

}   }   }

#endif
