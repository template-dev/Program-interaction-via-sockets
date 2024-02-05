#include <algorithm>
#include "../headers/DataProcessor.hpp"

void DataProcessor::start()
{
  if (inputThread.joinable())
    inputThread.join();
  
  m_exitFlag = true;
  m_cv.notify_one();
  
  if (processThread.joinable())
    processThread.join();
}

void DataProcessor::inputData()
{
  while (true)
  {
    std::unique_lock<std::mutex> lock(m_mutex);
    std::string msg;
    std::cout << "Enter a string (numbers): ";
    std::getline(std::cin, msg);

    bool isChar = false;
    for (const auto& ch : msg)
    {
      if (!std::isdigit(ch))
      {
        std::cout << "Letters have been found in the message! Please enter the numbers.\n";
        isChar = true;
        break;
      }
    }

    if (isChar) continue;

    std::sort(msg.begin(), msg.end(), std::greater<char>());

    for (auto it = msg.begin(); it != msg.end(); ++it)
    {
      if (*it % 2 == 0)
      {
        *it = 'K';
        it = msg.insert(std::next(it), 'B');
      }
    }
    m_buffer.push(msg);
    m_cv.notify_one();
  }
}

void DataProcessor::processAnalysis()
{
  while (true)
  {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, [&] { return m_exitFlag || !m_buffer.empty(); });

    if (m_exitFlag && m_buffer.empty())
      return;

    if (!m_buffer.empty())
    {
      std::cout << "Buffer: " << m_buffer.front() << std::endl;
      std::string receivedMsg = m_buffer.front();
      m_buffer.pop();
      int sum = 0;
      std::for_each(receivedMsg.begin(), receivedMsg.end(), [&sum](char ch){
        if (std::isdigit(ch))
          sum += ch - '0';
      });
      std::cout << "Sum: " << sum << std::endl;
      if(!m_networkManager.sendData(sum))
      {
        std::cerr << "Failed to send data. Ignoring the error." << std::endl;
      }
      sum = 0;
    }
  }
}

DataProcessor::~DataProcessor()
{
  m_exitFlag = true;
  m_cv.notify_all();

  if (inputThread.joinable())
    inputThread.join();

  if (processThread.joinable())
    processThread.join();
}