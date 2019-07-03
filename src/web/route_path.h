#include <iostream>
#pragma once
namespace Web {
  struct RoutePath {
    std::string name;
    std::string path;
    bool anonymous;
  };
}
