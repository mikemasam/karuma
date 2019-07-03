#include <iostream>
#pragma once
namespace Web {
  class ControllerResponse {
    public:
      std::string data;
      std::string type;
      int status = 200;
  };
}
