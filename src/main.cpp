#include <iostream>
#include <vector>
#include <algorithm>
#include "../src/web/web.h"
#include "../src/web/controller.h"
#include <jwt-cpp/jwt.h>

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
  //  Web *web = new Web();
  //  web->serve("127.0.0.1","9999");
  //  web->addRoute(std::make_shared<UserController>(),"/user/{id}/profile/");
  //  web->setCurrentUrl("http:://google.com/user/1/profile?213&w=1");
  std::string token = jwt::create()
    .set_issuer("auth0")
    .set_issued_at(std::chrono::system_clock::now())
    .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{3600})
    .set_payload_claim("sample", std::string("test"))
    .sign(jwt::algorithm::hs256{"secret"});


  auto decoded = jwt::decode(token);

  for(auto& e : decoded.get_payload_claims())
    std::cout << e.first << " = " << e.second.to_json() << std::endl;

  return 1;
}

