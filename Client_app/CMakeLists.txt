cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME "Client_App")

project(${PROJECT_NAME})

set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/external-libraries/boost)
find_package(Boost COMPONENTS REQUIRED)

add_executable(
  ${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/headers/interfaces/IDataProcessor.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/headers/interfaces/INetworkManager.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/headers/DataProcessor.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/headers/NetworkManager.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/DataProcessor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/NetworkManager.cpp
  app.cpp
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})