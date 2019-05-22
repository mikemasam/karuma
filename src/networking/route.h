#include <iostream>
#include <vector>
#include <memory>
#include "../core/controller.h"

#pragma once
namespace Networking {
  using Controller = Core::Controller;
  using string = std::string;
  struct Route {
    Route(std::shared_ptr<Controller> _controller, std::string _path,bool _anonymous) : controller(_controller), path(_path), anonymous(_anonymous){}
    std::shared_ptr<Controller> controller;
    std::string path;
    bool isAnonymous(){ return this->anonymous; }
    private:
    bool anonymous = false;
  };
}
