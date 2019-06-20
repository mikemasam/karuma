#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <sstream>
#include <algorithm>

namespace Web {
  using string = std::string;
  class Server;
  class Controller;
  class Route;

  class WebServer {
    public:
      WebServer();
      void processRequest(std::string url);
      void addRoute(Route route);
      const std::vector<Route> getRoutes();
      void serve(std::string address, std::string port);
      std::shared_ptr<Server> server;
    private:
      std::vector<Route> routes;
      std::string server_name;
  };
}
