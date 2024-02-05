#pragma once

class IDataProcessor
{
public:
  virtual void start() = 0;
  virtual ~IDataProcessor() = default;
};