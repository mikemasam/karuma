#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#pragma once
class Utils {
  public:
    static std::vector<std::string> explode(std::string str,char delimar);
    static bool regex(std::string subject,std::string reg, std::string &result);
};

