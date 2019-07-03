#include <iostream>
#include <vector>
#include <algorithm>
#include "core/app.h"
#include "web/web-server.h"
#include "web/controller.h"
#include "web/route.h"
#include <jwt-cpp/jwt.h>

using string = std::string;
using Controller = Web::Controller;
using WebServer = Web::WebServer;
using App = Core::App;
using Route = Web::Route;

class UserController : public Controller {
  public:
    std::string index();
    ~UserController();
};

std::string UserController::index(){
  std::cout << "query = " << this->getUrl()->getQuery() << std::endl;
  std::cout << "url = " << this->getUrl()->getPath() << std::endl;
  std::cout << "protocol = " << this->getUrl()->getProtocol() << std::endl;

  return "Index Called";
}

UserController::~UserController(){
  std::cout << " Controller Destroyed" << std::endl;
}




int main(){
  App::app_init();
  WebServer *web = new WebServer();
  web->serve("127.0.0.1","9999");
  auto r = Route(std::make_shared<UserController>(),"/user/{id}/profile/");
  r.addPath("-user-index","/user/{id}/profile/",true);
  web->addRoute(r);
  //web->processRequest("http:://google.com/user/1/profile?213&w=1");
  getchar();
  return 1;
}

