#include "server.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#pragma once
namespace Networking {
  // This is the C++11 equivalent of a generic lambda.
  // The function object is used to send an HTTP message.
  template<class Stream> struct Send {
    Stream& stream_;
    bool& close_;
    beast::error_code& ec_;

    Send(Stream& stream, bool& close, beast::error_code& ec) : stream_(stream), close_(close), ec_(ec){
    }

    template<bool isRequest, class Body, class Fields> 
      void operator()(http::message<isRequest, Body, Fields>&& msg) const {
        // Determine if we should close the connection after
        close_ = msg.need_eof();

        // We need the serializer here because the serializer requires
        // a non-const file_body, and the message oriented version of
        // http::write only works with const messages.
        http::serializer<isRequest, Body, Fields> sr{msg};
        http::write(stream_, sr, ec_);
      }
  };

}
