#include "headers/DataProcessor.hpp"

int main()
{
  std::string ip = "127.0.0.1";
  unsigned short port = 12345;
  DataProcessor dataProcessor(ip, port);
  dataProcessor.start();
}