#include <iostream>
#include "client.h"

#pragma once
/*
 * server class inside Web namespace
 */
namespace Web {
  class WebServer;
  class Server {
    public:
      /* server constructer */
      Server();
      static void serve(WebServer *ws);       //pass web_server context by pointer to initialize server class in another thread 
      void init(WebServer *ws);               //initilize server and accept clients, pass web server context to clients
      std::string address;                    //the address in which to accept client from
      std::string port;                       //the port in which to accept client from
    private:
      std::vector<Client*> connections;       //active connections from clients
      void clean();                           //clear closed clients connections
  };
}
