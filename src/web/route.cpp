#include <iostream>
#include "route.h"
#include <memory>
#include "../helpers/utils.h"

namespace Web {
  void Route::addPath(std::string name, std::string path, bool anonymous){
    auto p = RoutePath {name, path, anonymous};
    this->paths.push_back(p);
  }

  bool Route::_match(std::shared_ptr<Url> url, RoutePath route_path){
    //get Route path
    std::string _route_path = route_path.path;
    //get url path
    std::string _url_path  = url->getPath();



    //check if last or first character is forward slash and remove
    if(_route_path.back() == '/')
      _route_path.pop_back();
    if(_url_path.back() == '/')
      _url_path.pop_back();
    if(_route_path.front() == '/')
      _route_path.erase(0,1);
    if(_url_path.front() == '/')
      _url_path.erase(0,1);


    //comapre url path and route path
    if(_url_path == _route_path)
      return true;

    unsigned int match_count = 0;

    std::vector<std::string> route_parts = Helpers::Utils::explode(_route_path,'/');
    auto url_parts = url->getParts();

    //loop through url parts
    for(unsigned int i = 0;i < url_parts.size();i++){
      //get single url part
      std::string url_part = url_parts[i];
      //if url parts size is less break
      if(i >= route_parts.size())
        break; 
      //get a single route part
      std::string route_part = route_parts[i];

      std::cout << "Url Part= " << url_part << std::endl; 
      std::cout << "Route Part= " << route_part << std::endl; 

      std::string _regex_match;
      //compare url part and route part
      if(route_part == url_part){
        match_count++;
      }else if(Helpers::Utils::regex(route_part,"\\{(.*)\\}",_regex_match)){ //check for in url values
        RouteValue rv;
        rv.name = _regex_match;
        rv.value = url_part;
        this->_route_values.push_back(rv);
        match_count++;
      }
    }

    std::cout << "Matched Count = " << match_count << ", Url count = " << url_parts.size() << std::endl; 

    if(match_count == url_parts.size())
      return true;
    this->_route_values.clear();
    return false;
  }

  RouteFound* Route::match(std::shared_ptr<Url> url){

    //check url parts size
    if(url->getParts().size() < 1) {
      std::cout << "Url path too small " << url->getPath() << std::endl; 
      return NULL;
    }

    for(unsigned int i = 0;i < this->paths.size(); i++){
      RoutePath route_path = this->paths[i];
      if(this->_match(url, this->paths[i])){
        RouteFound * found = new RouteFound();

        found->controller = std::make_shared<Controller>(*this->controller);
        found->values = this->_route_values;
        found->path = route_path;

        return found;
      }
    }

    return NULL;
  }

  std::string Route::getName(){
    return this->name;
  }

}
