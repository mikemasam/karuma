#include <iostream>
#include <memory>
#include <thread>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>
#include "client.h"

#pragma once
namespace Networking {
  namespace net = boost::asio;            // from <boost/asio.hpp>
  using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
  class Server {
    public:
      Server();
      static void serve(std::shared_ptr<Server> server);
      void init();
      std::string address;
      std::string port;
    private:
      std::vector<Client*> connections;
  };
}
