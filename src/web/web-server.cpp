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
  void WebServer::addRoute(std::shared_ptr<Controller> cn,std::string route, bool anonymous){
    this->routes.push_back(Route(cn,route,anonymous));
  }
  void WebServer::addRoute(std::shared_ptr<Controller> cn,std::string route){
    this->routes.push_back(Route(cn,route,false));
  }

  const std::vector<Route> WebServer::getRoutes(){
    return this->routes;
  }

  void WebServer::processRequest(string url){
    //this->url = std::make_shared<Url>(url);
    //this->makeRoute();
  }

}
