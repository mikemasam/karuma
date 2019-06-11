#include "server.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <thread>
#include <boost/config.hpp>
#include "client.h"
#include "web-server.h"

namespace Web {

  namespace net = boost::asio;            // from <boost/asio.hpp>
  using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
  using WebServer = Web::WebServer;

  Server::Server(){
    std::cout << "New Server" << std::endl;
  }

  void Server::serve(WebServer *web_server){
    web_server->server->init(web_server);
  }

  void Server::clean(){
    std::cout << "----------------clients cleaning----------" << std::endl;
    for(unsigned int i = 0; i < connections.size();i++){

      //make sure size is ok
      if(i > (connections.size() - 1))
        continue;

      //get reference for the client
      Client * c = connections[i];

      //check if client is Done
      if(c->isDone()){
        std::cout << "Client Disconnected:" << c->getClientId() << std::endl;
        //delete client
        delete connections[i];
        //remove client
        connections.erase(connections.begin() + i);
      }
    }
    std::cout << "----------------end clients cleaning----------" << std::endl;
  }
  void Server::init(WebServer *web_server){
    try
    {
      std::cout << "Opening : " << address << ":" << port << std::endl;
      auto const _address = net::ip::make_address(address);
      auto const _port = static_cast<unsigned short>(std::atoi(port.c_str()));
      // The io_context is required for all I/O
      net::io_context ioc{1};
      // The acceptor receives incoming connections
      tcp::acceptor acceptor{ioc, {_address, _port}};
      for(;;)
      {
        //do cleaning
        this->clean();
        //list connected clients
        std::cout << "----------------clients----------" << std::endl;
        for(unsigned int i = 0; i < connections.size();i++){
          Client * c = connections[i];
          std::cout << "Client Connected:" << c->getClientId() << std::endl;
        }
        std::cout << "----------------clients----------" << std::endl;
        std::cout << "Connected:" << connections.size() << std::endl;
        // This will receive the new connection
        tcp::socket socket{ioc};
        // Block until we get a connection
        acceptor.accept(socket);
        //new client
        Client *s = new Client(web_server);
        //add client to pull
        this->connections.push_back(s);
        // Launch the session, transferring ownership of the socket
        std::thread{std::bind(&Client::init,std::move(socket),s)}.detach();
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
}
