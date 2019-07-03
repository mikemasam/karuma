#include <iostream>
#include <memory>
#include <vector>
#include "../networking/url.h"
#include "route_path.h"
#include "route_value.h"
#include "controller_response.h"

#pragma once
namespace Web {
  class Client;
  class WebServer;
  using string = std::string;
  using Url = Networking::Url;
  class Controller {
    public:
      void init(Client *client);
      ControllerResponse* processRequest(RoutePath path, std::vector<RouteValue> values);
      const WebServer* getContext();
      const std::shared_ptr<Url> getUrl();
    private:
      Client *client;
      ControllerResponse* getJsonResponse(std::string data);
      ControllerResponse* getNotFound(std::string data);
  };
}
