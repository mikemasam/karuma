#include <iostream>
#include <vector>
#include <algorithm>
#include "core/web.h"
#include "core/controller.h"
#include "networking/routes.h"

using string = std::string;
using Controller = Networking::Controller;
using Routes = Networking::Routes;
using Route = Networking::Route;
using Web = Core::Web;



class UserController : public Controller {
  public:
    std::string index() override;
    ~UserController();
};

std::string UserController::index(){
  return "User Index";
}

UserController::~UserController(){
  std::cout << " Controller Destroyed" << std::endl;
}



class MyRoutes : public Routes {
  public:
    MyRoutes();
    void anonymousRoutes() override;
    //const std::vector<Route> getRoutes();
};

MyRoutes::MyRoutes() : Routes(){
}


void MyRoutes::anonymousRoutes(){
  this->addRoute("/user/{id}/profile/");
}





int main(){
  MyRoutes m; 
  std::cout << m.getRoutes().size() << std::endl;
  Web *web = new Web();
  web->setCurrentUrl("http:://google.com/docs/ma dan.pdf");
  web->setCurrentUrl("http:://google.com/user/dan");
  web->setCurrentUrl("http:://google.com/user/1/profile");
  return 1;
}

