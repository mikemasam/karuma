#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include "utils.h"

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
