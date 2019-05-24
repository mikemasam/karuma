#include "client.h"
#include "send.h"

namespace Networking {


  Client::Client(){
    std::cout << "New Client" << std::endl;
  }

  bool Client::isDone() {
    return this->done;
  }

  http::response<http::string_body> Client::getResponse(auto version, auto keep_alive){
    http::response<http::string_body> res{http::status::not_found, version};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.keep_alive(keep_alive);
    res.body() = "The resource '' was not found.";
    res.prepare_payload();
    return res;
  }
  // This function produces an HTTP response for the given
  // request. The type of the response object depends on the
  // contents of the request, so the interface requires the
  // caller to pass a generic lambda for receiving the response.
  template<class Body, class Allocator, class Send>
    void Client::handle_request(http::request<Body, http::basic_fields<Allocator>>&&  req, Send&& send) {
      send(this->getResponse(req.version(),req.keep_alive()));
      this->done = true;
    }

  //------------------------------------------------------------------------------

  // Report a failure
  void Client::fail(beast::error_code ec, char const* what) {
    std::cerr << what << ": " << ec.message() << "\n";
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
    for(;;)
    {
      // Read a request
      http::request<http::string_body> req;
      http::read(socket, buffer, req, ec);

      if(ec == http::error::end_of_stream)
        break;
      if(ec)
        return this->fail(ec, "read");

      // Send the response
      this->handle_request(std::move(req),lambda);
      if(ec)
        return this->fail(ec, "write");

      if(close)
      {
        // This means we should close the connection, usually because
        // the response indicated the "Connection: close" semantic.
        break;
      }
    }
    // Send a TCP shutdown
    socket.shutdown(tcp::socket::shutdown_send, ec);
    // At this point the connection is closed gracefully
  }
}
