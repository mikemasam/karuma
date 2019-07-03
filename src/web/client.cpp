#include "client.h"
#include "send.h"
#include "web-server.h"
#include "route.h"
#include "../helpers/utils.h"


namespace Web {

  Client::Client(WebServer *web_server) {
    this->web_server = web_server;
    this->client_id = Helpers::Utils::random_uuid();
    // example using memcpy

    std::cout << "New Client : " << this->client_id << std::endl;
  }

  Client::~Client(){
    std::cout << "Client Disconnected:" << this->getClientId() << std::endl;
  }

  std::string Client::getClientId(){
    return this->client_id;
  }

  WebServer* Client::getWeb() {
    return web_server;
  }

  std::shared_ptr<Url> Client::getUrl() {
    return url;
  }

  bool Client::isDone() {
    return this->done;
  }

  http::response<http::string_body> Client::getResponse(ControllerResponse* controller_res, int version){
    //construct response
    http::response<http::string_body> res{boost::beast::http::int_to_status(controller_res->status), version};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, controller_res->type);
    res.keep_alive(true);
    if(controller_res != NULL){
      res.body() = controller_res->data;
    }else{
      res.body() = "";
    }
    res.prepare_payload();
    //return http response object
    return res;
  }
  // This function produces an HTTP response for the given
  // request. The type of the response object depends on the
  // contents of the request, so the interface requires the
  // caller to pass a generic lambda for receiving the response.
  template<class Body, class Allocator, class Send>
    void Client::handle_request(http::request<Body, http::basic_fields<Allocator>>&&  req, Send&& send) {
      //this->web_server;
      this->url = std::make_shared<Url>(Helpers::Utils::target_normalize("http://localhost", req.target()),req.method_string().to_string());
      auto res = this->findRoute();
      send(this->getResponse(res,req.version()));
    }

  //------------------------------------------------------------------------------

  // Report a failure
  void Client::fail(beast::error_code ec, char const* what) {
    std::cerr << "ClientError-:" << what << ": " << ec.message() << "\n";
  }


  void Client::init(tcp::socket& socket,Client *s){
    s->new_connection(socket);
  }
  // Handles an HTTP server connection
  void Client::new_connection( tcp::socket& socket){
    bool close = false;
    beast::error_code ec;

    // This buffer is required to persist across reads
    beast::flat_buffer buffer;

    // This lambda is used to send messages
    Send<tcp::socket> lambda{socket, close, ec};

    for(;;) {
      // Read a request
      http::request<http::string_body> req;
      http::read(socket, buffer, req, ec);

      //check if it's end of file/connection
      if(ec == http::error::end_of_stream){
        this->Done();
        break;
      }

      if(ec) {
        this->Done();
        return this->fail(ec, "read");
      }

      // Send the response
      this->handle_request(std::move(req),lambda);
      if(ec) {
        this->Done();
        return this->fail(ec, "write");
      }

      if(close) {
        // This means we should close the connection, usually because
        // the response indicated the "Connection: close" semantic.
        this->Done();
        break;
      }
    }
    // Send a TCP shutdown
    socket.shutdown(tcp::socket::shutdown_send, ec);
    // At this point the connection is closed gracefully
  }

  void Client::Done(){
    this->done = true;
  }

  //find route match
  ControllerResponse* Client::findRoute(){
    ControllerResponse* res;
    bool found = false;
    std::vector<Route> routes = this->web_server->getRoutes();

    for(unsigned int j = 0;j <routes.size();j++){
      Route route = routes[j];
      auto o = route.match(this->url);
      if(o != NULL){
        //this->web_server->getRoutes()[j].controller->init(this);
        //std::cout << this->web_server->getRoutes()[j].controller->index() << std::endl;
        res = o->controller->processRequest(o->path,o->values);
        std::cout << "Found One" << std::endl;
        found = true;
      }else{
        std::cout << "Route " << route.getName() << " not found on path " << this->url->getPath() << std::endl;
      }
    }
    if(!found)
      std::cout << this->url->getRaw() << " - Route not found at all" << std::endl << "-----------------------" << std::endl;
    return res;
  }
}
