#include "../Shared.hpp"

#ifndef _WEBSOCKET_H
#define _WEBSOCKET_H 1

namespace wsf { namespace sdk { namespace websocket {

    /*
    * @function listen
    * Create a websocket listener to listen to websockets in real time
    *
    * @argument|string socketUri
    * The socket url to listen to in ws:// or wss:// format
    *
    * @returns pplx::task<web::websockets::client::websocket_callback_client>
    * Returns a async task of the callback client
    */
    pplx::task<web::websockets::client::websocket_callback_client> listen(std::string socketUri) {
        return pplx::task<web::websockets::client::websocket_callback_client>([=] {
            web::websockets::client::websocket_callback_client newSocket;

            try {
                newSocket.connect(socketUri).wait();
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }

            return newSocket;
        });
    }

}   }   }

#endif
