#pragma once
#ifndef controller_h
#define controller_h
#include <iostream>
#include <memory>
#include "../networking/url.h"

namespace Core {
  class Web;
  using string = std::string;
  using Url = Networking::Url;
  class Controller {
    public:
      virtual std::string index();
      void init(Web *web);
      const Web* getContext();
      const std::shared_ptr<Url> getUrl();
    private:
      void _index();
      Web *web;
  };
}
#endif
