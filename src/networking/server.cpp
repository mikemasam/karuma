#include "server.h"
namespace Networking {


  Server::Server(){
    std::cout << "New Server" << std::endl;
  }

  void Server::serve(std::shared_ptr<Server> s){
    s->init();
  }

  void Server::init(){
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
        for(unsigned int i = 0; i < connections.size();i++){
          if(connections[i]->isDone())
            delete connections[i];
        }
        // This will receive the new connection
        tcp::socket socket{ioc};
        // Block until we get a connection
        acceptor.accept(socket);
        Client *s = new Client();
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
