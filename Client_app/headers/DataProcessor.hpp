#pragma once

#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <algorithm>
#include <memory>
#include "interfaces/IDataProcessor.hpp"
#include "NetworkManager.hpp"

class DataProcessor : public IDataProcessor
{
public:
  DataProcessor(const std::string& ip, const boost::asio::ip::port_type& port)
    : m_exitFlag{false}
    , m_buffer{}
    , m_mutex{}
    , m_cv{}
    , m_networkManager(ip, port)
    , inputThread(&DataProcessor::inputData, this)
    , processThread(&DataProcessor::processAnalysis, this)
  {}
  ~DataProcessor();

  void start() override;

private:
  void inputData();
  void processAnalysis();

private:
  bool m_exitFlag;
  std::queue<std::string> m_buffer;
  std::mutex m_mutex;
  std::condition_variable m_cv;
  NetworkManager m_networkManager;
  std::thread inputThread;
  std::thread processThread;
};