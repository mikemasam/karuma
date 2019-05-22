#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>
#include "../networking/route.h"
#include "../networking/url.h"
#include "web.h"

namespace Core {
  using string = std::string;
  using Router = Networking::Router;
  using Url = Networking::Url;

  void Web::addRoutes(Routes routes){
    this->routes = routes;
  }

  void Web::setCurrentUrl(string url){
    this->url = std::make_shared<Url>(url);
    this->makeRoute();
  }

  void Web::makeRoute(){
    bool found = false;
    Router router(this->url);
    std::vector<Route> routes = this->routes.getRoutes();
    for(unsigned int j = 0;j < routes.size();j++){
      if(router.match(routes[j].route)){
        std::cout << routes[j].cn->index() << std::endl;
        found = true;
      }else{
        //std::cout << "Route not found = " << this->url->getPath() << std::endl;
      }
    }

    if(!found)
      std::cout << "Route not found at all" << std::endl << "-----------------------" << std::endl;
  }
}
