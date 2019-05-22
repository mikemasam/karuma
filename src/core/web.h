#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "../networking/routing.h"
#include "../networking/routes.h"
#include "../networking/route.h"
namespace Core {
  using string = std::string;
  using Route = Networking::Route;
  using Routes = Networking::Routes;
  using Url = Networking::Url;
  class Web{
    public:
      const Route getCurrentRoute();
      void addRoutes(Routes routes);
      void setCurrentUrl(std::string url);
      void addRoute(Web *web, std::shared_ptr<Controller> cn,std::string route, bool anonymous);
      void addRoute(Web *web, std::shared_ptr<Controller> cn,std::string route);
      const std::vector<Route> getRoutes();
    private:
      std::vector<Route> open_routes;
      std::vector<Route> auth_routes;
      std::string server_name;
      void makeRoute();
      std::shared_ptr<Url> url;
  };
}
