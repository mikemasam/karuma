#include <iostream>
#include <vector>
#include <memory>
#include "route.h"
#include "routing.h"
#include "routes.h"


namespace Networking {
  using string = std::string;
  using Router = Networking::Router;

  Routes::Routes(){}
  Routes::~Routes(){}
  const std::vector<Route> Routes::getRoutes(){
    this->anonymousRoutes();
    this->authorizedRoutes();
    return this->anonymous_routes;
  }

  void Routes::anonymousRoutes(){
    std::cout << "Anony = " << std::endl;
  }
  void Routes::authorizedRoutes(){
    std::cout << "authorize = " << std::endl;
  }

  void Routes::addRoute(Web *web, std::shared_ptr<Controller> cn,std::string route, bool anonymous){
    Route r(cn,route,anonymous);
    Routes::anonymous_routes.push_back(r);
  }

}
