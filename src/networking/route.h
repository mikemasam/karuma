#include <iostream>
#include <vector>
#include <memory>
#include "../core/controller.h"

#pragma once
namespace Networking {
  using Controller = Core::Controller;
  using string = std::string;
  struct Route {
    Route(std::shared_ptr<Controller> _cn, std::string _route,bool _anonymous) : cn(_cn), route(_route), anonymous(_anonymous){}
    std::shared_ptr<Controller> cn;
    std::string route;
    bool isAnonymous(){ return this->anonymous; }
    private:
    bool anonymous = false;
  };
}
