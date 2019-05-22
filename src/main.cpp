#include <iostream>
#include <vector>
#include <algorithm>
#include "core/web.h"
#include "core/controller.h"

using string = std::string;
using Controller = Networking::Controller;
using Web = Core::Web;



class UserController : public Controller {
  public:
    std::string index() override;
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
  Web *web = new Web();
  web->addRoute(std::make_shared<UserController>(),"/user/{id}/profile/");
  web->setCurrentUrl("http:://google.com/docs/ma dan.pdf");
  web->setCurrentUrl("http:://google.com/user/dan");
  web->setCurrentUrl("http:://google.com/user/1/profile?213&w=1");
  std::cout << web->getRoutes().size() << std::endl;
  return 1;
}

