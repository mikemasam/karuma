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

    unsigned int match_count = 0;
    std::vector<std::string> _match_parts = Utils::explode(match,'/');

    for(unsigned int i = 0;i < _match_parts.size();i++){
      std::string _match_part  = _match_parts[i];
      if(i >= this->parts.size())
        break; 
      std::string part = this->parts[i];

      //std::cout <<"router [" << _match_part << "->" << part << "]" << std::endl;
      std::string _regex_match;
      if(part == _match_part){
        match_count++;
      }else if(Utils::regex(_match_part,"\\{(.*)\\}",_regex_match)){
        RouteValue rv;
        rv.name = _regex_match;
        rv.value = _match_part;
        this->_route_values.push_back(rv);
        match_count++;
      }
    }

      //std::cout <<"[" << match << " - #" << match_count << "] values size " << this->_route_values.size() << std::endl;

      if(match_count == _match_parts.size())
        return true;
      this->_route_values.clear();
      return false;
  }

  Router::Router(std::shared_ptr<Url> &url){
    if(url->isValid()){
      this->parts = Utils::explode(url->getPath(),'/');
    }else{

    }
  }
}
