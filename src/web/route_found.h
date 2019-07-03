#include "route_path.h"
#include "route_value.h"
#include "controller.h"
#pragma once
namespace Web {
  struct RouteFound {
    RoutePath path;
    std::vector<RouteValue> values;
    std::shared_ptr<Controller> controller;
  };
}
