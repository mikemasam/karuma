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
#include "../networking/url.h"
#include "controller_response.h"

#pragma once
/*
 * Client class in Web namespace
 */
namespace Web {

  class WebServer;
  class Route;
  using Url = Networking::Url;

  namespace beast = boost::beast;         // from <boost/beast.hpp>
  namespace http = beast::http;           // from <boost/beast/http.hpp>
  namespace net = boost::asio;            // from <boost/asio.hpp>
  using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

  class Client {
    public:
      /*
       * Cleint - constructor
       * Params
       * web_server - WebServer object pointer
       */
      Client(WebServer *web_server);
      ~Client();
      /*
       * init - initiate client with the socket that handles 
       */
      static void init(tcp::socket& socket, Client *s);
      bool isDone();
      void Done();
      std::string getClientId();

      const Route getCurrentRoute();
      //TODO: make web and url constant not to be editable
      std::shared_ptr<Url> getUrl();
      WebServer * getWeb();

    private:
      std::string client_id;
      bool done = false;
      void new_connection(tcp::socket& socket);
      WebServer *web_server;

      ControllerResponse* findRoute();
      std::shared_ptr<Url> url;


      template<class Body, class Allocator, class Send>
        void handle_request(http::request<Body, http::basic_fields<Allocator>>&&  req, Send&& send);

      void fail(beast::error_code ec, char const* what);

      http::response<http::string_body> getResponse(ControllerResponse* res, int version);
  };
}
