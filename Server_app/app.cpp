#include <boost/asio.hpp>
#include "headers/DataReceiver.hpp"

int main()
{
  while(true)
  {
    boost::asio::io_context ioContext;
    unsigned short port = 12345;
    DataReceiver dataReceiver(ioContext, port);
    ioContext.run();
  }
}