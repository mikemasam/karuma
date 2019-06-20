#pragma once
#include <iostream>
#include <vector>

namespace Networking {
  class Url{
    public:
      Url(std::string url);
      bool isValid();
      std::string getPath();
      std::string getHost();
      std::string getProtocol();
      std::string getQuery();
      std::vector<std::string> getParts();
    private:
      std::string url;
      void parse(const std::string& url);
      std::string _protocol, _host, _path, _query;
      bool _valid = false;
      std::vector<std::string> parts;
  };
}
