#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "../utils.h"
#include "../networking/url.h"

namespace Networking {
using Url = Networking::Url;
  struct RouteValue {
    std::string name;
    std::string value;
  };

  class Router {
    public:
      bool match(std::string match);
      Router(std::shared_ptr<Url> &url);
    private:
      std::vector<std::string> parts;
      std::string path;
      std::vector<RouteValue> _route_values;
  };
}

