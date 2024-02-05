#pragma once

class INetworkManager
{
public:
  virtual bool connect() = 0;
  virtual bool sendData(const int& data) = 0;
  virtual void disconnect() = 0;
  virtual void reconnect() = 0;
  virtual ~INetworkManager() = default;
};