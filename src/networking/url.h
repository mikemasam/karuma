#pragma once
#include <iostream>

namespace Networking {
  class Url{
    public:
      Url(std::string url);
      bool isValid();
      std::string getPath();
      std::string getHost();
      std::string getProtocal();
      std::string getQuery();
    private:
      std::string url;
      void parse(const std::string& url);
      std::string _protocol, _host, _path, _query;
      bool _valid = false;
  };
}
