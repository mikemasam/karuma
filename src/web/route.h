#include <iostream>
#include <vector>
#include <memory>
#include "controller.h"

#pragma once
namespace Web {
  using Controller = Web::Controller;
  using string = std::string;
  //route to hold controller and 
  class Route {
    public:
      Route(std::shared_ptr<Controller> _controller, std::string _name) : controller(_controller), name(_name){}
      Route addPath(std::string name, std::string path, bool anonymous);
      std::shared_ptr<Controller> controller;
      bool match(std::shared_ptr<Url> url);

    private:
      struct RoutePath {
        std::string name;
        std::string path;
        bool anonymous;
      };
      struct RouteValue {
        std::string name;
        std::string value;
      };
      bool _match(std::shared_ptr<Url> url, RoutePath route_path);
      std::string name;
      std::vector<RoutePath> paths;
      std::vector<RouteValue> _route_values;
  };
}
