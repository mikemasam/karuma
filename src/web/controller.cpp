#include "controller.h"
#include "web.h"
#include <memory>
namespace Core {
  std::string Controller::index(){
    return "Index Base";
  }

      void Controller::init(Web *web){
        this->web = web;
      }

      const Web* Controller::getContext(){
        return this->web;
      }
      const std::shared_ptr<Url> Controller::getUrl(){
        return this->web->getUrl();
      }
}
