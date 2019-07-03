#include "url.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <functional>
#include "../helpers/utils.h"

namespace Networking {
  Url::Url(const string url, const string method){

    this->url = url;
    this->_method = method;
    std::cout << "client url : " << this->url << std::endl;
    parse(this->url);
    if(this->isValid()){
      this->parts = Helpers::Utils::explode(this->getPath(),'/');
    }else{
      std::cout << "Invalid URL" << std::endl;
    }
  }

  //credits
  //stackoverflow.com_
  //answered Apr 11 '10 at 6:17
  //wilhelmtell
  // ctors, copy, equality, ...

  void Url::parse(const string& url_s)
  {
    if(url_s.length() > 2083)
    {
      _valid = false;
      std::cout << "?Too long url" << std::endl;
      return;
    }
    const string prot_end("://");
    string::const_iterator prot_i = search(url_s.begin(), url_s.end(),
        prot_end.begin(), prot_end.end());
    _protocol.reserve(distance(url_s.begin(), prot_i));
    transform(url_s.begin(), prot_i,
        back_inserter(_protocol),
        ptr_fun<int,int>(tolower)); // protocol is icase
    if( prot_i == url_s.end() ){
      std::cout << "?Protocal ended" << std::endl;
      return;
    }
    advance(prot_i, prot_end.length());
    string::const_iterator path_i = find(prot_i, url_s.end(), '/');
    _host.reserve(distance(prot_i, path_i));
    transform(prot_i, path_i,
        back_inserter(_host),
        ptr_fun<int,int>(tolower)); // host is icase
    string::const_iterator query_i = find(path_i, url_s.end(), '?');
    _path.assign(path_i, query_i);
    if( query_i != url_s.end() )
      ++query_i;
    _query.assign(query_i, url_s.end());
    _valid = true;
  }

  bool Url::isValid(){
    return _valid;
  }

  std::string Url::getMethod(){
    return this->_method;
  }
  std::string Url::getPath(){
    return this->_path;
  }

  std::string Url::getQuery(){
    return this->_query;
  }

  std::string Url::getProtocol(){
    return this->_protocol;
  }

  std::vector<std::string> Url::getParts(){
    return this->parts;
  }

  std::string Url::getRaw(){
    return this->url;
  }
}
