#include <iostream>
#pragma once
namespace Core {
  class App {
    public:
      static std::string read_env(std::string name, std::string _default);
      static void app_init();
  };
}
