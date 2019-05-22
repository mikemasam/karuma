#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "route.h"
#include "../core/controller.h"

namespace Networking {
  class Routes {
    public:
      Routes();
      ~Routes();
      virtual void anonymousRoutes();
      virtual void authorizedRoutes();
  };
}
