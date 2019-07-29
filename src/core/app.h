#include <iostream>
#pragma once

/*
 * Main application context class inside Web namespace
 */
namespace Core {
  class App {
    public:
      /* read_env - read enviroment variable 
       * Params
       * name - variable name
       * _default - default value if no value found
       * Return
       * string - value found
       */
      static std::string read_env(std::string name, std::string _default);
      /*
       * app_init - initialize application context and register error handlers
       */
      static void app_init();
  };
}
