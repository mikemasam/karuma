#include "web-server.h"
#include "server.h"
#include "route.h"

namespace Web {

  WebServer::WebServer(){
      this->server = std::make_shared<Server>();
  }

  void WebServer::serve(std::string address, std::string port){
    this->server->address = address;
    this->server->port = port;
    std::thread{std::bind(&Server::serve,this)}.detach();
  }

  void WebServer::addRoute(Route route){
    this->routes.push_back(route);
  }

  const std::vector<Route> WebServer::getRoutes(){
    return this->routes;
  }

}
