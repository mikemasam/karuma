#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "../networking/url.h"

namespace Web {
  using Url = Networking::Url;
  struct RouteValue {
    std::string name;
    std::string value;
  };

  class Router {
    public:
      Router(std::shared_ptr<Url> &url);
    private:
      std::string path;
      std::vector<RouteValue> _route_values;
  };
}

