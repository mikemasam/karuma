#include <iostream>
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

  namespace beast = boost::beast;         // from <boost/beast.hpp>
  namespace http = beast::http;           // from <boost/beast/http.hpp>
  namespace net = boost::asio;            // from <boost/asio.hpp>
  using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

  class Client {
    public:
      Client();
      static void init(tcp::socket& socket, Client *s);
      bool isDone();
    private:
      bool done = false;
      void new_connection(tcp::socket& socket);
      //http::request<Body, http::basic_fields<Allocator>>&&

      template<class Body, class Allocator, class Send>
        void handle_request(http::request<Body, http::basic_fields<Allocator>>&&  req, Send&& send);
      void fail(beast::error_code ec, char const* what);
      http::response<http::string_body> getResponse(auto version, auto keep_alive);
  };
}
