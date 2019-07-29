#include <iostream>
#include <memory>
#include <vector>
#include "../networking/url.h"
#include "route_path.h"
#include "route_value.h"
#include "controller_response.h"

#pragma once
/*
 * Controller class
 */
namespace Web {
  class Client;
  class WebServer;
  using string = std::string;
  using Url = Networking::Url;
  class Controller {
    public:
      /*
       * init - initiate controller with client pointer
       * Params
       * client - Client pointer object to be handled
       */
      void init(Client *client);
      /*
       * processRequest - handle request in controller with the provided path and query values
       * Params
       * path - RoutePath object
       * values - a list of RouteValue from url
       * Return
       * ControllerResponse - a base response object
       */
      ControllerResponse* processRequest(RoutePath path, std::vector<RouteValue> values);
      /*
       * getContext - get WebServer object from controller
       * Return
       * WebServer - WebServer object pointer 
       */
      const WebServer* getContext();
      /*
       * getUrl - get url shared pointer object
       * Return
       * shared_prt<Url> - shared pointer of Url object
       */
      const std::shared_ptr<Url> getUrl();
    private:
      Client *client; //current client handled by this controller object
      ControllerResponse* getJsonResponse(std::string data); //json response generator
      ControllerResponse* getNotFound(std::string data); //not found response generator
  };
}
