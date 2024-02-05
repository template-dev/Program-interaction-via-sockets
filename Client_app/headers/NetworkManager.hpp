#pragma once

#include <boost/asio.hpp>
#include "interfaces/INetworkManager.hpp"

class NetworkManager : public INetworkManager
{
public:
  NetworkManager(const std::string& ip, const boost::asio::ip::port_type& port);
  ~NetworkManager();

  bool sendData(const int& data) override;
private:
  boost::asio::io_context m_ioContext;
  boost::asio::ip::tcp::socket m_socket;
  boost::asio::ip::tcp::endpoint m_endpoint;
  unsigned int m_failedSendAttempts;

  bool connect() override;
  void reconnect() override;
  void disconnect() override;
};