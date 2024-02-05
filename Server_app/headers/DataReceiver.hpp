#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include "interfaces/IDataReceiver.hpp"

class DataReceiver : public IDataReceiver
{
public:
  DataReceiver(boost::asio::io_context& ioContext, unsigned short port);

private:
  boost::asio::ip::tcp::acceptor m_acceptor;
  boost::asio::ip::tcp::socket m_socket;
  static const size_t m_maxDataLength = sizeof(int);
  char m_receivedData[sizeof(int)];

  void startAccept() override;
  void startRead() override;
  void processData(std::size_t length) override;
};