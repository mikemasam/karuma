#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

#include "utils.h"

namespace Helpers {
  std::vector<std::string> Utils::explode(std::string str,char delimar){
    std::stringstream ss(str);
    std::vector<std::string> result;

    while( ss.good() )
    {
      std::string substr;
      getline( ss, substr, delimar );
      if(!substr.empty())
        result.push_back( substr );
    }
    return result;
  }


  bool Utils::regex(std::string subject,std::string reg, std::string &result){
    try {
      std::smatch match;
      std::regex re(reg);
      if (std::regex_search(subject, match, re)) {
        result = match.str(1);
        return true;
      }
    } catch (std::regex_error& e) {
      std::cout << "Error " << e.what() << std::endl;
      // Syntax error in the regular expression
    }
    return false;
  }

  std::string Utils::random_uuid() {
    boost::uuids::random_generator generator;
    boost::uuids::uuid uuid = generator();
    return to_string(uuid);
  }
  // Append an HTTP rel-path to a local filesystem path.
  // The returned path is normalized for the platform.
  std::string Utils::target_normalize(beast::string_view base, beast::string_view path) {
    if (base.empty())
      return std::string(path);
    std::string result(base);
#ifdef BOOST_MSVC
    char constexpr path_separator = '\\';
    if(result.back() == path_separator)
      result.resize(result.size() - 1);
    result.append(path.data(), path.size());
    for(auto& c : result)
      if(c == '/')
        c = path_separator;
#else
    char constexpr path_separator = '/';
    if(result.back() == path_separator)
      result.resize(result.size() - 1);
    result.append(path.data(), path.size());
#endif
    return result;
  }


}
