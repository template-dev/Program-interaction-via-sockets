#include "../headers/DataReceiver.hpp"

DataReceiver::DataReceiver(boost::asio::io_context& ioContext, unsigned short port)
  : m_acceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    m_socket(ioContext)
{
  startAccept();
}

void DataReceiver::startAccept()
{
 m_acceptor.async_accept(m_socket, [this](boost::system::error_code errorCode)
 {
    if (!errorCode)
    {
      std::cout << "Connection established. Waiting for data...\n";
      startRead();
    }
    else
    {
      if (errorCode == boost::asio::error::operation_aborted)
        return;
      std::cerr << "Error accepting connection: " << errorCode.message() << std::endl;
      m_acceptor.cancel();
    }
  });
}

void DataReceiver::processData(std::size_t data)
{
  if (data == sizeof(int))
  {
    int receivedValue;
    std::memcpy(&receivedValue, m_receivedData, sizeof(int));
    if (receivedValue > 2 && receivedValue % 32 == 0)
      std::cout << "Received valid data: " << receivedValue << std::endl;
    else
      std::cerr << "Error: Invalid data length or format!" << std::endl;
  }
  else
  {
      std::cerr << "Error: Invalid data received!" << std::endl;
  }
}

void DataReceiver::startRead()
{
  boost::asio::async_read(m_socket, boost::asio::buffer(m_receivedData, sizeof(int)),
  [this](boost::system::error_code errorCode, std::size_t length)
  {
    if (!errorCode)
    {
      processData(length);
      startRead();
    }
    else
    {
      if (errorCode == boost::asio::error::eof)
      {
        std::cout << "Client disconnected. Waiting for a new connection." << std::endl;
        m_socket.close();
        startAccept();
      }
      else
      {
        std::cerr << "Error reading data: " << errorCode.message() << std::endl;
      }
    }
  });
}