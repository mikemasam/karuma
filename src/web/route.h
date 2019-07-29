#include <iostream>
#include <vector>
#include <memory>
#include "controller.h"
#include "route_path.h"
#include "route_value.h"
#include "route_found.h"
#pragma once
/*
 * A Route Class insude Web Namespace
 * contructor takes a shared pointer of Controller class and a controller route name.
 */
namespace Web {
  using Controller = Web::Controller;
  using string = std::string;
  class Route {
    public:
      /* constructor 
       * Params
       * _controller - controller shared pointer 
       * _name - controller Route name 
       * */
      Route(std::shared_ptr<Controller> _controller, std::string _name) : controller(_controller), name(_name){}
      /* addPath - Use to add path to a controller route
       * Params
       * name - unique name if the path 
       * path - a url path with query values in {0} style
       * anonymous - whether this path is can be accessed without authentication
       * Return void
       */
      void addPath(std::string name, std::string path, bool anonymous);
      /*
       * match - match provided url in every path in this controller route and return RouteFound if any matched
       * Params
       * url - a Url object from client request
       * Return
       * RouteFound - a RouteFound object or null when no match found
       */
      RouteFound* match(std::shared_ptr<Url> url);
      /* getName - get a controller route name
       * Return
       * string - name of controller route name
       */
      std::string getName();
    private:
      /*
       * _match - match provided url in path true if any matched
       * Params
       * url - a Url object from client request
       * route_path - a route to match with
       * Return
       * bool - true if a match found
       */
      bool _match(std::shared_ptr<Url> url, RoutePath route_path);
      std::shared_ptr<Controller> controller; //current controller shared pointer
      std::string name; //current controller route name
      std::vector<RoutePath> paths; //current list of RoutePath
      std::vector<RouteValue> _route_values; //route values found by match function in url
  };
}
