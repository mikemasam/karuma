#pragma once
#include <iostream>
#include <memory>
#include "../networking/url.h"
namespace Web {
  class Client;
  class WebServer;
  using string = std::string;
  using Url = Networking::Url;
  class Controller {
    public:
      virtual std::string index();
      void init(Client *client);
      const WebServer* getContext();
      const std::shared_ptr<Url> getUrl();
    private:
      void _index();
      Client *client;
  };
}
