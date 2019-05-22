#pragma once
#include <iostream>

namespace Core {
  using string = std::string;
  class Controller {
    public:
      virtual std::string index();
    private:
      void _index();
  };
}
