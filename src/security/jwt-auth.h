#include <iostream>
#include <dotenv.h>

#pragma once
namespace security {
  struct JwtClaim{
    std::string name;
    std::string body
  }
  class JwtAuth {
    JwtAuth();
    std::string create(int seconds);
  };
}
