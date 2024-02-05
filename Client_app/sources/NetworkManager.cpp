#include <iostream>
#include <string>
#include "../headers/NetworkManager.hpp"

NetworkManager::NetworkManager(const std::string& ip, const boost::asio::ip::port_type& port)
  : m_ioContext{}
  , m_socket{m_ioContext}
  , m_endpoint{boost::asio::ip::address::from_string(ip), port}
  , m_failedSendAttempts{0}
{
  connect();
}

NetworkManager::~NetworkManager()
{
  if(!m_ioContext.stopped() && m_socket.is_open())
  {
    m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    m_socket.close();
    m_ioContext.stop();
  }
}

bool NetworkManager::connect()
{
  try
  {
    m_socket.connect(m_endpoint);
    return true;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return false;
  }  
}

void NetworkManager::disconnect()
{
  if (m_socket.is_open())
  {
    m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    m_socket.close();
  }
}

void NetworkManager::reconnect()
{
  disconnect();
  while (!connect())
  {
    std::cerr << "Failed to reconnect. Retrying in 5 seconds..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
  }
}

bool NetworkManager::sendData(const int& data)
{
  try
  {
    if(!m_socket.is_open())
      reconnect();

    const auto bytes = boost::asio::buffer(reinterpret_cast<const char*>(&data), sizeof(data));
    boost::asio::write(m_socket, bytes);
    return true;
  }
  catch(const std::exception& ex)
  {
    std::cerr << "Error sending data to the server: " << ex.what() << std::endl;
    return false;
  }
}