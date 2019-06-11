#include "controller.h"
#include "web-server.h"
#include "client.h"
namespace Web {
  std::string Controller::index(){
    return "Index Base";
  }

  void Controller::init(Client *client){
    this->client = client;
  }

  const WebServer* Controller::getContext(){
    return this->client->getWeb();
  }
  const std::shared_ptr<Url> Controller::getUrl(){
    return this->client->getUrl();
  }
}
