#include <iostream>
#include <vector>
#include <memory>
#include "controller.h"
#include "route_path.h"
#include "route_value.h"
#include "route_found.h"
#pragma once
namespace Web {
  using Controller = Web::Controller;
  using string = std::string;
  class Route {
    public:
      Route(std::shared_ptr<Controller> _controller, std::string _name) : controller(_controller), name(_name){}
      void addPath(std::string name, std::string path, bool anonymous);
      RouteFound* match(std::shared_ptr<Url> url);
      std::string getName();
    private:
      bool _match(std::shared_ptr<Url> url, RoutePath route_path);
      std::shared_ptr<Controller> controller;
      std::string name;
      std::vector<RoutePath> paths;
      std::vector<RouteValue> _route_values;
  };
}
