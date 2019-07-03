#pragma once
#include <iostream>
#include <vector>

namespace Networking {
  using namespace std;
  class Url{
    public:
      Url(const string url, const string method);
      bool isValid();
      std::string getPath();
      std::string getMethod();
      std::string getHost();
      std::string getProtocol();
      std::string getQuery();
      std::string getRaw();
      std::vector<std::string> getParts();
    private:
      std::string url;
      void parse(const std::string& url);
      std::string _protocol, _host, _path, _query, _method;
      bool _valid = false;
      std::vector<std::string> parts;
  };
}
