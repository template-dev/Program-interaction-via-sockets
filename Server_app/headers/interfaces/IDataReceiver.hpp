#pragma once

class IDataReceiver
{
public:
  ~IDataReceiver() = default;
  virtual void startAccept() = 0;
  virtual void startRead() = 0;
  virtual void processData(std::size_t length) = 0;
};