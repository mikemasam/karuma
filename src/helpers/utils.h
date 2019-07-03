#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <boost/beast/core.hpp>
#include <boost/config.hpp>

#pragma once
namespace Helpers {
  namespace beast = boost::beast;
  class Utils {
    public:
      static std::vector<std::string> explode(std::string str,char delimar);
      static bool regex(std::string subject,std::string reg, std::string &result);
      static std::string random_uuid();
      static std::string target_normalize(beast::string_view base, beast::string_view path);
  };
}
