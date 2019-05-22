#pragma once
#ifndef web_h 
#define web_h 

#include <iostream>
#include <vector>
#include <memory>
#include "controller.h"
#include "../networking/router.h"
#include "../networking/route.h"
#include "../networking/url.h"

namespace Core {
  using string = std::string;
  using Route = Networking::Route;
  using Url = Networking::Url;
  class Web{
    public:
      const Route getCurrentRoute();
      void setCurrentUrl(std::string url);
      void addRoute(std::shared_ptr<Controller> cn,std::string route, bool anonymous);
      void addRoute(std::shared_ptr<Controller> cn,std::string route);
      const std::vector<Route> getRoutes();
      const std::shared_ptr<Url> getUrl();
    private:
      std::vector<Route> routes;
      std::string server_name;
      void makeRoute();
      std::shared_ptr<Url> url;
  };
}

#endif
