#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>
#include "web.h"

namespace Core {
  using string = std::string;
  using Router = Networking::Router;
  using Url = Networking::Url;

  void Web::addRoute(std::shared_ptr<Controller> cn,std::string route, bool anonymous){
    this->routes.push_back(Route(cn,route,anonymous));
  }
  void Web::addRoute(std::shared_ptr<Controller> cn,std::string route){
    this->routes.push_back(Route(cn,route,false));
  }

  const std::vector<Route> Web::getRoutes(){
    return this->routes;
  }

  const std::shared_ptr<Url> Web::getUrl(){
    return this->url;
  }


  void Web::setCurrentUrl(string url){
    this->url = std::make_shared<Url>(url);
    this->makeRoute();
  }

  void Web::makeRoute(){
    bool found = false;
    Router router(this->url);
    for(unsigned int j = 0;j < this->routes.size();j++){
      if(router.match(this->routes[j].path)){
        Route *r = &this->routes[j];
        r->controller->init(this);
        std::cout << r->controller->index() << std::endl;
        found = true;
      }else{
        //std::cout << "Route not found = " << this->url->getPath() << std::endl;
      }
    }
    if(!found)
      std::cout << "Route not found at all" << std::endl << "-----------------------" << std::endl;
  }
}
