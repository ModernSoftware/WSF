#include "Shared.hpp"
#include "utility/Router.utility.hpp"

#include "../services/Server.service.hpp"

#ifndef _SERVERINFO_H
#define _SERVERINFO_H 1

namespace wsf { namespace route {

    wsf::utility::Response info(wsf::utility::Router& app) {
        wsf::utility::Response res;

        res._json = wsf::service::metadata(res._json);
        res._json["query"] = app.query;

        return res;
    }

}   }

#endif
