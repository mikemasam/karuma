#include <iostream>
#include <chrono>
#include <jwt-cpp/jwt.h>

#pragma once
namespace Security {
  struct JwtClaim{
    std::string name;
    std::string body;
  };
  class JwtAuth {
    JwtAuth();
    std::string create(int seconds);
  };
}
