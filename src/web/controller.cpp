#include "controller.h"
#include "web-server.h"
#include "client.h"
namespace Web {

  ControllerResponse* Controller::processRequest(RoutePath path, std::vector<RouteValue> values) {
    std::cout << "Base Request" << std::endl;
    return this->getJsonResponse("['1':'qwd2ed']");
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

  ControllerResponse* Controller::getJsonResponse(std::string data){
    ControllerResponse* res = new ControllerResponse();
    res->data = data;
    res->type = "application/json";
    res->status = 200;
    return res;
  }

  ControllerResponse* Controller::getNotFound(std::string data){
    ControllerResponse* res = new ControllerResponse();
    res->data = data;
    res->type = "html/text";
    res->status = 404;
    return res;
  }

}
