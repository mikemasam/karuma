#include "routing.h"


namespace Networking {
  using string = std::string;
  bool Router::match(string match){
    if(this->parts.size() < 1) 
      return false;
    if(match.back() == '/')
      match.pop_back();
    if(path.back() == '/')
      path.pop_back();

    if(match.front() == '/')
      match.erase(0,1);
    if(path.front() == '/')
      path.erase(0,1);

    if(path == match)
      return true;

    std::vector<std::string> _match_parts = Utils::explode(match,'/');

    for(unsigned int i = 0;i < this->parts.size();i++){
      std::string part  = this->parts[i];

      if(i > _match_parts.size())
        continue; 

      std::string _match_part = _match_parts[i];
      std::string _regex_match;
      if(part == _match_part){
        return true;
      }else if(Utils::regex(part,"{(.*?)}",_regex_match)){
        RouteValue rv;
        rv.name = _regex_match;
        rv.value = _match_part;
        this->_route_values.push_back(rv);
        if(i == (this->parts.size() - 1))
          return true;
      }
    }
    return false;
  }

  Router::Router(std::shared_ptr<Url> &url){
    if(url->isValid()){
      this->parts = Utils::explode(url->getPath(),'/');
    }
  }
}
