#include "Shared.hpp"

#ifndef _SERVERDATA_H
#define _SERVERDATA_H 1

namespace wsf { namespace service {

    web::json::value metadata(web::json::value info) {
        info["version"] = web::json::value::string("0.0.1");
        info["server"] = web::json::value::string("WSF");
        return info;
    }

}   }

#endif
